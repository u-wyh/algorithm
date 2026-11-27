// https://www.luogu.com.cn/problem/P4079
// 题意：多组数据，第一行输入组数 T；
// 每组第一行输入齿轮数 N 和链条数 M，
// 接下来 M 行每行输入 u, v, x, y。
// 表示仅考虑该链条时，
// 齿轮 u 转动 x 圈则齿轮 v 转动 y
// 圈（y 可负表示反向转动，图不一定连通）。
// 每组输出一行 Case #k: Yes 或 No，
// 判断这 N 个齿轮能否同时正常转动（传动比是否自洽）。
// 数据范围：1 <= T <= 32，1 <= N <= 1000，
// 1 <= M <= 10^4，1 <= x, |y| <= 100（x 为正整数
// y 为非零整数）。
//P4079
// 算法标签：带权并查集
#include<bits/stdc++.h>
using namespace std;
const double eps = 1e-10;
const int MAXN = 10005;

int n,m;
int fa[MAXN];
double dis[MAXN];

int find(int x){
    if(x!=fa[x]){
        int tmp=fa[x];
        fa[x]=find(tmp);
        dis[x]*=dis[tmp];
    }
    return fa[x];
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int T;
    cin>>T;
    for(int t=1;t<=T;t++){
        cin>>n>>m;
        bool ans=true;
        for(int i=1;i<=n;i++){
            fa[i]=i;
            dis[i]=1.0;
        }
        for(int i=1;i<=m;i++){
            int u,v;
            double x,y;
            cin>>u>>v>>x>>y;
            int fu=find(u),fv=find(v);
            if(fu!=fv){
                fa[fu]=fv;
                dis[fu]*=(x*dis[v]/(y*dis[u]));
            }
            else{
                //如果他们在一个集合中  那么dis一定要是1
                if(abs(dis[u]/dis[v]-x/y)>eps){
                    ans=false;
                }
            }
        }
        if(ans){
            cout<<"Case #"<<t<<": Yes"<<endl;
        }
        else{
            cout<<"Case #"<<t<<": No"<<endl;
        }
    }
    return 0;
}
