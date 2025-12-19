#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;
const int MAXT = 10*MAXN;
const int MAXM = 31;
const int MOD = 1e9+7;

int n,m,k;

int nums[MAXM];

int val[MAXN];
bool vis[MAXN];

int tree[MAXT][2];

int cnt=1;
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];

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

void addedge(int u,int v,int w){
    Next[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void insert(int num){
    //cout<<"  "<<num<<endl;
    int cur = 1;
    for (int i = 30, path; i >= 0; i--) {
        path = (num >> i) & 1;
        if (tree[cur][path] == 0) {
            tree[cur][path] = ++cnt;
        }
        cur = tree[cur][path];
    }
}

void dfs1(int u,int fa,int value){
    vis[u]=true;
    val[u]=value;
    insert(value);
    for(int i=head[u];i;i=Next[i]){
        int v=to[i],w=weight[i];
        if(v==fa){
            continue;
        }
        if(vis[v]){
            if((value^w)!=val[v]){
                cout<<0<<endl;
                exit(0);
            }
            continue;
        }
        dfs1(v,u,value^w);
    }
}

int dfs2(int u,int pos){
    if(pos==-1){
        return 1;
    }
    int ans=0;
    if(nums[pos]==0){
        if(tree[u][0]&&tree[u][1]){
            ans=0;
        }
        else if(tree[u][0]){
            ans=dfs2(tree[u][0],pos-1);
        }
        else {
            ans=dfs2(tree[u][1],pos-1);
        }
    }
    else{
        if(tree[u][0]&&tree[u][1]){
            ans=dfs2(tree[u][0],pos-1)+dfs2(tree[u][1],pos-1);
        }
        else if(tree[u][0]){
            ans=(1<<pos)+dfs2(tree[u][0],pos-1);
        }
        else {
            ans=(1<<pos)+dfs2(tree[u][1],pos-1);
        }
    }
	return ans%MOD;
}

int main()
{
    n=read(),m=read(),k=read();
    for(int i=30;i>=0;i--){
        if(k&(1<<i)){
            nums[i]=1;
        }
    }
    for(int i=1;i<=m;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        addedge(u,v,w);
        addedge(v,u,w);
    }
    cnt=1;
    long long ans=1;
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            for(int i=1;i<=cnt;i++){
                tree[i][0]=tree[i][1]=0;
            }
            cnt=1;
            dfs1(i,0,0);
            ans*=dfs2(1,30);
            ans%=MOD;
        }
    }
    cout<<ans<<endl;
    return 0;
}
