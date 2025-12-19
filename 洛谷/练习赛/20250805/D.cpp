#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;

int n;
int nums[MAXN];
int diff[MAXN];
int f[MAXN];

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
    int T=read();
    while(T--){
        n=read();
        for(int i=1;i<=n;i++){
            nums[i]=read();
        }
        for(int i=1;i<=n;i++){
            diff[i]=nums[i]-nums[i-1];
        }
        int ans=0;
        f[1]=0;
        for(int i=2;i<=n;i++){
            if(f[i-1]<0){
                f[i]=f[i-1]+diff[i];
            }
            else{
                f[i]=diff[i];
            }
            ans=min(ans,f[i]);
        }
        cout<<-ans<<endl;
    }
    return 0;
}