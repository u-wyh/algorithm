// https://www.luogu.com.cn/problem/P5641
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int MAXT = 4e5+5;
const int P = 998244353;
const int g = 3;
const int gi = 332748118;

int n,k;
int a[MAXN];
int f[MAXN];
int inv[MAXN];
int A[MAXT];
int B[MAXT];

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

void prepare(){
    inv[1]=1;
    for(int i=2;i<n;i++){
        inv[i]=(P-P/i)*inv[P%i]%P;
    }

    f[0]=1;
    for(int i=1;i<n;i++){
        f[i]=f[i-1]*(k+i-1)%P;
        f[i]=f[i]*inv[i]%P;
    }
}

signed main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        a[i]%=P;
    }

    prepare();

    for(int i=0;i<n;i++){
        A[i]=a[i+1]*f[i];
        B[i]=f[i];
    }
    int len=1;
    while(len<(2*n-1)){
        len<<=1;
    }

    NTT(A,len,1);
    NTT(B,len,1);
    for(int i=0;i<len;i++){
        A[i]=A[i]*B[i]%P;
    }
    NTT(A,len,-1);

    int invn=qpow(len,P-2);
    for(int i=0;i<len;i++){
        A[i]=A[i]*invn%P;
    }

    for(int i=0;i<n;i++){
        cout<<A[i]<<' ';
    }
    return 0;
}