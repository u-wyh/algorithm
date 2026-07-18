// 异或关系
// 一共n个数，编号0 ~ n-1，实现如下三种类型的操作，一共调用m次
// I x v        : 声明 第x个数 = v
// I x y v      : 声明 第x个数 ^ 第y个数 = v
// Q k a1 .. ak : 查询 一共k个数，编号为a1 .. ak，这些数字异或起来的值是多少
// 对每个Q的操作打印答案，如果根据之前的声明无法推出答案，打印"I don't know."
// 如果处理到第s条声明，发现了矛盾，打印"The first s facts are conflicting."
// 注意只有声明操作出现，s才会增加，查询操作不占用声明操作的计数
// 发现矛盾之后，所有的操作都不再处理，更多的细节可以打开测试链接查看题目
// 1 <= n <= 20000    1 <= m <= 40000    1 <= k <= 15
// 测试链接 : https://acm.hdu.edu.cn/showproblem.php?pid=3234
// 测试链接 : https://www.luogu.com.cn/problem/UVA12232
// 测试链接 : https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=244&page=show_problem&problem=3384
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
//这道题的一个难度是输入数据很恶心
//除此之外  还需要增加一个虚点  绝对顶点永远不会挂着其他点的下面   它的值就是0
//我们在合并集合的时候也需要注意，不能将绝对顶点当场普通点处理
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e4+5;
const int MAXK = 20;

int t,n,m;
bool flag;//表示是否出现了冲突
int cnti;//表示现在到了第几个操作
int fa[MAXN];
int dis[MAXN];//与头节点的异或值

//收集查询信息
int nums[MAXK];
int fas[MAXK];

void prepare(){
    flag=false;
    cnti=0;
    for(int i=0;i<=n;i++){
        //节点n是绝对顶点
        fa[i]=i;
        dis[i]=0;
    }
}

int find(int i){
    if(i!=fa[i]){
        int tmp=fa[i];
        fa[i]=find(tmp);
        dis[i]^=dis[tmp];
    }
    return fa[i];
}

//处理i类型的操作  返回这个操作是否合法
bool opi(int l,int r,int v){
    cnti++;
    int lf=find(l);
    int rf=find(r);
    if(lf==rf){
        if((dis[l]^dis[r])!=v){
            flag=true;
            return false;
        }
    }
    else{
        if(lf==n){
            //绝对顶点不能做孩子节点
            swap(lf,rf);
        }
        fa[lf]=rf;
        dis[lf]=dis[l]^dis[r]^v;
    }
    return true;
}

//处理q类型的操作
int opq(int k){
    int ans=0;
    for(int i=1;i<=k;i++){
        int f=find(nums[i]);
        ans^=dis[nums[i]];
        fas[i]=f;
    }
    sort(fas+1,fas+k+1);
    for (int l = 1, r; l <= k; l = r + 1) {
        r = l;
        while (r + 1 <= k && fas[r + 1] == fas[l]) {
            r++;
        }
        int cnt = r - l + 1;
        if (cnt % 2 == 1 && fas[l] != n) {
            //表示一定无法得知答案
            return -1;
        }
    }
    return ans;
}

int main()
{
    t=0;
    string line;
    while(getline(cin,line)){
        istringstream iss(line);
        if(!(iss>>n>>m)){
            break;
        }
        if(n==0&&m==0){
            break;
        }
        prepare();
        cout << "Case " << ++t << ":" << endl;
        for (int i = 0; i < m; ++i) {
            getline(cin, line);
            istringstream iss_op(line);
            string op;
            iss_op >> op;
            if (op == "I") {
                vector<int> params;
                int x;
                while (iss_op >> x) {
                    params.push_back(x);
                }
                if (flag) 
                    continue;//如果已经不合法了   那么就把剩下的数据读入就好了
                int l, r, v;
                if (params.size() == 2) {
                    l = params[0];
                    r = n;//和绝对顶点相连
                    v = params[1];
                } else if (params.size() == 3) {
                    l = params[0];
                    r = params[1];
                    v = params[2];
                } else {
                    continue;
                }
                if (!opi(l, r, v)) {
                    cout << "The first " << cnti << " facts are conflicting." << endl;
                }
            } else if (op == "Q") {
                int k;
                iss_op >> k;
                for (int j = 1; j <= k; ++j) {
                    iss_op >> nums[j];
                }
                if (flag) continue;
                int ans = opq(k);
                if (ans == -1) {
                    cout << "I don't know." << endl;
                } else {
                    cout << ans << endl;
                }
            }
        }
        cout << endl;
    }
    return 0;
}
/*
2 6
I 0 1 3
Q 1 0
Q 2 1 0
I 0 2
Q 1 1
Q 1 0
3 3
I 0 1 6 
I 0 2 2
Q 2 1 2
2 4
I 0 1 7
Q 2 0 1
I 0 1 8
Q 2 0 1
0 0
*/