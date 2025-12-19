#include<stdio.h>
#include<stdlib.h>

int cmp(const void *a,const void *b)
{
    return (*(int *)b-*(int *)a);
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int a[n+1],b[m+1];
    for(int i=1;i<n;i++){
        scanf("%d",&a[i]);
    }
    a[n]=0;
    for(int i=1;i<m;i++){
        scanf("%d",&b[i]);
    }
    b[m]=0;
    qsort(a+1,n-1,sizeof(int),cmp);
    qsort(b+1,m-1,sizeof(int),cmp);
    long long ans=0;
    int s1=1,s2=1;
    for(int i=2;i<n+m;i++){
        if(a[s1]>b[s2])
            ans+=s2*a[s1++];
		else
            ans+=s1*b[s2++];
    }
    printf("%lld\n",ans);
    return 0;
}
