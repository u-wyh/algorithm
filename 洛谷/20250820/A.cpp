#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;

int n,m;
int nums[MAXN];
int tree[MAXN];

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

inline int lowbit(int x){
    return x&-x;
}

void add(int x,int v){
    while(x<=n){
        tree[x]+=v;
        x+=lowbit(x);
    }
}

int query(int x){
    int ans=0;
    while(x){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}

signed main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++){
        nums[i]=read();
    }
    long long ans=0;
    for(int i=1;i<m;i++){
        int u=nums[i],v=nums[i+1];
        if(u>v){
            swap(u,v);
        }
        int l=v-u;
        int r=n-l;
        if(l<r){
            ans+=l;
            int diff=r-l;
            add(u,diff);
            add(v,-diff);
        }
        else if(l>r){
            ans+=r;
            int diff=l-r;
            add(v,diff);
            add(1,diff);
            add(u,-diff);
        }
        else{
            ans+=l;
        }
    }
    long long res=1e18;
    for(int i=1;i<=n;i++){
        res=min(res,query(i));
    }
    ans+=res;
    cout<<ans<<endl;
    return 0;
}