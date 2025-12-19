#include<bits/stdc++.h>
using namespace std;

char a[30],b[30];

void build(int l1,int r1,int l2,int r2){
    for(int i=l2;i<=r2;i++){
        if(b[i]==a[l1]){
            int cnt=i-l2;
            build(l1+1,l1+cnt,l2,i-1);
            build(l1+cnt+1,r1,i+1,r2);
            printf("%c",a[l1]);
            return ;
        }
    }
}

int main()
{
    int n=1;
    while(scanf("%c",&b[n])==1&&b[n]!='\n')
        n++;
    for(int i=1;i<=n-1;i++)
        cin>>a[i];
    //printf("%d\n",n);
    build(1,n-1,1,n-1);
    return 0;
}
