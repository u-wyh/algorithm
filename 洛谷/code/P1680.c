#include<stdio.h>

#define MOD 1000000000+7

int min(int a,int b){
    return a<b?a:b;
}

int C(int m,int n){
    int ans=1;
    for(int i=1,j=m;i<=min(n,m-n);i++,j--){
        //printf("%d\n",ans);
        ans=(ans*j)%MOD;
        ans=(ans/i)%MOD;
    }
    return ans;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int a[m+1];
    for(int i=1;i<=m;i++){
        scanf("%d",&a[i]);
        n=n-a[i];
    }
    //printf("%d %d\n",n,m);
    printf("%d\n",C(n-1,m-1));
    return 0;
}
