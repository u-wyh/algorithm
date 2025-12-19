#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;

int n;
char s[MAXN];

int main()
{
    scanf("%d %s",&n,s+1);
    long double ans=0,len=0;
    for(int i=1;i<=n;i++){
        if(s[i]=='o'){
            ans+=2*len+1;
            len+=1;
        }
        else if(s[i]=='x'){
            len=0;
        }
        else{
            ans+=len+0.5;
            len=(len+1)/2;;
        }
    }
    printf("%.4Lf",ans);
    return 0;
}