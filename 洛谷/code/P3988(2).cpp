#include<bits/stdc++.h>
using namespace std;
const int MAXN = 7e5+5;

int n,p;
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

int queryrk(int rk){
    int ans=0,cnt=0;
    for(int i=p;i>=0;i--){
        ans+=(1<<i);
        if(ans>n||cnt+tree[ans]>=rk){
            ans-=(1<<i);
        }
        else{
            cnt+=tree[ans];
        }
    }
    return ans+1;
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        add(i,1);
    }
    p=log2(n)+1;
    int cur=1;
    for(int i=1;i<=n;i++){
        int m=read();
        int len=n-i+1;
        int u=query(cur);
        int now=(u+m)%len;
        if(now==0){
            now=len;
        }
        int x=queryrk(now);
        printf("%d\n",x);
        add(x,-1);
        if(now==len){
            cur=queryrk(1);
        }
        else{
            cur=queryrk(now);
        }
    }
    return 0;
}