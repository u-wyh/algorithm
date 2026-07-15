#include<bits/stdc++.h>
using namespace std;
const int maxn=505,maxk=105;
int n,m,f[maxn][maxk][maxk][3];
char s[maxn];
int main(){
    scanf("%d%d%s",&n,&m,s+1);
    memset(f,128,sizeof(f));
    f[0][0][0][1]=0;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=m;j++){
            for(int k=0;k<=m;k++){
                if(s[i]=='z'){
                    f[i][j][k][1]=max(f[i-1][j][k][0]+1,f[i-1][j][k][1]);
                    if(k) f[i][j][k][0]=max(f[i-1][j][k-1][0],f[i-1][j][k-1][1]);
                } else {
                    f[i][j][k][0]=max(f[i-1][j][k][0],f[i-1][j][k][1]);
                    if(j) f[i][j][k][1]=max(f[i-1][j-1][k][0]+1,f[i-1][j-1][k][1]);
                }
            }
        }
    }
    int ans=0;
    for(int i=0;i<=m;i++){
        ans=max(ans,max(f[n][i][i][1],f[n][i][i][0]));
    }
    printf("%d\n",ans);
    return 0;
}

