#include<stdio.h>

int s[4],a[21],nowtime,maxtime,sum,ans,maxdeep;

int max(int a,int b){
    return a>b?a:b;
}

void dfs(int x){
    if(x>maxdeep){
        maxtime=max(maxtime,nowtime);
        return ;
    }
    if(nowtime+a[x]<=sum/2){
        nowtime+=a[x];
        dfs(x+1);
        nowtime-=a[x];
    }
    dfs(x+1);
}

int main()
{
    for(int i=0;i<4;i++){
        scanf("%d",&s[i]);
    }
    for(int i=0;i<4;i++){
        nowtime=0;
        maxdeep=s[i];
        sum=0;
        for(int j=1;j<=s[i];j++){
            scanf("%d",&a[j]);
            sum+=a[j];
        }
        maxtime=0;
        dfs(1);
        ans+=(sum-maxtime);
    }
    printf("%d\n",ans);
    return 0;
}
