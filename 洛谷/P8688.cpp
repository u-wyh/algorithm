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
    f[0][0][0]=1;f[0][0][1]=1;
    f[0][1][0]=1;f[0][1][1]=1;

    int base=(k*(k+1)/2)%MOD;
    for(int x=1;x<=len1;x++){
        for(int free1=0;free1<=1;free1++){
            for(int free2=0;free2<=1;free2++){
                int upa=free1?k-1:nums1[x];
                int upb=free2?k-1:nums2[x];
                int ans=0;
                if(free1&&free2){
                    ans=base*f[x-1][1][1]%MOD;
                }
                else if(free1&&!free2){
                    int part1=(k*upb%MOD-(upb*(upb-1)%MOD*INV2)%MOD+MOD)%MOD;
                    int part2=(k-upb%MOD);
                    ans=(part1*f[x-1][1][1]%MOD+part2*f[x-1][1][0]%MOD)%MOD;
                }
                else if(!free1&&free2){
                    int part1=(((upa+1)*upa)%MOD*INV2)%MOD;
                    int part2=(upa+1)%MOD;
                    ans=(part1*f[x-1][1][1]%MOD+part2*f[x-1][0][1]%MOD)%MOD;
                }
                else{
                    if(upa<upb){
                        int part1=upa*(upa+1)/2%MOD;
                        int part3=(upa+1)%MOD;
                        ans=(part1*f[x-1][1][1]+part3*f[x-1][0][1]%MOD)%MOD;
                    }
                    else if(upa>upb){
                        int part1=(upb*(upb+1)/2%MOD+upb*(upa-upb)%MOD)%MOD;
                        int part2=(upa-upb)%MOD;
                        int part3=upb;
                        int part4=1;
                        ans=(part1*f[x-1][1][1]%MOD+part2*f[x-1][1][0]%MOD+part3*f[x-1][0][1]%MOD+part4*f[x-1][0][0]%MOD)%MOD;
                    }
                    else{
                        int part1=upa*(upa+1)/2%MOD;
                        int part3=upa;
                        int part4=1;
                        ans=(part1*f[x-1][1][1]%MOD+part3*f[x-1][0][1]%MOD+part4*f[x-1][0][0]%MOD)%MOD;
                    }
                }

                f[x][free1][free2]=ans;
            }
        }
    }
    return f[len1][0][0];
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