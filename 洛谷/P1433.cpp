#include<bits/stdc++.h>
using namespace std;

int n,cnt=0;
double x[16],y[16],dist[16][16];
double ans;
bool vis[16];

void dfs(int deep,int now ,double sum){
    cnt++;
    if(cnt>=10000000){
        printf("%.2f",ans);
        exit(0);
    }
    if(deep>n){
        if(sum<ans){
            ans=sum;
        }
        return ;
    }
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            double t=sum+dist[now][i];
            if(t>=ans)
                continue;
            vis[i]=1;
            dfs(deep+1,i,t);
            vis[i]=0;
        }
    }
}

int main()
{
    cin>>n;
    ans=1e6;
    x[0]=0;
    y[0]=0;
    for(int i=1;i<=n;i++){
        cin>>x[i]>>y[i];
    }
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            dist[i][j]=sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
        }
    }
    dfs(1,0,0);
    printf("%.2f",ans);
    return 0;
}
