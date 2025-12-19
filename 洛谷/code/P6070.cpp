#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e3+5;

int arr[MAXN][MAXN];
int diff[MAXN][MAXN];
int n,m,k;

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
    n=read(),m=read(),k=read();
    for(int i=1;i<=m;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        arr[u][v]=w;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            diff[i][j]=arr[i][j]-arr[i][j-1];
        }
    }
    int ans=0;
    for(int i=1;i<=(n-k+1);i++){
        for(int j=1;j<=(n-k+1);j++){
            if(diff[i][j]==0){
                continue;
            }
            ans+=abs(diff[i][j]);
            int num=diff[i][j];
            for(int t=i;t<=i+k-1;t++){
                diff[t][j]-=num;
                diff[t][j+k]+=num;
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(diff[i][j]){
                cout<<-1<<endl;
                return 0;
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}
