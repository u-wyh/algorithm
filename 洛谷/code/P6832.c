#include<stdio.h>
#include<string.h>
#define Max 10000005

int main()
{
    char s[Max];
    fgets(s,Max,stdin);
    int n=strlen(s)-1;
    long long nums[26];
    long long ans=0;
    for(int i=0;i<26;i++)
        nums[i]=0;
    for(int i=0;i<n;i++)
    {
        nums[s[i]-'a']++;
    }
    for(int i=0;i<26;i++)
        ans=ans>nums[i]?ans:nums[i];
    printf("%lld\n",ans);
    return 0;
}
