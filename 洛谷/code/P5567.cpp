// https://www.luogu.com.cn/problem/P5667
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN=2e5+5;
const int MAXT=2e6+5;
const int P=998244353;
const int g=3;
const int gi=332748118;

int n,m;
int A[MAXT];
int B[MAXT];
int rev[MAXT];
int f[MAXN];

int fac[MAXN];
int invfac[MAXN];

// 快速幂
int qpow(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=ans*a%P;
        }
        a=a*a%P;
        b>>=1;
    }
    return ans;
}

// 迭代 NTT
void NTT(int A[],int n,int op){
    // 位逆序置换
    for(int i=0;i<n;i++){
        rev[i]=(rev[i>>1]>>1)+((i&1)?(n>>1):0);
    }
    for(int i=0;i<n;i++){
        if(i<rev[i]){
            swap(A[i],A[rev[i]]);
        }
    }
    // 蝶形运算
    for(int m=2;m<=n;m<<=1){
        int g1=qpow(op==1?g:gi,(P-1)/m);
        for(int i=0;i<n;i+=m){
            int gk=1;
            for(int j=0;j<m/2;j++){
                int x=A[i+j];
                int y=A[i+j+m/2]*gk%P;
                A[i+j]=(x+y)%P;
                A[i+j+m/2]=(x-y+P)%P;
                gk=gk*g1%P;
            }
        }
    }
}

signed main()
{
    cin>>n>>m;
    for(int i=0;i<=n;i++){
        cin>>f[i];
    }

    fac[0]=1;
    for(int i=1;i<=n;i++){
        fac[i]=(fac[i-1]*i)%P;
    }
    invfac[n]=qpow(fac[n],P-2);
    for(int i=n;i>=1;i--){
        invfac[i-1]=invfac[i]*i%P;
    }

    for(int i=0;i<=n;i++){
        A[i]=f[i]*invfac[i]%P*invfac[n-i]%P;
        if((n-i)&1){
            A[i]=P-A[i];
        }
    }
    for(int j=0;j<=2*n;j++){
        B[j]=qpow(m-n+j,P-2);
    }

    int len=1;
    while(len<(3*n+1)){
        len<<=1;
    }
    NTT(A,len,1);
    NTT(B,len,1);
    for(int i=0;i<len;i++){
        A[i]=A[i]*B[i]%P;
    }
    NTT(A,len,-1);
    int invlen=qpow(len,P-2);
    for(int i=0;i<len;i++){
        A[i]=A[i]*invlen%P;
    }

    int px=1;
    for(int k=0;k<=n;k++){
        px=px*(m-k)%P;
    }
    for(int j=0;j<=n;j++){
        int val=px;
        val*=A[n+j];
        val%=P;
        px=px*(m+j+1)%P;
        px=px*qpow(m-n+j,P-2)%P;
        cout<<val<<' ';
    }
    return 0;
}