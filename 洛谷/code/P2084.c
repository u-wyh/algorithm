#include<stdio.h>
#include<string.h>

#define Max 1001

int main()
{
    int m;
    char str[Max];
    scanf("%d",&m);
    scanf(" ");
    fgets(str,Max,stdin);
    int n=strlen(str)-1;
    if(str[0]-'0'!=0)
        printf("%d*%d^%d",str[0]-'0',m,n-1);
    for(int i=1;i<n;i++)
    {
        if(str[i]-'0'!=0)
        {
            printf("+%d*%d^%d",str[i]-'0',m,n-i-1);
        }
    }
    return 0;
}
