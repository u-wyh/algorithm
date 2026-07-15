#include<stdio.h>
#include<string.h>

#define MAX 100000+5

int max(int a,int b){
    return a>b?a:b;
}

int main()
{
    char s[MAX];
    scanf("%s",s);
    int ans=0,n=strlen(s),maxans=-1;
    for(int i=0;i<n;i++){
        if(s[i]=='0')
            ans+=1;
        else{
            ans-=1;
        }
        maxans=max(maxans,ans);
        if(ans<0)
            ans=0;
    }
    printf("%d\n",maxans);
    return 0;
}
