#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e4+5;
const double eps = 1e-6;

int n;
int nums[MAXN];
double pos;
double f[MAXN];
double g[MAXN];

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

bool check(double d){
    for(int i=n;i>=1;i--){
        if(d>=f[i]+1){
            for(int j=i;j<=n&&1.0*nums[j]<=d*2+nums[i];j++){
                if(g[j]+1<=d){
                    return true;
                }
            }
            break;
        }
    }
    return false;
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        nums[i]=read();
    }
    sort(nums+1,nums+n+1);

    f[1]=-1;
    int pos=nums[1],v=0;
    for(int i=2;i<=n;i++){
        if(nums[i]<=pos+v){
            f[i]=v;
        }
        else{
            pos=nums[i-1];
            v=f[i-1]+1;
            f[i]=max(f[i-1]+1,1.0*nums[i]-nums[i-1]);
        }
        // cout<<f[i]<<' ';
    }

    g[n]=-1;
    pos=nums[n],v=0;
    for(int i=n-1;i>=1;i--){
        if(nums[i]>=pos-v){
            g[i]=v;
        }
        else{
            pos=nums[i+1];
            v=g[i+1]+1;
            g[i]=max(g[i+1]+1,1.0*nums[i+1]-nums[i]);
        }
        // cout<<g[i]<<' ';
    }

    // for(int i=1;i<=n;i++){
    //     cout<<f[i]<<' ';
    // }
    // cout<<endl;
    
    // for(int i=1;i<=n;i++){
    //     cout<<g[i]<<' ';
    // }
    // cout<<endl;

    double l=0,r=(nums[n]-nums[1])/2.0,ans=0;
    while(r-l>=eps){
        double mid=(r+l)/2.0;
        if(check(mid)){
            ans=mid;
            r=mid;
        }
        else{
            l=mid;
        }
    }
    printf("%.1lf\n",ans);
    return 0;
}
/*
11

0 17 27 51 63 70 74 75 78 92 97
*/