#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;

int n,t;
int nums[MAXN];
int sum[MAXN];

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
    n=read(),t=read();
    for(int i=1;i<=n;i++){
        nums[i]=read();
    }
    for(int i=1;i<=n;i++){
        sum[i]=sum[i-1]+nums[i];
    }
    t=(t-1)%sum[n]+1;
    for(int i=1;i<=n;i++){
        if(t<=sum[i]){
            cout<<i<<' '<<(t-sum[i-1])<<endl;
            return 0;
        }
    }
    return 0;
}