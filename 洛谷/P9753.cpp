#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e6+5;

int n;
char str[MAXN];
int g[MAXN];
long long f[MAXN];

int main()
{
    scanf("%d",&n);
    scanf("%s",str+1);
    for(int i=1;i<=n;i++){
        int pos=i-1;
        while(pos>0){
            if(str[pos]==str[i]){
                g[i]=pos;
                break;
            }
            else{
                pos=g[pos]-1;
            }
        }
    }
    // for(int i=1;i<=n;i++){
    //     cout<<g[i]<<' ';
    // }
    // cout<<endl;
    // f[0]=-1;
    for(int i=1;i<=n;i++){
        if(g[i]){
            f[i]=f[g[i]-1]+1;
        }
    }
    // for(int i=1;i<=n;i++){
    //     cout<<f[i]<<' ';
    // }
    // cout<<endl;
    long long ans=0;
    for(int i=1;i<=n;i++){
        ans+=f[i];
    }
    cout<<ans<<endl;
    return 0;
}