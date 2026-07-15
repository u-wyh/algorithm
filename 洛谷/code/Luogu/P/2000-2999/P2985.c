#include<stdio.h>
#include<stdbool.h>

#define MAX 50005

int a[MAX];
int n,m;

int check(int x){
    int h=0,k=1;
    for(int i=1;i<=m;i++){
        while(h<x){
            if(k==n+1)
                return false;
            h+=a[k++];
        }
        if(h<x)
            return false;
        h/=2;
    }
    return true;
}

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    int l=0,r=1000000000,mid,ans=0;
    while(l<=r){
        mid=l+((r-l)>>1);
        if(check(mid)){
            l=mid+1;
            ans=mid;
        }else{
            r=mid-1;
        }
    }
    printf("%d\n",ans);
    int h=0,k=1;
    for(int i=1;i<=m;i++){
        if(i==m){
            while(k<=n){
                k++;
                printf("%d\n",m);
            }
        }
        else{
        while(h<ans){
            h+=a[k];
            printf("%d\n",i);
            k++;
        }
        h/=2;}
    }
    return 0;
}

