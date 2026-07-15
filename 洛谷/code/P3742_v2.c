#include<stdio.h>
#include<string.h>

int main()
{
    int n;
    scanf("%d",&n);
    char s1[n],s2[n],s3[n];
    scanf("%s",s1);
    scanf("%s",s2);
    //printf("%c   %c",s1[n-1],s2[n-1]);
    for(int i=0;i<n;i++)
    {
        if(s1[i]<s2[i])
        {
            printf("-1\n");
            return 0;
        }
        else
        {
            s3[i]=s2[i];
        }
    }
    s3[n]='\0';
    puts(s3);
    return 0;
}
