#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;
const int MAXH = 20;
const int INF = 1e18;

int n;
int val[MAXN];

int edge[MAXN];
int dis[MAXN];
int dep[MAXN];

int dp[MAXN][MAXH][2];

void compute(){
    for(int u=n;u>=1;u--){
        int lson=u<<1;
        int rson=lson|1;

        for(int k=1;k<=dep[u]+1;k++){
            int anc=u>>k;

            // 第 k 级祖先的另一个儿子
            int bro=(u>>(k-1))^1;

            // 叶子节点
            if(lson>n){
                int d=dis[u]-dis[anc];

                // 点完 u 后去第 k 级祖先
                dp[u][k][0]=d*val[anc];

                // 点完 u 后去第 k 级祖先的另一个儿子
                if(bro==0){
                    dp[u][k][1]=0;
                }
                else if(bro<=n){
                    dp[u][k][1]=(d+edge[bro])*val[bro];
                }
                else{
                    dp[u][k][1]=INF;
                }
            }

            // 只有左儿子
            else if(rson>n){
                int enter=edge[lson]*val[lson];

                dp[u][k][0]=enter+dp[lson][k+1][0];
                dp[u][k][1]=enter+dp[lson][k+1][1];
            }

            // 有两个儿子
            else{
                int enterl=edge[lson]*val[lson];
                int enterr=edge[rson]*val[rson];

                // 最终去祖先
                dp[u][k][0]=min(
                    enterl+dp[lson][1][1]+dp[rson][k+1][0],
                    enterr+dp[rson][1][1]+dp[lson][k+1][0]
                );

                // 最终去祖先的另一个儿子
                dp[u][k][1]=min(
                    enterl+dp[lson][1][1]+dp[rson][k+1][1],
                    enterr+dp[rson][1][1]+dp[lson][k+1][1]
                );
            }
        }
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>val[i];
    }

    for(int i=2;i<=n;i++){
        cin>>edge[i];
        dep[i]=dep[i>>1]+1;
        dis[i]=dis[i>>1]+edge[i];
    }

    compute();

    int ans=INF;
    for(int u=1;u<=n;u++){
        int temp=dp[u][1][0];
        int cur=u;
        while(cur!=1){
            int fa=cur>>1;
            int bro=cur^1;
            if(bro<=n){
                temp+=edge[bro]*val[bro];
                temp+=dp[bro][2][0];
            }
            else{
                int grandfa=fa>>1;
                temp+=edge[fa]*val[grandfa];
            }
            cur=fa;
        }
        ans=min(ans,temp);
    }
    cout<<ans<<endl;
    return 0;
}