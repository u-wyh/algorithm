#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n;
int pos[MAXN];
struct node{
    int pos,l,r;
}nums[MAXN];

int in[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

int dfn[MAXN];
int low[MAXN];
int dfncnt;
int st[MAXN];
int top;
bool instack[MAXN];
int col[MAXN];
int color;

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

//找到第一个大于等于val的位置
int find1(int val){
    int l=1,r=n,ans=1;
    while(l<=r){
        int mid=(l+r)/2;
        if(pos[mid]>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

//找到第一个大于val的位置  如果没有就是n+1
int find2(int val){
    int l=1,r=n,ans=n+1;
    while(l<=r){
        int mid=(l+r)/2;
        if(pos[mid]>val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

inline void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void tarjan(int u){
    low[u]=dfn[u]=++dfncnt;
    instack[u]=true;
    st[++top]=u;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(instack[v]){
            low[u]=min(low[u],dfn[v]);
        }
    }
    if(low[u]==dfn[u]){
        col[u]=++color;
        instack[u]=false;
        while(st[top]!=u){
            instack[st[top]]=false;
            col[st[top--]]=color;
        }
        top--;
    }
}

bool cmp(node a,node b){
    return a.pos<b.pos;
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        pos[i]=read();
        nums[i].pos=pos[i];
        int d1,d2;
        d1=read(),d2=read();
        nums[i].l=pos[i]-d1;
        nums[i].r=pos[i]+d2;
    }
    sort(pos+1,pos+n+1);
    sort(nums+1,nums+n+1,cmp);
    for(int i=1;i<=n;i++){
        nums[i].l=find1(nums[i].l);
        nums[i].r=find2(nums[i].r)-1;
        // cout<<i<<": "<<nums[i].l<<' '<<nums[i].r<<endl;
    }
    int l=n+1;
    for(int i=n;i>=1;i--){
        int vl=nums[i].l,vr=nums[i].r;
        if(vl>=l){
            continue;
        }
        vr=min(l-1,vr);
        for(int j=vl;j<=vr;j++){
            addedge(i,j);
        }
        l=vl;
    }

    int r=0;
    for(int i=1;i<=n;i++){
        int vl=nums[i].l,vr=nums[i].r;
        if(vr<=r){
            continue;
        }
        vl=max(vl,r+1);
        for(int j=vl;j<=vr;j++){
            addedge(i,j);
        }
        r=vr;
    }

    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }
    for(int u=1;u<=n;u++){
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(col[u]!=col[v]){
                in[col[v]]++;
            }
        }
    }
    int ans=0;
    for(int i=1;i<=color;i++){
        if(in[i]==0){
            ans++;
        }
    }
    cout<<ans<<endl;
    return 0;
}