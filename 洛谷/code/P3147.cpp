#include<bits/stdc++.h>
using namespace std;
const int MAXN = 60;
const int MAXM = 262150;

int n;
int f[MAXN][MAXM];

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
    n=read();
    for(int i=1;i<=n;i++){
        int u;
        u=read();
        f[u][i]=i+1;
    }
    int ans=0;
    for(int i=2;i<=log2(n)+40;i++){
        for(int j=1;j<=n;j++){
            if(!f[i][j]){
                f[i][j]=f[i-1][f[i-1][j]];
            }
            if(f[i][j]){
                ans=i;
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}
