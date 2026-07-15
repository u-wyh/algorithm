#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m,k;
char s[MAXN];
int nums[MAXN];
int dis[27][27];
int sum[MAXN][27];
int tmp[27];
int f[MAXN];

void floyd(){
    for(int k=1;k<=m;k++){
        for(int i=1;i<=m;i++){
            for(int j=1;j<=m;j++){
                dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
            }
        }
    }
}

int main()
{
    cin>>n>>m>>k;
    scanf("%s",s+1);
    for(int i=1;i<=n;i++){
        nums[i]=s[i]-'a'+1;
    }
    for(int i=1;i<=m;i++){
        for(int j=1;j<=m;j++){
            cin>>dis[i][j];
        }
    }
    floyd();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            sum[i][j]=sum[i-1][j]+dis[nums[i]][j];
        }
    }
    for(int i=1;i<=n;i++){
        f[i]=INT_MAX;
    }
    for(int i=1;i<=26;i++){
        tmp[i]=0;
    }

    for(int i=k;i<=n;i++){
        if(i>=2*k){
            for(int j=1;j<=m;j++){
                tmp[j]=min(tmp[j],f[i-k]-sum[i-k][j]);
            }
        }
        for(int j=1;j<=m;j++){
            f[i]=min(f[i],sum[i][j]+tmp[j]);
        }
    }

    cout<<f[n]<<endl;
    return 0;
}