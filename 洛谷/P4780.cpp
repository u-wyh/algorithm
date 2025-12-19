#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e4+5;
const long long LIMIT = (1ll<<31);

int n;
long long ans=1;

int prime[MAXN];
int cnt=0;
bool vis[MAXN];

bool isprime(int val){
    if(val<=50000){
        return !vis[val];
    }
    for(int i=2;i*i<=val;i++){
        if(val%i==0){
            return false;
        }
    }
    return true;
}

void euler(int n){
    vis[0]=vis[1]=true;
    for(int i=2;i<=n;i++){
        if(!vis[i]){
            prime[++cnt]=i;
        }
        for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
            vis[i*prime[j]]=1;
            if(i%prime[j]==0){
                break;
            }
        }
    }
}

void dfs(int u,long long cur,int rest){
    if(rest==1){
        if(cur<ans){
            ans=cur;
        }
        return ;
    }
    if(isprime(rest+1)){
        ans=min(ans,cur*(rest+1));
    }
    for(int i=u;i<=cnt;i++){
        int p=prime[i];
        int q=p-1;
        if(q>rest){
            break;
        }
        if(rest%q){
            continue;
        }
        long long nxtcur=cur*p;
        if(nxtcur>ans){
            continue;
        }
        int nxtrest=rest/q;
        dfs(u+1,nxtcur,nxtrest);
        while(nxtrest%p==0){
            nxtrest/=p;
            nxtcur*=p;
            if(nxtcur>ans){
                break;
            }
            dfs(i+1,nxtcur,nxtrest);
        }
    }
}

int main()
{
    cin>>n;
    euler(50000);
    if(n==1){
        cout<<1<<endl;
        return 0;
    }
    ans=LIMIT+1;
    dfs(1,1,n);
    if(ans>LIMIT){
        cout<<-1<<endl;
    }
    else{
        cout<<ans<<endl;
    }
    return 0;
}