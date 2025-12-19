#include<bits/stdc++.h>
using namespace std;
const int MAXN = (1<<20);
const int MAXM = 21;

int n;
int dp[MAXM][MAXN];


inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

int main()
{
    return 0;
}