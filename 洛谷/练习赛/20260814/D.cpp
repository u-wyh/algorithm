#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXP = 22;

int n,m;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cntg=1;

int dep[MAXN];
int dfncnt;
int dfn[MAXN];
int stjump[MAXN][MAXP];

int headq[MAXN];
int nxtq[MAXN];
int idq[MAXN];
int tq[MAXN];
int cntq=1;

struct node{
    int id;
    int u;
    int tim;
};
node nums[MAXN];
int cntn;

bool ans[MAXN];

int headv[MAXN];
int nxtv[MAXN];
int tov[MAXN];
int cntv=1;

// 重要点数组
int arr[MAXN];
int pointcnt[MAXN];
int point[MAXN];
int tmp[MAXN<<1];

void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void addedgeq(int u,int id,int t){
    nxtq[cntq]=headq[u];
    idq[cntq]=id;
    tq[cntq]=t;
    headq[u]=cntq++;
}

void dfs(int u,int f){
    dfn[u]=++dfncnt;
    dep[u]=dep[f]+1;
    stjump[u][0] = f;
    for (int p = 1; p < MAXP; p++) {
        stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=f){
            dfs(v,u);
        }
    }
    for(int i=headq[u];i;i=nxtq[i]){
        int id=idq[i];
        int t=tq[i];
        nums[++cntn]={id,u,t+dep[u]};
    }
}

bool cmp1(node &a,node &b){
    if(a.tim!=b.tim){
        return a.tim<b.tim;
    }
    return a.u<b.u;
}

bool cmp2(int a,int b){
    return dfn[a]<dfn[b];
}

int getLca(int a, int b) {
    if (dep[a] < dep[b]) {
        swap(a, b);
    }
    for (int p = MAXP - 1; p >= 0; p--) {
        if (dep[stjump[a][p]] >= dep[b]) a = stjump[a][p];
    }
    if (a == b) {
        return a;
    }
    for (int p = MAXP - 1; p >= 0; p--) {
        if (stjump[a][p] != stjump[b][p]) {
            a = stjump[a][p];
            b = stjump[b][p];
        }
    }
    return stjump[a][0];
}

void addedgev(int u,int v){
    nxtv[cntv]=headv[u];
    tov[cntv]=v;
    headv[u]=cntv++;
}

void dfs1(int u){
    for(int i=headv[u];i;i=nxtv[i]){
        int v=tov[i];
        dfs1(v);
        if(pointcnt[v]==1){
            pointcnt[u]++;
            point[u]=point[v];
        }
    }
}

void compute(int l,int r){
    if(r-l==0){
        ans[nums[l].id]=true;
        return ;
    }

    int len1=0;
    for(int i=l;i<=r;i++){
        int u=nums[i].u;
        arr[++len1]=u;
        pointcnt[u]++;
        point[u]=nums[i].id;
    }

    int len2=1;
    sort(arr+1,arr+len1+1,cmp2);
    for(int i=2;i<=len1;i++){
        if(arr[i]!=arr[i-1]){
            arr[++len2]=arr[i];
        }
    }

    int len=0;
    for(int i=1;i<len2;i++){
        tmp[++len]=arr[i];
        tmp[++len]=getLca(arr[i],arr[i+1]);
    }
    tmp[++len]=arr[len2];
    sort(tmp+1,tmp+len+1,cmp2);

    int unique = 1;
    for (int i = 2; i <= len; i++) {
        if (tmp[unique] != tmp[i]) {
            tmp[++unique] = tmp[i];
        }
    }

    cntv=1;
    // 清空用到的head数组
    for (int i = 1; i <= unique; i++) {
        headv[tmp[i]] = 0;
    }
    for(int i=1;i<unique;i++){
        addedgev(getLca(tmp[i],tmp[i+1]),tmp[i+1]);
    }
    dfs1(tmp[1]);
    if(pointcnt[tmp[1]]==1){
        ans[point[tmp[1]]]=true;
    }

    for(int i=1;i<=unique;i++){
        pointcnt[tmp[i]]=0;
    }
}

void compute(){
    sort(nums+1,nums+m+1,cmp1);
    int l=1,r=0;
    while(l<=m){
        while((r+1)<=m&&nums[r+1].tim==nums[l].tim){
            r++;
        }
        compute(l,r);
        l=r+1;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }
    for(int i=1;i<=m;i++){
        int u,t;
        cin>>u>>t;
        addedgeq(u,i,t);
    }
    dfs(1,0);

    compute();

    for(int i=1;i<=m;i++){
        if(ans[i]){
            cout<<1;
        }
        else{
            cout<<0;
        }
    }
    return 0;
}