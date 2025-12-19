#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define MAX 200000+5

int n;
long long m;
int a[MAX];
double average;

int main()
{
    scanf("%d %lld",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    int l=0,r=n,mid,ans;
    while(l<=r){
        mid=l+((r-l)>>1);

    }
    return 0;
}
