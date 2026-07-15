#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+7;
const int MAXN = 4e5+5;

int n,m;

int fa[MAXN];
int cnt;
struct node{
    int p,val;
};
node nums[MAXN];

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

node add(node a,node b){
    return {a.p*b.p%MOD,(a.val*b.p+b.val)%MOD};
}

int find(int x){
    if(x==fa[x]){
        return x;
    }
    int f=find(fa[x]);
    nums[x]=add(nums[x],nums[fa[x]]);
    fa[x]=f;
    return f;
}

signed main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        fa[i]=i;
        nums[i]={1,0};
    }
    cnt=n;
    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();
        int fx=find(u);
        int fy=find(v);
        if(fx!=fy){
            node xval=nums[u];
            node yval=nums[v];
            node tmp={10,i};

            nums[fa[u]]=add(tmp,yval);
            nums[fa[v]]=add(tmp,xval);

            fa[fa[u]]=fa[fa[v]]=++cnt;
            fa[cnt]=cnt;
            nums[cnt]={1,0};
        }
    }

    for(int i=1;i<=n;i++){
        find(i);
        cout<<nums[i].val<<endl;
    }
    return 0;
}