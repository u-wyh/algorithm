#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e5+5;
const int INF = 1e15;

int n,d,k;
int pos[MAXN];
int val[MAXN];
int dp[MAXN];
int q[MAXN];

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

bool check(int limit){
    int l=max(1ll,d-limit);
    int r=d+limit;
    int h=0,t=0;
    for(int i=1;i<=n;i++){
        dp[i]=-INF;
    }
    dp[0]=0;
    int now=0;
    for(int i=1;i<=n;i++){
        while(now<i&&pos[i]-pos[now]>=l){
            while(h<t&&dp[now]>=dp[q[t]]){
                t--;
            }
            q[++t]=now;
            now++;
        }
        while(h<t&&pos[i]-pos[q[h+1]]>r){
            h++;
        }
        if(h<t)
            dp[i]=dp[q[h+1]]+val[i];
        if(dp[i]>=k){
            return true;
        }
    }
    return false;
}

signed main()
{
    n=read(),d=read(),k=read();
    int all=0;
    for(int i=1;i<=n;i++){
        pos[i]=read(),val[i]=read();
        if(val[i]>0){
            all+=val[i];
        }
    }
    if(all<k){
        cout<<-1<<endl;
        return 0;
    }
    pos[0]=0,val[0]=0;
    int l=0,r=1e9,ans=-1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    cout<<ans<<endl;
    return 0;
}