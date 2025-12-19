#include<bits/stdc++.h>
using namespace std;
const int MAXN = 205;
const int MAXM = 4005;

int n,m,x;
char c;
bool vis[MAXN][MAXM];
char s[MAXM][MAXM];

int main()
{
    scanf("%d %d %d %c",&n,&m,&x,&c);
    for(int i=1;i<=n*x;i++){
        scanf("%s",s[i]+1);
    }
    for(int i=1;i<=n*x;i++){
        for(int j=1;j<=m*x;j++){
            if(s[i][j]==c){
                vis[(i-1)/x+1][(j-1)/x+1]=1;
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cout<<vis[i][j];
        }
        cout<<endl;
    }
    return 0;
}