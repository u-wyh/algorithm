#include<stdio.h>

int n,m,k;
int r[20005],c[20005],d1[40010],d2[40010];

int main()
{
    scanf("%d %d %d",&n,&m,&k);
    int a[k],b[k];
    for(int i=1;i<=k;i++){
        scanf("%d %d",&a[i],&b[i]);
        r[a[i]]=1;
        c[b[i]]=1;
        d1[a[i]+b[i]]=1;
        d2[a[i]-b[i]+20010]=1;
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(r[i]==1)
                break;
            if(c[j]==1)
                continue;
            if(d1[i+j]==1||)
        }
    }
    return 0;
}
