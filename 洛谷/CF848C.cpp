#include<bits/stdc++.h>
using namespace std;
const int MAXN = 8e5+5;
const int MAXM = 1e5+5;

int n,m;
int val[MAXM];
set<int>s[MAXM];
long long ans[MAXM];

struct node{
    int op,l,r,id;
};
node nums[MAXN];
int cnt;//所有操作个数

long long tree[MAXM];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

bool cmp(node a,node b){
    return a.l>b.l;
}

inline int lowbit(int x){
    return x&-x;
}

void add(int x,int val){
    while(x<=n){
        tree[x]+=val;
        x+=lowbit(x);
    }
}

long long query(int x){
    long long ans=0;
    while(x){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}

void merge(int l,int mid,int r){
    int p1=l-1,p2=mid+1;
    for(;p2<=r;p2++){
        while(p1+1<=mid&&nums[p1+1].l>=nums[p2].l){
            p1++;
            if(nums[p1].op){
                add(nums[p1].r,nums[p1].op*(nums[p1].r-nums[p1].l));
            }
        }
        if(nums[p2].op==0){
            ans[nums[p2].id]+=query(nums[p2].r);
        }
    }
    for(int i=l;i<=p1;i++){
        if(nums[i].op){
            add(nums[i].r,nums[i].op*(nums[i].l-nums[i].r));
        }
    }
    sort(nums+l,nums+r+1,cmp);
}

void cdq(int l,int r){
    if(l==r){
        return ;
    }
    int mid=(l+r)>>1;
    cdq(l,mid);
    cdq(mid+1,r);
    merge(l,mid,r);
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
        if(!s[val[i]].empty()){
            auto last_pos = s[val[i]].end();
            last_pos--; // 移动到最后一个元素
            nums[++cnt] = {1, *last_pos, i, 0}; // 添加这对位置的贡献
        }
        s[val[i]].insert(i);
    }
    for(int i=1;i<=m;i++){
        int op,u,v;
        op=read(),u=read(),v=read();
        if(op==1){
            int old_color=val[u];
            auto current_it = s[old_color].find(u); // 找到当前位置的迭代器
            
            // 1. 处理右边的连接（如果有）
            auto next_it = current_it;
            next_it++;
            if (next_it != s[old_color].end()) {
                int next_pos = *next_it;
                // 移除当前节点和下一个节点的连接
                nums[++cnt] = {-1, u, next_pos, 0};
                
                // 如果当前节点不是第一个，还需要处理前一个节点和下一个节点的连接
                if (current_it != s[old_color].begin()) {
                    auto prev_it = current_it;
                    prev_it--;
                    int prev_pos = *prev_it;
                    nums[++cnt] = {1, prev_pos, next_pos, 0}; // 恢复被破坏的连接
                }
            }
            
            // 2. 处理左边的连接（如果有）
            if (current_it != s[old_color].begin()) {
                auto prev_it = current_it;
                prev_it--;
                int prev_pos = *prev_it;
                nums[++cnt] = {-1, prev_pos, u, 0}; // 移除前一个节点和当前节点的连接
            }
            
            // 从原颜色的集合中移除当前节点
            s[old_color].erase(current_it);
            
            // 3. 更新颜色并添加新连接
            val[u] = v; // 修改颜色
            auto [new_it, inserted] = s[v].insert(u); // 插入新位置
            
            // 处理新颜色的左边连接
            if (new_it != s[v].begin()) {
                auto left_it = new_it;
                left_it--;
                int left_pos = *left_it;
                nums[++cnt] = {1, left_pos, u, 0}; // 添加新连接
            }
            
            // 处理新颜色的右边连接
            auto right_it = new_it;
            right_it++;
            if (right_it != s[v].end()) {
                int right_pos = *right_it;
                nums[++cnt] = {1, u, right_pos, 0}; // 添加新连接
                
                // 如果左边有节点，还需要调整
                if (new_it != s[v].begin()) {
                    auto left_it = new_it;
                    left_it--;
                    int left_pos = *left_it;
                    nums[++cnt] = {-1, left_pos, right_pos, 0}; // 移除旧的长连接
                }
            }
            
            ans[i] = -1; // 标记这不是查询操作
        }
        else{
            nums[++cnt]={0,u,v,i};
        }
    }
    cdq(1,cnt);
    for(int i=1;i<=m;i++){
        if(ans[i]!=-1){
            printf("%lld\n",ans[i]);
        }
    }
    return 0;
}