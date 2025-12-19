#include<bits/stdc++.h>
using namespace std;

int n,now,ans;
int landmine[25],vis[25],choose[25],last[25];
int connect[25][25];

void dfs(int x,int k,int now){//表示现在到了第x号  已经选择了k个  目前的值是now
    int i,flag=1;
    for(i=1;i<=n;i++){
        if(connect[x][i]==1&&vis[i]==0){
            vis[x]=1;
            choose[k+1]=x;
            flag=0;
            //if(k==0)
                //dfs(x+1,k,now);
            dfs(i,k+1,now+landmine[x]);
            vis[x]=0;
            choose[k+1]=0;
            if(k==0)
                dfs(x+1,k,now);
        }
    }
    if(flag){
        if(ans<now+landmine[x]){
            ans=now+landmine[x];
            memset(last,0,sizeof(last));
            for(int i=1;i<=k;i++){
                last[i]=choose[i];
            }
            last[k+1]=x;
            return ;
        }else{
            return ;
        }
    }
}

int main()
{
    cin>>n;
    int maxland=0,h;
    for(int i=1;i<=n;i++){
        cin>>landmine[i];
        if(maxland<landmine[i]){
            maxland=landmine[i];
            h=i;
        }
    }
    int sum=0;
    for(int i=1;i<=n;i++){
        int a;
        connect[i][i]=0;
        for(int j=1;j<=n-i;j++){
            cin>>a;
            sum+=a;
            connect[i][i+j]=a;
        }
    }
    /*
    for(int i=1;i<=n;i++){
        for(int j=1;j<i;j++){
            connect[i][j]=connect[j][i];
        }
    }

    printf("-----------------------------------------\n");
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            printf("%2d",connect[i][j]);
        }
        printf("\n");
    }
    printf("-----------------------------------------\n");
    */
    if(sum==0){
        printf("%d\n%d\n",h,maxland);
        return 0;
    }
    ans=maxland;
    last[1]=h;
    dfs(1,0,0);
    int i=1;
    while(last[i]!=0)
        printf("%d ",last[i++]);
    printf("\n");
    printf("%d\n",ans);
    return 0;
}
