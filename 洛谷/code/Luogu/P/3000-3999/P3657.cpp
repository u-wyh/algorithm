#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n;
int a[MAXN];
int b[MAXN];
int pos[MAXN];

int tree[MAXN];

int help[MAXN];

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

void update(int x,int val){
    while(x<=n){
        tree[x]=max(tree[x],val);
        x+=lowbit(x);
    }
}

int query(int x){
    int ans=0;
    while(x){
        ans=max(ans,tree[x]);
        x-=lowbit(x);
    }
    return ans;
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        a[i]=read();
    }
    for(int i=1;i<=n;i++){
        b[i]=read();
        pos[b[i]]=i;
    }
    for(int p=1;p<=n;p++){
        int i=a[p];
        for(int j=max(i-4,1);j<=min(n,i+4);j++){
            help[j]=query(pos[j]-1);
        }
        for(int j=max(i-4,1);j<=min(n,i+4);j++){
            update(pos[j],help[j]+1);
        }
    }
    cout<<query(n)<<endl;
    return 0;
}