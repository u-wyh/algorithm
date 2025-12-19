#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e3+5;

int n,m,k;
int val[MAXN][MAXN];
int row[MAXN][MAXN];
int col[MAXN][MAXN];
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
    k=read(),m=read(),n=read();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            val[i][j]=read();
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            row[i][j]=row[i][j-1]+val[i][j];
            col[i][j]=col[i-1][j]+val[i][j];
        }
    }

    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            f[i][j][0]=0;
            f[i][j][1]=m;
        }
    }
    f[1][n][0]=1;
    f[1][n][1]=m;
    int ans=n+m;
    for(int len=n;len;len--){
        bool flag=false;
        for(int l=1,r=len;r<=n;l++,r++){
            int p=f[l][r][0];
            int q=f[l][r][1];
            if(p==0){
                continue;
            }
            while(p<=q&&col[r][p]-col[l-1][p]<=k){
                p++;
            }
            while(p<=q&&col[r][q]-col[l-1][q]<=k){
                q--;
            }
            if(p>q){
                ans=min(ans,n-len+m);
                flag=true;
                break;
            }
            if(row[l][q]-row[l][p-1]<=k){
                f[l+1][r][0]=p;
                f[l+1][r][1]=q;
            }
            if(row[r][q]-row[r][p-1]<=k){
                f[l][r-1][0]=p;
                f[l][r-1][1]=q;
            }
        }
        if(flag){
            break;
        }
    }

    for(int i=1;i<=m;i++){
        for(int j=i;j<=m;j++){
            f[i][j][0]=0;
            f[i][j][1]=n;
        }
    }
    f[1][m][0]=1;
    f[1][m][1]=n;
    for(int len=m;len;len--){
        bool flag=false;
        for(int l=1,r=len;r<=m;l++,r++){
            int p=f[l][r][0];
            int q=f[l][r][1];
            if(p==0){
                continue;
            }
            while(p<=q&&row[p][r]-row[p][l-1]<=k){
                p++;
            }
            while(p<=q&&row[q][r]-row[q][l-1]<=k){
                q--;
            }
            if(p>q){
                ans=min(ans,n-len+m);
                flag=true;
                break;
            }
            if(col[q][l]-col[p-1][l]<=k){
                f[l+1][r][0]=p;
                f[l+1][r][1]=q;
            }
            if(col[q][r]-col[p-1][r]<=k){
                f[l][r-1][0]=p;
                f[l][r-1][1]=q;
            }
        }
        if(flag){
            break;
        }
    }
    cout<<ans<<endl;
    return 0;
}