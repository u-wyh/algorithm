#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2005;

int n,m;
char s1[MAXN];
char s2[MAXN];
int f[MAXN][MAXN];

signed main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>s1[i];
        if(s1[i]=='A'){
            s1[i]='T';
        }
        else if(s1[i]=='T'){
            s1[i]='A';
        }
        else if(s1[i]=='G'){
            s1[i]='C';
        }
        else{
            s1[i]='G';
        }
    }
    for(int i=1;i<=m;i++){
        cin>>s2[i];
    }
    f[0][0]=1;
    for(int i=1;i<=n;i++){
        f[i][0]=1;
        for(int j=1;j<=min(i,m);j++){
            if(s1[i]==s2[j]){
                f[i][j]=(f[i-1][j]+f[i-1][j-1]);
            }
            else{
                f[i][j]=f[i-1][j];
            }
        }
    }
    cout<<f[n][m]<<endl;
    return 0;
}
