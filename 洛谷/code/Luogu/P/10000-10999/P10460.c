#include<stdio.h>
#include<stdbool.h>

int max(int a,int b){
    return a>b?a:b;
}

bool check(int l,int r,int *sum){
    if((sum[r]-sum[l-1])%2==1)
        return true;
    return false;
}

int main()
{
    int t;
    scanf("%d",&t);
    for(int i=1;i<=t;i++){
        int n;
        scanf("%d",&n);
        int s[n+1],e[n+1],d[n+1],sum[n+1],l=1,r=0,mid;
        sum[0]=0;
        for(int i=1;i<=n;i++){
            scanf("%d %d %d",&s[i],&e[i],&d[i]);
            r=max(r,e[i]);
            sum[i]=sum[i-1]+(e[i]-s[i]+1)/d[i];
        }
        if(sum[n]%2==0){
            printf("There's no weakness. \n");
            continue;
        }
        while(l<=r){
            mid=l+((r-l)>>1);
            if(check(l,mid,sum)){
                r=mid;
            }else{
                l=mid;
            }
        }
        printf("%d %d\n",l,mid);
    }
    return 0;
}
