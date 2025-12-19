#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 65;
const int MOD = 1e9+7;
const int INV2 = 500000004;

int n,m,k;
int len1;
int nums1[MAXN];
int len2;
int nums2[MAXN];
int f[MAXN][2][2];

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

int gettotal(){
    return ((((n-m)%MOD)*((m+1)%MOD))%MOD+((((m+1)%MOD)*((m+2)%MOD)%MOD)*INV2%MOD))%MOD;
}

int compute(){
    len1=0,len2=0;
    while(n){
        nums1[++len1]=n%k;
        n/=k;
    }
    while(m){
        nums2[++len2]=m%k;
        m/=k;
    }
    for(int i=len2+1;i<=len1;i++){
        nums2[i]=0;
    }
    f[len1+1][0][1]=0,f[len1+1][1][0]=0,f[len1+1][1][1]=0;
    f[len1+1][0][0]=1;

    int base=(k*(k+1)/2)%MOD;
    for(int x=len1;x>=1;x--){
        for(int free1=0;free1<=1;free1++){
            for(int free2=0;free2<=1;free2++){
                int a=nums1[x],b=nums2[x];
                int ans=0;
                if(free1&&free2){
                    ans=(ans+f[x+1][1][1]*base%MOD)%MOD;
                    ans=(ans+f[x+1][1][0]*((2*k-b+1)*b/2%MOD)%MOD)%MOD;
                    ans=(ans+f[x+1][0][1]*((a+1)*a/2%MOD)%MOD)%MOD;
                    if(a>b){
                        ans=(ans+((a*2-b+1)*b/2%MOD)*f[x+1][0][0]%MOD)%MOD;
                    }
                    else {
                        ans=(ans+((a+1)*a/2%MOD)*f[x+1][0][0]%MOD)%MOD;
                    }
                }
                else if(free1&&!free2){
                    if(a-1>=b){
                        ans=(ans+f[x+1][0][0]*(a-b)%MOD)%MOD;
                    }
                    ans=(ans+(k-b)*f[x+1][1][0])%MOD;
                }
                else if(!free1&&free2){
                    if(a>b-1){
                        ans=(ans+b*f[x+1][0][0]%MOD)%MOD;
                    }
                    else{
                        ans=(ans+(a+1)*f[x+1][0][0]%MOD)%MOD;
                    }
                    ans=(ans+(a+1)*f[x+1][0][1]%MOD)%MOD;
                }
                else{
                    if(a>=b){
                        ans=1*f[x+1][0][0];
                    }
                    else{
                        ans=0;
                    }
                }

                f[x][free1][free2]=ans;
            }
        }
    }
    return (f[1][0][0]+f[1][1][0]+f[1][0][1]+f[1][1][1])%MOD;
}

signed main()
{
    int T=read();
    k=read();
    while(T--){
        n=read(),m=read();
        m=min(n,m);
        int all=gettotal();
        int res=compute();
        all=(all-res+MOD)%MOD;
        cout<<all<<endl;
    }
    return 0;
}