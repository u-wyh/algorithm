#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int MAXT = 4e5+5;
const int P = 1004535809;
const int g = 3;
const int gi = 334845270;

int n,t;
int A[MAXT],B[MAXT];
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
    string s;
    cin>>n>>s>>t;
    for(int i=0;i<n;i++){
        cin>>A[i];
        A[i]%=P;
    }
    int k=0;
    for(char c:s){
        k=(k*10+c-'0')%P;
    }

    inv[1]=1;
    for(int i=2;i<n;i++){
        inv[i]=(P-P/i)*inv[P%i]%P;
    }

    B[0]=1;
    for(int i=1;i<n;i++){
        if(t==1){
            B[i]=B[i-1]*(i-1-k+P)%P;
        }
        else{
            B[i]=B[i-1]*(k+i-1)%P;
        }
        B[i]=B[i]*inv[i]%P;
    }

    int len=1;
    while(len<2*n-1){
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
    int invn=qpow(len,P-2);
    for(int i=0;i<len;i++){
        A[i]=A[i]*invn%P;
    }

    // 只输出前 n 项
    for(int i=0;i<n;i++){
        printf("%lld ",A[i]);
    }
    return 0;
}