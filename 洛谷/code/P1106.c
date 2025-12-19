#include<stdio.h>
#include<string.h>

#define MAX 255

char s[MAX];
int nums[MAX],stack[MAX],size=0;
int k;

int main()
{
    scanf("%s",s);
    int n=strlen(s);
    scanf("%d",&k);
    //printf("%d\n",n);
    for(int i=0;i<n;i++){
        nums[i+1]=s[i]-'0';
    }
    int h=k;
    for(int i=1;i<=n;i++){
        while(k&&size&&nums[i]<stack[size]){
            k--;
            stack[size--]=0;
        }
        stack[++size]=nums[i];
    }
    int i=1;
    while(stack[i]==0&&i!=n-h)
        i++;
    for(;i<=n-h;i++){
        printf("%d",stack[i]);
    }
    return 0;
}
