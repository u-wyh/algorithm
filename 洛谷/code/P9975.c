#include<stdio.h>
#include<stdbool.h>

#define MAX 300000+5

char s[MAX];
int n;

bool check(int x){

}

int main()
{
    scanf("%d",&n);
    scanf("%s",s);
    int l=0,r=n,mid,ans=0;
    while(l<=r){
        mid=(l+r)/2;
        if(check(mid)){
            ans=mid;
            r=mid-1;
        }else{
            l=mid+1;
        }
    }
    printf("%d\n",ans);
    return 0;
}

