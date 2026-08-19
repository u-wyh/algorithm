#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;

int n;
int arr[MAXN];
long long ans;

struct node{
    int l;
    int r;
    int lt;
    int rt;
    int len;
};
node nums[MAXN<<1];
int cntn;

int fa[MAXN<<1];
int sz[MAXN<<1];

int head[MAXN<<1];
int nxt[MAXN<<2];
int to[MAXN<<2];
int cntg=1;

int tmp[2][MAXN];
int len[2];

int a[MAXN<<1];
int cnta;

void addedge(int u,int v){
    cout<<"   "<<u<<' '<<v<<endl;
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        fa[fx]=fy;
        sz[fy]+=sz[fx];
        sz[fx]=1;
        nums[fy].l=min(nums[fx].l,nums[fy].l);
        nums[fy].r=max(nums[fx].r,nums[fy].r);
        nums[fy].lt=min(nums[fx].lt,nums[fy].lt);
        nums[fy].rt=max(nums[fx].rt,nums[fy].rt);
        a[++cnta]=fx;
        a[++cnta]=fy;
    }
}

int help[MAXN<<2][2];
int cnth;

void compute1(int now,int nxt){
    len[nxt]=0;
    cnta=0;
    cnth=0;
    for(int i=1;i<=len[now];i++){
        int x=find(tmp[now][i]);
        int y=find(nums[x].lt);
        if(y!=0&&(abs(nums[x].l-nums[y].r)==1||abs(nums[y].l-nums[x].r)==1)){
            help[++cnth][0]=x;
            help[cnth][1]=y;
        }
        y=find(nums[x].rt);
        if(y!=0&&(abs(nums[x].l-nums[y].r)==1||abs(nums[y].l-nums[x].r)==1)){
            help[++cnth][0]=x;
            help[cnth][1]=y;
        }
    }
    for(int i=1;i<=cnth;i++){
        un(help[i][0],help[i][1]);
    }
    for(int i=1;i<=len[now];i++){
        int x=find(tmp[now][i]);
        if(sz[x]>1){
            ++cntn;
            sz[x]=1;
            fa[x]=cntn;
            fa[cntn]=cntn;
            sz[cntn]=1;
            nums[cntn]=nums[x];
            nums[cntn].len=nums[cntn].r-nums[cntn].l;
            tmp[nxt][++len[nxt]]=cntn;
        }
    }

    if(cnta==0){
        return ;
    }
    sort(a+1,a+cnta+1);
    int len1=1;
    for(int i=2;i<=cnta;i++){
        if(a[i]!=a[i-1]){
            a[++len1]=a[i];
        }
    }

    for(int i=1;i<=len1;i++){
        int f=find(a[i]);
        addedge(f,a[i]);
        // nums[f].l=min(nums[f].l,nums[a[i]].l);
        // nums[f].r=max(nums[f].r,nums[a[i]].r);
        // nums[f].lt=min(nums[f].lt,nums[a[i]].lt);
        // nums[f].rt=max(nums[f].rt,nums[a[i]].rt);
        // nums[f].len=nums[f].r-nums[f].l;
    }
}

void compute(){
    cntn=n;
    for(int i=1;i<=n;i++){
        fa[i]=i;
        sz[i]=1;

        nums[i].l=arr[i];
        nums[i].r=arr[i];
        nums[i].lt=i-1;
        nums[i].rt=i+1;
        nums[i].len=0;
    }

    int now=0;
    len[now]=0;
    for(int i=1;i<=n;i++){
        tmp[now][++len[now]]=i;
    }
    while(len[now]){
        int nxt=now^1;
        compute1(now,nxt);
        now=nxt;
    }
}

int dep[MAXN];

void dfs(int u,int d){
    dep[d]=max(dep[d],nums[u].len);
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs(v,d+1);
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        arr[x]=i;
    }

    compute();

    int f=find(1);
    for(int i=2;i<=n;i++){
        if(find(i)!=f){
            cout<<-1<<endl;
            return 0;
        }
    }

    dfs(f,1);
    for(int i=1;i<=n+1;i++){
        // cout<<i<<"  "<<dep[i]<<endl;
        ans+=dep[i];
    }
    cout<<ans<<endl;
    return 0;
}
/*
7
7 1 4 2 3 5 6

3
2 1 3

5
1 2 3 5 4 
*/