#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;

int n;
int nums[MAXN];
int sum[MAXN];
double ans=0;
int p,le;

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

double check(int pos,int len){
    double ans=1.0*(sum[n]-sum[n-len]+sum[pos]-sum[pos-len-1])/(2*len+1);
    return ans-nums[pos];
}

void compute(int pos,int len){
    int l=0,r=len;
    while(r-l>4){
        int midl=(r-l)/3+l;
        int midr=r-(r-l)/3;
        double k1=check(pos,midl);
        double k2=check(pos,midr);
        if(k1<k2){
            l=midl;
        }
        else{
            r=midr;
        }
    }
    for(int k=l;k<=r;k++){
        double res=check(pos,k);
        if(res>ans){
            ans=res;
            p=pos;
            le=k;
        }
    }
}

signed main()
{
    n=read();
    for(int i=1;i<=n;i++){
        nums[i]=read();
    }
    sort(nums+1,nums+n+1);
    for(int i=1;i<=n;i++){
        sum[i]=nums[i]+sum[i-1];
    }
    for(int i=1;i<=n;i++){
        cout<<sum[i]<<' ';
    }
    cout<<endl;
    p=1,le=0;
    for(int i=1;i<=n;i++){
        compute(i,min(i-1,n-i));
    }
    printf("%lld\n",2*le+1);
    for(int i=p-le;i<=p;i++){
        cout<<nums[i]<<' ';
    }
    for(int i=n-le+1;i<=n;i++){
        cout<<nums[i]<<' ';
    }
    return 0;
}