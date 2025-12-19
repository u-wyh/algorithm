#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e6+5;

int n,s;
int nums[MAXN];
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
    n=read(),s=read();
    nums[0]=-1;
    for(int i=1;i<=n;i++){
        nums[i]=read();
        nums[i]=max(nums[i],nums[i-1]+1);
    }
    f[1]=2*s+nums[1];
    int p=0;
    for(int i=2;i<=n;i++){
        while(p<i&&(f[p]-p)<(nums[i]-i+1)){
            p++;
        }
        f[i]=1-p+2*s+i-1+nums[i];
        if(p!=i){
            f[i]=min(f[i],f[p]-2*p+2*i+2*s-2);
        }
    }
    cout<<f[n]<<endl;
    return 0;
}