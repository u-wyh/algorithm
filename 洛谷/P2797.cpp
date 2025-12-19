#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;

int n;
int nums[MAXN];
int sum[MAXN];
double ans=0;

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
        ans=max(ans,check(pos,k));
    }
}

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
    }
    sort(nums+1,nums+n+1);
    for(int i=1;i<=n;i++){
        sum[i]=nums[i]+sum[i-1];
    }
    for(int i=2;i<n;i++){
        compute(i,min(i-1,n-i));
    }
    printf("%.2lf\n",ans);
    return 0;
}