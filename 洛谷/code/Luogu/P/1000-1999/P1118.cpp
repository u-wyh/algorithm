#include<bits/stdc++.h>
using namespace std;
#define MAX 13

int n,need,sum=0;
int ans[MAX],now[MAX],vis[MAX],C[MAX],C2[MAX],C3[MAX],C4[MAX];

int c(int a,int b){
    if(b==0)
        return 1;
    int sum=1;
    for(int i=1;i<=min(b,a-b);i++){
        sum=sum*(a-i+1)/i;
    }
    return sum;
}

void build(){
    for(int i=1;i<=n;i++){
        C[i]=c(n-1,i-1);
    }
}

void dfs(int i,int j){
    if((i>n&&j!=need)||(j+C4[n-i+1]>need)||(j+C3[n-i+1]<need)){
        return ;
    }
    if(i>n&&j==need){
        int k;
        for(k=1;k<=n;k++){
            if(now[k]>ans[k]){
                break;
            }
        }
        if(k==n+1){
            for(k=1;k<=n;k++){
                ans[k]=now[k];
            }
        }
        return ;
    }
    for(int k=1;k<=n;k++){
        if(vis[k]!=0)
            continue;
        else{
            vis[k]=1;
            j+=C[i]*k;
            now[i]=k;
            dfs(i+1,j);
            vis[k]=0;
            j-=C[i]*k;
            now[i]=0;
        }
    }
}

int main()
{
    cin>>n>>need;
    build();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=i;j++){
            C2[n-j+1]=C[n-j+1];
        }
        sort(C2+n-i+1,C2+n+1);
        int a=1,b=n,h=n;
        for(int k=1;k<=i;k++){
            C3[i]+=(b--)*C2[h];
            C4[i]+=(a++)*C2[h--];
        }
        //printf("%d %d\n",C3[i],C4[i]);
    }
    memset(ans,13,sizeof(ans));
    memset(now,0,sizeof(now));
    memset(vis,0,sizeof(vis));
    dfs(1,0);
    if(ans[1]>=13)
        return 0;
    for(int i=1;i<=n;i++){
        printf("%d ",ans[i]);
    }
    return 0;
}
