// https://www.luogu.com.cn/problem/P2792
// 题意：输入商品总数 n、每种商品的原价 c_i（实数）与所需数量 m_i，以及 k 种优惠方案 (A, B, P)。
// 若已购买过至少一件商品 A，之后就能以优惠价 P 元/件购买任意数量的商品 B；不允许购买任何不必要的商品。
// 合理安排购买顺序，使买齐所有所需商品的总花费最小。
// 输出一个保留两位小数的实数，表示最少总花费。
// 数据范围：对于 100% 的数据，1 <= n <= 50，0 < c_i <= 1000，0 <= m_i <= 100，1 <= k <= 500
// 1 <= A, B <= n，0 <= P < 1000（所有价格不出现分）。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 55;
const int MAXM = 1005;

int n,k;
double price[MAXN];
int need[MAXN];
double lowprice[MAXN];

int nodeid[MAXN];
int nodecnt;

struct Edge{
    int u,v;
    double w;
};
Edge edge[MAXM];
int edgecnt;

double in[MAXN];
int pre[MAXN];
int id[MAXN];
int vis[MAXN];

void prepare(){
    for(int i=1;i<=nodecnt;i++){
        pre[i]=0;
        in[i]=INT_MAX;
        id[i]=0;
        vis[i]=0;
    }
}

double zhuliu(){
    double res=0;

    while(true){
        prepare();
        for(int i=1;i<=edgecnt;i++){
            int u=edge[i].u;
            int v=edge[i].v;
            double w=edge[i].w;
            if(u!=v&&w<in[v]){
                in[v]=w;
                pre[v]=u;
            }
        }

        for(int i=1;i<=nodecnt;i++){
            if(i==nodecnt){
                continue;
            }
            res+=in[i];
        }

        int cnt=0;
        int idx=0;

        for(int i=1;i<nodecnt;i++){
            if(vis[i]){
                continue;
            }
            idx++;
            int v=i;
            while(vis[v]!=idx&&!id[v]&&v!=nodecnt){
                vis[v]=idx;
                v=pre[v];
            }
            if(v!=nodecnt&&!id[v]){
                cnt++;
                id[v]=cnt;
                for(int u=pre[v];u!=v;u=pre[u]){
                    id[u]=cnt;
                }
            }
        }

        if(cnt==0){
            break;
        }

        for(int i=1;i<=nodecnt;i++){
            if(!id[i]){
                id[i]=++cnt;
            }
        }

        for(int i=1;i<=edgecnt;i++){
            if(edge[i].u!=edge[i].v){
                edge[i].w-=in[edge[i].v];
            }
            edge[i].u=id[edge[i].u];
            edge[i].v=id[edge[i].v];
        }

        nodecnt=cnt;
    }

    return res;
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%lf %d",&price[i],&need[i]);
        lowprice[i]=price[i];
    }
    scanf("%d",&k);
    for(int i=1;i<=k;i++){
        int a,b;
        double p;
        scanf("%d %d %lf",&a,&b,&p);
        if(need[b]&&need[a]){
            lowprice[b]=min(lowprice[b],p);
            edge[++edgecnt]={a,b,p};
        }
    }
    for(int i=1;i<=n;i++){
        if(need[i]){
            edge[++edgecnt]={n+1,i,price[i]};
        }
    }

    for(int i=1;i<=n;i++){
        if(need[i]){
            nodeid[i]=++nodecnt;
        }
    }
    nodeid[n+1]=++nodecnt;

    for(int i=1;i<=edgecnt;i++){
        edge[i].u=nodeid[edge[i].u];
        edge[i].v=nodeid[edge[i].v];
    }

    double ans=zhuliu();
    for(int i=1;i<=n;i++){
        if(need[i]){
            ans+=((need[i]-1)*lowprice[i]);
        }
    }
    printf("%.2lf",ans);
    return 0;
}