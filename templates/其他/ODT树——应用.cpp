//P4344
#include <bits/stdc++.h>
using namespace std;
#define IT set<Node>::iterator

int n,m;

// 定义区间节点结构体
struct Node {
    int l, r;       // 区间的左右端点
    mutable int v;  // 区间的值，mutable 允许在 const 对象中修改
    Node(int L, int R = -1, int V = 0) : l(L), r(R), v(V) {}
    // 重载 < 运算符，用于 set 排序
    bool operator<(const Node &o) const {
        return l < o.l;
    }
};

set<Node> s; // 使用 set 存储区间节点

// 将区间在 pos 处分割，返回分割后的右区间迭代器
IT split(int pos) {
    IT it = s.lower_bound(Node(pos)); // 找到第一个左端点 >= pos 的区间
    if (it != s.end() && it->l == pos)
        return it; // 如果 pos 正好是某个区间的起点，直接返回
    --it; // 否则找到包含 pos 的区间
    int L = it->l, R = it->r, V = it->v;
    s.erase(it); // 删除原区间
    s.insert(Node(L, pos - 1, V)); // 插入左半部分
    return s.insert(Node(pos, R, V)).first; // 插入右半部分并返回迭代器
    // 返回一个pair，其中第一个元素是一个迭代器，指向插入的元素（或已经存在的元素），
    // 第二个元素是一个布尔值，表示插入是否成功。
}

// 区间赋值操作
void assign(int l, int r, int val) {
    IT itr = split(r + 1), itl = split(l); // 分割区间 [l, r]
    s.erase(itl, itr); // 删除 [l, r] 内的所有区间 删除从itl到itr之间的所有元素（不包括itr）
    s.insert(Node(l, r, val)); // 插入新的区间
}

void compute(int l,int r,int u,int v){
    IT itr=split(r+1),itl=split(l);
    int sum=0;
    for(;itl!=itr;itl++){
        if(itl->v==1){
            sum+=(itl->r - itl->l +1);
        }
    }
    assign(l,r,0);
    itr=split(v+1),itl=split(u);
    //cout<<sum<<endl;
    for(;itl!=itr&&sum;itl++){
        if(itl->v==0){
            if(sum>=(itl->r-itl->l+1)){
                itl->v=1;
                sum-=(itl->r-itl->l+1);
            }
            else{
                assign(itl->l,itl->l+sum-1,1);
                sum=0;
            }
        }
    }
}

int query(int l,int r){
    IT itr=split(r+1),itl=split(l);
    int res=0,ans=0;
    for(;itl!=itr;itl++){
        if(itl->v==0){
            res+=(itl->r-itl->l+1);
        }
        else{
            ans=max(ans,res);
            res=0;
        }
    }
    return max(ans,res);//因为最后有可能是0结尾
}

int main()
{
    cin>>n>>m;
    s.insert(Node(1, n, 1));
    for(int i=1;i<=m;i++){
        int op,l,r;
        cin>>op>>l>>r;
        if(op==0){
            assign(l,r,0);
        }
        else if(op==1){
            int u,v;
            cin>>u>>v;
            compute(l,r,u,v);
        }
        else{
            cout<<query(l,r)<<endl;
        }
    }
    return 0;
}

