#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXH = 18;

int n,q;
char s[MAXN<<1];
char t[MAXN];
int l[MAXN][MAXH];
int r[MAXN][MAXH];
int sum[MAXN];
int sl[MAXN][MAXH];
int sr[MAXN][MAXH];

int query(int u,int v){
    if(u==v){
        return 0;
    }
    int ans=0;
    for(int i=MAXH-1;i>=0;i--){
        if(r[u][i]>=v){
            continue;
        }
        ans+=(1<<i);
        u=r[u][i];
    }
    ans++;
    return ans;
}

int main()
{
    scanf("%d %d",&n,&q);
    scanf("%s",s+1);
    scanf("%s",t+1);
    int cnt=0,now=1;
    for(int i=1;i<=2*n;i++){
        if(s[i]=='L'){
            cnt++;
        }
        else{
            r[now][0]=cnt;
            now++;
        }
    }
    cnt=n+1,now=n;
    for(int i=2*n;i>=1;i--){
        if(s[i]=='R'){
            cnt--;
        }
        else{
            l[now][0]=cnt;
            now--;
        }
    }

    for(int i=1;i<=n;i++){
        sum[i]=sum[i-1]+t[i]-'0';
    }
    for(int i=1;i<=n;i++){
        sr[i][0]=sum[r[i][0]];
        sl[i][0]=sum[l[i][0]-1];
    }

    for(int k=1;k<MAXH;k++){
        for(int i=1;i<=n;i++){
            l[i][k]=l[l[i][k-1]][k-1];
            r[i][k]=r[r[i][k-1]][k-1];
            sr[i][k]=sr[i][k-1]+sr[r[i][k-1]][k-1];
            sl[i][k]=sl[i][k-1]+sl[l[i][k-1]][k-1];
        }
    }

    while(q--){
        int u,v;
        scanf("%d %d",&u,&v);
        int ans1=query(u,v);
        long long ans2=t[u]-'0'+t[v]-'0';
        int steps=ans1-1;
        for(int i=MAXH-1;i>=0;i--){
            if(steps&(1<<i)){
                ans2+=sr[u][i];
                u=r[u][i];
            }
        }
        for(int i=MAXH-1;i>=0;i--){
            if(steps&(1<<i)){
                ans2-=sl[v][i];
                v=l[v][i];
            }
        }
        cout<<ans1<<' '<<ans2<<endl;
    }
    return 0;
}