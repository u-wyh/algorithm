#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;

int n,k;
int a[MAXN];
int b[MAXN];

struct node{
    int val,sub,x;
};

struct compare{
    bool operator()(node a,node b){
        return a.val<b.val;
    }
};
priority_queue<node,vector<node>,compare>heap;

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

signed main()
{
    n=read(),k=read();
    for(int i=1;i<=n;i++){
        a[i]=read();
        b[i]=read();
        heap.push({a[i]-b[i],i,1});
    }
    int ans=0;
    while(k--){
        node tmp=heap.top();
        if(tmp.val<=0){
            break;
        }
        heap.pop();
        ans+=tmp.val;
        int id=tmp.sub;
        heap.push({a[id]-b[id]-2*b[id]*tmp.x,id,tmp.x+1});
    }
    cout<<ans<<endl;
    return 0;
}