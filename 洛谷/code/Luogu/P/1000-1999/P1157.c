#include<stdio.h>

int a[30];

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    for(int s=(1<<n)-1;s>=0;s--){
        int cnt=0;
        for(int i=0;i<n;i++){
            if(s&(1<<i))
                a[cnt++]=i;
        }
        if(cnt==m){
            for(int i=m-1;i>=0;i--){
                printf("%3d",n-a[i]);
            }
            printf("\n");
        }
    }
    return 0;
}
