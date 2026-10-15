// https://www.luogu.com.cn/problem/P4091
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int MAXT = 4e5+5;
const int P = 998244353;
const int g = 3;
const int gi = 332748118;

int n,m;
int A[MAXT];
int B[MAXT];
int fac[MAXN];
int invfac[MAXN];
int inv[MAXN];

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

// 递归 NTT
void NTT(int A[],int n,int op){
    if(n==1){
        return;
    }

    int A1[n/2],A2[n/2];
    // 拆分奇偶项
    for(int i=0;i<n/2;i++){
        A1[i]=A[i*2];
        A2[i]=A[i*2+1];
    }

    // 递归分治
    NTT(A1,n/2,op);
    NTT(A2,n/2,op);

    // 单位根
    int g1=qpow(op==1?g:gi,(P-1)/n);
    int gk=1;

    // 蝶形运算
    for(int i=0;i<n/2;i++){
        A[i]=(A1[i]+A2[i]*gk)%P;
        A[i+n/2]=(A1[i]-A2[i]*gk%P+P)%P;
        gk=gk*g1%P;
    }
}

signed main()
{
    cin>>n;

    fac[0]=1;
    for(int i=1;i<=n;i++){
        fac[i]=(fac[i-1]*i)%P;
    }
    invfac[n]=qpow(fac[n],P-2);
    for(int i=n;i>=1;i--){
        invfac[i-1]=invfac[i]*i%P;
    }
    inv[1]=1;
    for(int i=2;i<=n;i++){
        inv[i]=(P-P/i)*inv[P%i]%P;
    }

    for(int k=0;k<=n;k++){
        if(k&1){
            A[k]=P-invfac[k];
        }
        else{
            A[k]=invfac[k];
        }

        if(k==0){
            B[k]=1;
        }
        else if(k==1){
            B[k]=n+1;
        }
        else{
            B[k]=(qpow(k,n+1)-1+P)%P;
            B[k]=B[k]*inv[k-1]%P;
            B[k]=B[k]*invfac[k]%P;
        }
    }

    m=1;
    while(m<(2*n-1)){
        m<<=1;
    }
    NTT(A,m,1);
    NTT(B,m,1);
    for(int i=0;i<m;i++){
        A[i]=A[i]*B[i]%P;
    }
    NTT(A,m,-1);

    int invn=qpow(m,P-2);
    for(int i=0;i<m;i++){
        A[i]=A[i]*invn%P;
    }

    int ans=0;
    int pow2=1;
    for(int j=0;j<=n;j++){
        ans=(ans+A[j]*fac[j]%P*pow2)%P;
        pow2=pow2*2%P;
    }
    cout<<ans<<endl;
    return 0;
}