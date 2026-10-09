#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n;
int arr[3][MAXN];

struct node{
    int a,b,c;
};
node nums[MAXN];
int fa[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cntg=1;

int dfn[MAXN];
int low[MAXN];
int st[MAXN];
bool insta[MAXN];
int top;
int color;
int dfncnt;
int col[MAXN];

void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void tarjan(int x){
    dfn[x]=++dfncnt;
    low[x]=dfncnt;
    st[++top]=x;
    insta[x]=true;
    for(int i=head[x];i;i=nxt[i]){
        int v=to[i];
        if(!dfn[v]){
            tarjan(v);
            low[x]=min(low[x],low[v]);
        }
        else if(insta[v]){
            low[x]=min(low[x],dfn[v]);
        }
    }
    if(dfn[x]==low[x]){
        col[x]=++color;
        while(st[top]!=x){
            col[st[top]]=color;
            insta[st[top]]=false;
            top--;
        }
        insta[x]=false;
        top--;
    }
}

void compute(int a,int b,int op){
    cntg=1;
    color=0;
    dfncnt=0;
    top=0;
    for(int i=1;i<=n;i++){
        head[i]=0;
        dfn[i]=low[i]=col[i]=0;
        insta[i]=false;
    }

    for(int i=1;i<n;i++){
        addedge(arr[a][i],arr[a][i+1]);
        addedge(arr[b][i],arr[b][i+1]);
    }

    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }

    for(int i=1;i<=n;i++){
        int c=col[i];
        if(op==1){
            nums[i].a=c;
        }
        else if(op==2){
            nums[i].b=c;
        }
        else{
            nums[i].c=c;
        }
    }
}

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

bool cmp(node &a,node &b){
    if(a.a!=b.a){
        return a.a<b.a;
    }
    if(a.b!=b.b){
        return a.b<b.b;
    }
    return a.c<b.c;
}

void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        fa[fx]=fy;
    }
}

void solve(){
    cin>>n;
    for(int j=0;j<3;j++){
        for(int i=1;i<=n;i++){
            cin>>arr[j][i];
        }
    }

    compute(0,1,1);
    compute(0,2,2);
    compute(2,1,3);

    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    sort(nums+1,nums+n+1,cmp);
    for(int i=2;i<=n;i++){
        if((nums[i].a==nums[i-1].a)&&(nums[i].b==nums[i-1].b)&&(nums[i].c==nums[i-1].c)){
            un(i,i-1);
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        if(find(i)==i){
            ans++;
        }
    }
    cout<<ans<<endl;
}

int main()
{
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}