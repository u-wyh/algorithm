#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e3+5;

int n;
int val[MAXN];
int diff[MAXN];

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
    int T=read();
    while(T--){
        n=read();
        for(int i=1;i<=n;i++){
            val[i]=read();
        }
        for(int i=1;i<=n;i++){
            diff[i]=val[i]-val[i-1];
        }
        int eorval=0;
        for(int i=n;i>=1;i-=2){
            eorval^=diff[i];
        }
        cout<<(eorval?"TAK":"NIE")<<endl;
    }
    return 0;
}