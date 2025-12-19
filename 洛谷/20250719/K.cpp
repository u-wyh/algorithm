#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n;
int fa[MAXN];
int pri[MAXN];
int ans[MAXN];

struct node{
    int u,v,a,b;
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

void prepare(){
    for(int i=1;i<=n;i++){
        ans[i]=0;
        fa[i]=i;
    }
}

bool cmp(node a,node b){
    return (a.a==b.a)?(a.b>b.b):(a.a>b.a);
}

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

int main()
{
    int T;
    T=read();
    while(T--){
        n=read();
        prepare();
        for(int i=1;i<=n;i++){
            int u=read();
            pri[u]=i;
        }
        for(int i=1;i<n;i++){
            nums[i].u=read(),nums[i].v=read();
            if(pri[nums[i].u]>pri[nums[i].v]){
                swap(nums[i].u,nums[i].v);
            }
            nums[i].a=pri[nums[i].u];
            nums[i].b=pri[nums[i].v];
        }
        sort(nums+1,nums+n,cmp);
        for(int i=1;i<n;i++){
            int fu=find(nums[i].u),fv=find(nums[i].v);
            ans[fv]=fu;
            fa[fv]=fu;
        }
        for(int i=1;i<=n;i++){
            cout<<ans[i]<<' ';
        }
        cout<<endl;
    }
    return 0;
}