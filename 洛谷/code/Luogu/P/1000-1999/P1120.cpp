#include<bits/stdc++.h>
using namespace std;
const int MAXN = 666;

int n,sum,mn=MAXN,mx,d;
int len[MAXN],a[MAXN],pre[MAXN];

void dfs(int u,int k,int p){
    if(u==0){
        dfs(d,k-1,a[n]);
        return;
    }
    if(k==0){
        cout<<d<<endl;
        exit(0);
    }
    p=(p<u)?p:u;
    while(p&&len[p]==0){
        --p;
    }
    while(p){
        if(len[p]){
            --len[p];
            dfs(u-p,k,p);
            ++len[p];
            if((u==p)||(u==d))
                return ;
            p=pre[p];
        }else{
            p=pre[p];
        }
    }
}

int main()
{
    cin>>n;
    for(int i=1,x;i<=n;++i){
        cin>>x;
        sum+=x;
        a[i]=x;
        ++len[x];
    }
    sort(a+1,a+n+1);
    for(int i=1;i<=n;++i){
        if(a[i]!=a[i-1])
            pre[a[i]]=a[i-1];
    }
    for(d=a[n];(d<<1)<=sum;++d){
        if(sum%d==0){
            dfs(d,sum/d,a[n]);
        }
    }
    cout<<sum<<endl;
    return 0;
}
