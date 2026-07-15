#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e3+5;

int n,m;
int arr[MAXN][MAXN];
//fi,j,0​ 表示在考虑前 i 行前 j 列且   上一步   从左边走过来时的最小害怕值，
//fi,j,1​ 表示在考虑前 i 行前 j 列且   上一步   从上面走过来时的最小害怕值。
int f[MAXN][MAXN][2];

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
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            arr[i][j]=read();
            f[i][j][0]=f[i][j][1]=1e9;
        }
    }
    f[1][1][0]=arr[1][1]+arr[1][2]+arr[2][1];
    f[1][1][1]=arr[1][1]+arr[1][2]+arr[2][1];
    for(int i=2;i<=m;i++){
        f[1][i][0]=f[1][i-1][0]+arr[1][i+1]+arr[2][i];
    }
    for(int i=2;i<=n;i++){
        f[i][1][1]=f[i-1][1][1]+arr[i+1][1]+arr[i][2];
    }
    for(int i=2;i<=n;i++){
        for(int j=2;j<=m;j++){
            f[i][j][1]=min(f[i-1][j][0],f[i-1][j][1]+arr[i][j-1])+arr[i+1][j]+arr[i][j+1];
            f[i][j][0]=min(f[i][j-1][0]+arr[i-1][j],f[i][j-1][1])+arr[i+1][j]+arr[i][j+1];
        }
    }
    cout<<min(f[n][m][0],f[n][m][1])<<endl;
    return 0;
}
