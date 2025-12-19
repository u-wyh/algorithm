#include<stdio.h>
#include<stdlib.h>

int cmp(const void *a,const void *b){
    return (*(int *)b - *(int *)a);
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int T[n+1],t[n+1];
    t[1]=0;
    for(int i=1;i<=n;i++){
        scanf("%d",&T[i]);
        if(i>=2){
            t[i]=T[i]-T[i-1];
        }
    }
    qsort(t+1,n,sizeof(int),cmp);
    int sum=0;
    for(int i=1;i<=(m-1);i++){
        sum+=t[i];
    }
    printf("%d\n",T[n]+1-T[1]-sum+m-1);
    return 0;
}
