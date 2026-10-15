// https://www.luogu.com.cn/problem/P4841
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e6+5;
const int MAXT = 6e6+5;
const int P = 1004535809;
const int g = 3;
const int gi = 334845270;

int n;
int a[MAXN];
int b[MAXN];
int c[MAXN];
int A[MAXT];
int B[MAXT];
int C[MAXT];
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

// 多项式求逆
// 求 b(x)=a(x)^(-1) mod x^n
void poly_inv(int n){
    if(n==1){
        b[0]=qpow(a[0],P-2);
        return;
    }

    poly_inv(n>>1);
    int len=n<<1;

    // 构造多项式
    // A 为 a 的前 n 项
    // B 为已经求出的 b 的前 n/2 项
    for(int i=0;i<len;i++){
        A[i]=(i<n?a[i]:0);
        B[i]=(i<n/2?b[i]:0);
    }

    NTT(A,len,1);
    NTT(B,len,1);
    for(int i=0;i<len;i++){
        int t=(2-A[i]*B[i]%P+P)%P;
        A[i]=B[i]*t%P;
    }
    NTT(A,len,-1);

    int invn=qpow(len,P-2);
    for(int i=0;i<n;i++){
        b[i]=A[i]*invn%P;
    }
}

signed main()
{
    cin>>n;

    fac[0]=1;
    for(int i=1;i<=n;i++){
        fac[i]=fac[i-1]*i%P;
    }
    invfac[n]=qpow(fac[n],P-2);
    for(int i=n;i>=1;i--){
        invfac[i-1]=invfac[i]*i%P;
    }
    inv[1]=1;
    for(int i=2;i<=n;i++){
        inv[i]=(P-P/i*inv[P%i]%P)%P;
    }

    int m=1;
    while(m<=n){
        m<<=1;
    }

    for(int i=0;i<=n;i++){
        int t=i*(i-1)/2;
        c[i]=qpow(2,t);
        a[i]=c[i]*invfac[i]%P;
    }

    poly_inv(m);

    for(int i=0;i<2*m;i++){
        A[i]=0;
        B[i]=0;
    }
    for(int i=1;i<=n;i++){
        A[i]=c[i]*invfac[i-1]%P;
    }

    for(int i=0;i<m;i++){
        B[i]=b[i];
    }
    m<<=1;

    NTT(A,m,1);
    NTT(B,m,1);
    for(int i=0;i<m;i++){
        A[i]=A[i]*B[i]%P;
    }
    NTT(A,m,-1);
    int invm=qpow(m,P-2);
    for(int i=0;i<m;i++){
        A[i]=A[i]*invm%P;
    }

    int ans=A[n]*fac[n-1]%P;
    cout<<ans<<endl;
    return 0;
}