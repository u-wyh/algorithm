#include<stdio.h>
#include<string.h>
#define Max 1005

int main()
{
    char s1[Max],s2[Max];
    fgets(s1,Max,stdin);
    fgets(s2,Max,stdin);
    int n=strlen(s1);
    int m=strlen(s2);
    int k=0;
    for(int i=0;i<n;i++)
    {
        if(s2[k]==s1[i])
            k++;
        if(k==m-1)
            break;
    }
    printf("%d\n",k);
    return 0;
}
