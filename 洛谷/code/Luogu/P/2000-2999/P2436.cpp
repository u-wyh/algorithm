#include<bits/stdc++.h>
using namespace std;
#define MAX 1005

int n,m;
int a[MAX],b[MAX];
int ansa,ansb;
int maxans;

void dfs(int x,int y){
    if(x+y>maxans){
        return ;
    }
    int i=1;
    while(i<=n){
        if((a[i]%(x+y))>x||(a[i]%(x+y))==0){
            dfs(x+1,y);
            dfs(x+1,y+1);
            dfs(x,y+1);
            break;
        }
        i++;
    }
    if(i==n+1){
        i=1;
        while(i<=m){
            if((b[i]%(x+y))<x&&(b[i]%(x+y))!=0){
                dfs(x+1,y);
                dfs(x+1,y+1);
                dfs(x,y+1);
                break;
            }
            i++;
        }
    }
    if(i==m+1){
        if(x<=ansa){
            ansa=x;
            ansb=min(y,ansb);
        }
    }
}

int main()
{
    while(scanf("%d %d",&n,&m)==2){
        memset(a,-1,sizeof(a));
        memset(b,-1,sizeof(b));
        maxans=0;
        ansa=1e9,ansb=1e9;
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
        }
        for(int i=1;i<=m;i++){
            scanf("%d",&b[i]);
        }
        maxans=a[1]+b[1];
        dfs(1,1);
        if(ansa==-1&&ansb==-1){
            printf("No\n");
        }else{
            printf("%d %d\n",ansa,ansb);
        }
    }
    return 0;
}
