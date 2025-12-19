#include<stdio.h>
#include<string.h>
#define Max 105

int main()
{
    char s1[Max],s2[Max];
    fgets(s1,Max,stdin);
    fgets(s2,Max,stdin);
    int n=strlen(s1)-1,count=0;
    for(int i=0;i<n-1;i++)
    {
        if(s1[i]!=s2[i])
        {
            count++;
            if(s1[i+1]=='*')
                s1[i+1]='o';
            else
                s1[i+1]='*';
        }
    }
    printf("%d\n",count);
    return 0;
}
