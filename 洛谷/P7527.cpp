#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n;
int arr[MAXN];
int nxt[MAXN];
int lst[MAXN];
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

int lowbit(int x){
    return x&(-x);
}

int sum(int x){
    int ans=0;
    while(x){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}

void add(int x,int val){
    while(x<=n){
        tree[x]+=val;
        x+=lowbit(x);
    }
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        arr[i]=read();
        if(lst[arr[i]]!=0){
            nxt[lst[arr[i]]]=i;
        }
        else{
            add(i,1);
        }
        lst[arr[i]]=i;
        nxt[i]=n+1;
    }
    long long ans=0;
    for(int i=1;i<=n;i++){
        add(i,-1);
        if(i+1<=nxt[i]-1){
            ans+=sum(nxt[i]-1);
        }
        add(nxt[i],1);
    }
    cout<<ans<<endl;
    return 0;
}
