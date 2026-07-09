#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;
const int INF = 1e6+10;

int n;
int aim[MAXN];

int indeg[MAXN];
int in[MAXN];

int dp0[MAXN];
int dp1[MAXN];

int que[MAXN];

int dponcycle(int len){
    if(len==1){
        return dp0[que[1]];
    }

    int f0=dp0[que[1]];
    int f1=-INF;
    for(int i=2;i<=len;i++){
        int u=que[i];
        int nf0=max(f0,f1)+dp0[u];
        int nf1=f0+dp1[u];

        f0=nf0;
        f1=nf1;
    }
    int ans=max(f0,f1);

    f0=-INF;
    f1=dp1[que[1]];
    for(int i=2;i<=len;i++){
        int u=que[i];
        int nf0=max(f0,f1)+dp0[u];
        int nf1=f0+dp1[u];

        f0=nf0;
        f1=nf1;
    }
    ans=max(ans,f0);
    return ans;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>aim[i];
        indeg[aim[i]]++;
        in[aim[i]]++;
    }
    for(int i=1;i<=n;i++){
        dp0[i]=0;
        dp1[i]=1;
    }

    int maxdead=0;
    for(int i=1;i<=n;i++){
        if(indeg[i]>0){
            maxdead++;
        }
    }
    int l=1,r=0;
    for(int i=1;i<=n;i++){
        if(indeg[i]==0){
            que[++r]=i;
        }
    }
    while(l<=r){
        int u=que[l++];
        int v=aim[u];
        dp0[v]+=max(dp0[u],dp1[u]);
        dp1[v]+=dp0[u];

        indeg[v]--;
        if(indeg[v]==0){
            que[++r]=v;
        }
    }

    int maxalive=0;

    for(int i=1;i<=n;i++){
        if(indeg[i]){
            int len=0;
            int x=i;
            que[++len]=x;
            x=aim[x];
            while(x!=i){
                indeg[x]=0;
                que[++len]=x;
                x=aim[x];
            }
            maxalive+=dponcycle(len);
            if(len>1){
                bool ok=true;
                for(int j=1;j<=len;j++){
                    int u=que[j];
                    if(in[u]!=1){
                        ok=false;
                        break;
                    }
                }
                if(ok){
                    maxdead--;
                }
            }
        }
    }
    cout<<(n-maxalive)<<' '<<maxdead<<endl;
    return 0;
}