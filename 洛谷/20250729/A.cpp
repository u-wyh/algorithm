#include<bits/stdc++.h>
using namespace std;
#define int long long

int n,k,s,t;

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

signed main()
{
    int T;
    T=read();
    while(T--){
        n=read(),k=read(),s=read(),t=read();
    }
    return 0;
}