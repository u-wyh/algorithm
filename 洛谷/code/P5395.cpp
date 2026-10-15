// https://www.luogu.com.cn/problem/P5395

#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN=2e5+5;
const int MAXT=1<<20;
const int P=167772161;
const int g=3;
const int gi=55924054;

int n;
int A[MAXT],B[MAXT];
int fac[MAXN],invfac[MAXN];

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

    vector<int> A1(n/2),A2(n/2);

    // 拆分奇偶项
    for(int i=0;i<n/2;i++){
        A1[i]=A[i*2];
        A2[i]=A[i*2+1];
    }

    // 递归分治
    NTT(A1.data(),n/2,op);
    NTT(A2.data(),n/2,op);

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

signed main(){
    scanf("%lld",&n);

    // 预处理阶乘和逆阶乘
    fac[0]=1;
    for(int i=1;i<=n;i++){
        fac[i]=fac[i-1]*i%P;
    }

    invfac[n]=qpow(fac[n],P-2);
    for(int i=n;i>=1;i--){
        invfac[i-1]=invfac[i]*i%P;
    }

    // A[i] = i^n / i!
    // B[i] = (-1)^i / i!
    for(int i=0;i<=n;i++){
        A[i]=qpow(i,n)*invfac[i]%P;

        if(i&1){
            B[i]=(P-invfac[i])%P;
        }
        else{
            B[i]=invfac[i];
        }
    }

    // 补零到 2 的整数次幂
    int len=1;
    while(len<=2*n){
        len<<=1;
    }

    // 正变换
    NTT(A,len,1);
    NTT(B,len,1);

    // 对应点值相乘
    for(int i=0;i<len;i++){
        A[i]=A[i]*B[i]%P;
    }

    // 逆变换
    NTT(A,len,-1);

    // 乘以 len 的逆元
    int invlen=qpow(len,P-2);
    for(int i=0;i<len;i++){
        A[i]=A[i]*invlen%P;
    }

    // 输出第 n 行斯特林数
    for(int i=0;i<=n;i++){
        printf("%lld ",A[i]);
    }

    return 0;
}
