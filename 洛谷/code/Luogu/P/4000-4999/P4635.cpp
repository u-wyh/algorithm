#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;

int n,m,p;
int tree[MAXN];
int diff[MAXN];

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

void add(int x,int val){
    diff[x]+=val;
    while(x<=n){
        tree[x]+=val;
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
    n=read(),m=read(),p=read();
    int pre=0;
    for(int i=1;i<=n;i++){
        int x=read();
        add(i,(x-pre+p)%p);
        pre=x;
    }
    for(int i=1;i<=m;i++){
        int op,l,r,v;
        op=read(),l=read(),r=read();
        if(op==1){
            v=read()%p;
            add(l,(diff[l]+v>=p)?v-p:v);
            add(r+1,(diff[r+1]>=v)?-v:p-v);
        }
        else{
            printf("%lld\n",query(r)/p-query(l)/p);
        }
    }
    return 0;
}