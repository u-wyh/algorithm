#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;

int n,m;
long long arr[MAXN];
int q[MAXN];
long long f[MAXN];
int pre[MAXN];

int main()
{
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>arr[i];
        }
        arr[++n]=0;
        for(int i=1;i<=n;i++){
            f[i]=pre[i]=0;
        }
        cin>>m;
        for(int i=1;i<=m;i++){
            int l,r;
            cin>>l>>r;
            pre[r+1]=max(pre[r+1],l);
        }
        for(int i=1;i<=n;i++){
            pre[i]=max(pre[i],pre[i-1]);
        }
        int l=1,r=0;
        q[++r]=0;
        for(int i=1;i<=n;++i){
            while(l<=r&&q[l]<pre[i]) ++l;
            f[i]=f[q[l]]+arr[i];
            while(l<=r&&f[q[r]]>=f[i]) --r;
            q[++r]=i;
        }
        cout<<f[n]<<endl;
    }
    return 0;
}
