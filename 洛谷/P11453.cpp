#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;
const int MAXM = MAXN*6;

int n,m;
bool ok[MAXN];
int arr[MAXN];
int tot=0;
int tmp[MAXN*3];

int x[MAXN],y[MAXN],t[MAXN];

int dis[MAXN];
bool vis[MAXN];
queue<int>q;

int cnt=1;
int head[MAXM];
int nxt[MAXM];
int to[MAXM];
int weight[MAXM];

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

void prepare(){
    cnt=1;
    for(int i=0;i<=tot;i++){
        head[i]=0;
        ok[i]=false;
    }
}

int find(int val){
    int l=1,r=tot,ans;
    while(l<=r){
        int mid=(l+r)/2;
        if(tmp[mid]>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

inline void addedge(int u,int v,int w){
    // cout<<u<<' '<<v<<' '<<w<<endl;
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void spfa(){
    for(int i=1;i<=tot;i++){
        dis[i]=INT_MAX;
        vis[i]=false;
    }
    dis[tot]=0;
    vis[tot]=true;
    q.push(tot);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        vis[u]=false;
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int w=weight[i];
            if(w+dis[u]<dis[v]){
                dis[v]=w+dis[u];
                if(!vis[v]){
                    q.push(v);
                    vis[v]=true;
                }
            }
        }
    }
}

int main()
{
    int T;
    T=read();
    while(T--){
        n=read(),m=read();
        tot=0;
        tmp[++tot]=-1e9-1;
        for(int i=1;i<=n;i++){
            arr[i]=read();
            tmp[++tot]=arr[i];
        }
        for(int i=1;i<=m;i++){
            x[i]=read(),y[i]=read(),t[i]=read();
            tmp[++tot]=x[i],tmp[++tot]=y[i];
        }
        sort(tmp+1,tmp+tot+1);
        int k=tot;
        tot=0;
        tmp[0]=tmp[1]-1;
        for(int i=1;i<=k;i++){
            if(tmp[i]!=tmp[i-1]){
                tmp[++tot]=tmp[i];
            }
        }
        prepare();
        for(int i=1;i<=n;i++){
            arr[i]=find(arr[i]);
            addedge(arr[i]-1,arr[i],1);
            addedge(arr[i],arr[i]-1,0);
            ok[arr[i]]=1;
        }
        for(int i=2;i<=tot;i++){
            if(!ok[i]){
                addedge(i,i-1,0);
                addedge(i-1,i,0);
            }
        }
        for(int i=1;i<=m;i++){
            x[i]=find(x[i]),y[i]=find(y[i]);
            addedge(y[i],x[i]-1,-t[i]);
        }
        spfa();
        cout<<(n-(dis[tot]-dis[1]))<<endl;
    }
    return 0;
}