#include<stdio.h>
#include<string.h>

int main()
{
    char s1[70],s2[70];
    int ans=0;
    scanf("%s",s1);
    scanf("%s",s2);
    for(int i=0;i<strlen(s1)-1;i++){
        for(int j=1;j<strlen(s2);j++){
            if(s1[i]==s2[j]&&s1[i+1]==s2[j-1])
                ans++;
        }
    }
    printf("%lld\n",1<<ans);
    return 0;
}
