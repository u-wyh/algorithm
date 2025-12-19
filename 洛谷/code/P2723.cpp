#include<cstdio>
int n,m;
int a[101],b[101];
int s[100001];

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    s[0]=1;
    for(int i=1;i<=m;i++)
    {
        int min=2147483647;
        for(int j=1;j<=n;j++)
        {
            while(a[j]*s[b[j]]<=s[i-1]) b[j]++;
            if(a[j]*s[b[j]]<min) min=a[j]*s[b[j]];
        }
        s[i]=min;
    }
    printf("%d",s[m]);
}
