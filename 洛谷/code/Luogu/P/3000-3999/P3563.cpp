#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 250005;

int n;
int centroid;

long long ans;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cntg=1;

int sz[MAXN];

inline void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void dfs(int u,int fa){
    sz[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa){
            dfs(v,u);
            sz[u]+=sz[v];
        }
    }
}

int findcentroid(){
    dfs(1,0);
    int half=n>>1;
    bool find=false;
    int u=1,f=0;
    while(!find){
        find=true;
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(v!=f&&sz[v]>half){
                f=u;
                u=v;
                find=false;
                break;
            }
        }
    }
    return u;
}

void dfs1(int u,int fa){
    sz[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa){
            dfs1(v,u);
            sz[u]+=sz[v];
        }
    }
    ans+=sz[u]-1;
}

int szcnt[MAXN];
int nums[MAXN];
int len;
bool f[MAXN];

void compute(){
    for(int i=head[centroid];i;i=nxt[i]){
        int v=to[i];
        szcnt[sz[v]]++;
    }
    for(int i=1;i<n;i++){
        if(szcnt[i]){
            int val=szcnt[i];

            for(int b=1;val>0;b<<=1){
                int t=min(b,val);
                nums[++len]=t*i;
                val-=b;
            }
        }
    }

    sort(nums+1,nums+len+1);
    int now=0;
    int limit=(n-1)/2;
    f[0]=true;
    for(int i=1;i<=len;i++){
        int val=nums[i];

        int up=min(limit,now+val);
        for(int j=up;j>=val;j--){
            if(f[j-val]){
                f[j]=true;
            }
        }
        now=up;
    }

    int x=limit;
    while(x>0&&!f[x]){
        x--;
    }

    ans+=1ll*x*(n-1-x);
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }

    centroid=findcentroid();

    dfs1(centroid,0);

    compute();

    cout<<(n-1)<<' '<<ans<<endl;
    return 0;
}