#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n;
char s[MAXN];
int f[MAXN],g[MAXN];

int main()
{
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d %s",&n,s+1);
        for(int i=1;i<=n;i++){
            if(s[i]=='('){
                f[i]=f[i-1]+1;
            }
            else{
                f[i]=f[i-1];
            }
        }
        f[n+1]=0,g[n+1]=0;
        for(int i=n;i>=1;i--){
            if(s[i]==')'){
                g[i]=g[i+1]+1;
            }
            else{
                g[i]=g[i+1];
            }
        }
        int ans=INT_MAX;
        for(int i=0;i<=n;i++){
            ans=min(ans,f[i]+g[i+1]);
        }
        cout<<ans<<endl;
    }
    return 0;
}