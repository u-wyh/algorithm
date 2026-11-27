// https://www.luogu.com.cn/problem/P3452
// 题意：输入员工数 n 和已知相互存有电话号码的员工对数 m，
// 以及 m 对互存号码的员工 (a_i, b_i)。
// 要将员工分到尽量多的办公楼中，
// 要求在任意两栋不同办公楼工作的每对员工都必须相互存有对方电话号码。
// 第一行输出最多能租用的办公楼数 t，
// 第二行按非降序输出 t 栋楼各自的员工数（任意合法方案）。
// 数据范围：2 <= n <= 10^5，1 <= m <= 2*10^6，
// 1 <= a_i < b_i <= n，无重复信息。
// 算法标签：并查集、排序
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 2e6+5;

int n,m;
int fa[MAXN];
int sz[MAXN];
int ans[MAXN];
struct node{
    int u,v;
}nums[MAXM];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}


inline int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

inline void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        sz[fx]+=sz[fy];
        fa[fy]=fx;
    }
}

inline bool cmp(node a,node b){
    return a.u==b.u?a.v<b.v:a.u<b.u;
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        fa[i]=i;
        sz[i]=1;
    }
    vector<int>vec[n+1];
    for(int i=1,u,v;i<=m;i++){
        nums[i].u=read();
        nums[i].v=read();
        if(nums[i].u>nums[i].v){
            int temp=nums[i].u;
            nums[i].u=nums[i].v;
            nums[i].v=temp;
        }
//        vec[u].push_back(v);
//        vec[v].push_back(u);
    }
    sort(nums+1,nums+m+1,cmp);
//    for(int i=1;i<=n;i++){
//        sort(vec[i].begin(),vec[i].end());
//    }
    for(int i=1;i<=m;i++){
        vec[nums[i].u].push_back(nums[i].v);
        vec[nums[i].v].push_back(nums[i].u);
    }
    for(int i=1;i<=n;i++){
        int last=i+1;
        for(int j=0;j<vec[i].size();j++){
            while(last<vec[i][j]){
                un(i,last);
                last++;
            }
            last=vec[i][j]+1;
        }
    }
    int cnt=0;
    for(int i=1;i<=n;i++){
        if(fa[i]==i){
            cnt++;
            ans[cnt]=sz[i];
        }
    }
    sort(ans+1,ans+cnt+1);
    cout<<cnt<<endl;
    for(int i=1;i<=cnt;i++){
        cout<<ans[i]<<' ';
    }
    return 0;
}
