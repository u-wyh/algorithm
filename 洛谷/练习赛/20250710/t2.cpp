#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;

int n,m;
int nums[MAXN];
int diff[MAXN];
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
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        nums[i]=read();
    }
    for(int i=2;i<=n;i++){
        diff[i]=nums[i]-nums[i-1];
    }
    for(int i=1;i<=n;i++){
        sum[i]=sum[i-1]+max(0ll,diff[i]);
    }
    int k=read();
    for(int i=1;i<=m;i++){
        int l,r;
        l=read(),r=read();
        cout<<(sum[r]-sum[l]+k)<<endl;
    }
    return 0;
}