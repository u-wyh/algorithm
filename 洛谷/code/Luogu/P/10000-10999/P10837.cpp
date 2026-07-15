#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n,m,cnt,tot,pos;
int t[MAXN],p[MAXN<<1];
int val[2][MAXN];
long long ans,sum;
int q[MAXN<<1];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>t[i];
    }
    for(int i=1;i<=n;i++){
        p[++cnt]=t[i];
        p[++cnt]=t[i]+m;
    }
    sort(t+1,t+n+1);
    sort(p+1,p+cnt+1);
    for(int i=1;i<=cnt;i++){
        if(p[i]!=p[i-1]){
            p[++tot]=p[i];
        }
    }
    int l=1,r=1;
    for(int i=1;i<=tot;i++){
        while(l<r&&t[q[l]]+m<=p[i]){
            l++;
        }
        while(pos+1<=n&&t[pos+1]<=p[i]){
            q[r++]=++pos;
        }
        if(r-l==1){
            val[0][q[l]]+=p[i+1]-p[i],sum+=p[i+1]-p[i];
        }
        if(r-l==2){
            val[1][q[l]]+=p[i+1]-p[i],val[1][q[r-1]]+=p[i+1]-p[i];
        }
    }
    for(int i=1;i<=n;i++)
        ans=max(ans,sum-val[0][i]+val[1][i]+m);
    cout<<ans<<endl;
    return 0;
}
