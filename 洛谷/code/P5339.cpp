// https://www.luogu.com.cn/problem/P5339
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1005;
const int MAXT = 4005;
const int P = 998244353;
const int g = 3;
const int gi = 332748118;

int n,a,b,c,d;
int A[MAXT];
int B[MAXT];
int C[MAXT];
int D[MAXT];
int fac[MAXN];
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
    cin>>n>>a>>b>>c>>d;

    fac[0]=1;
    for(int i=1;i<=n;i++){
        fac[i]=(fac[i-1]*i)%P;
    }
    inv[n]=qpow(fac[n],P-2);
    for(int i=n-1;i>=0;i--){
        inv[i]=(inv[i+1]*(i+1))%P;
    }

    int kmax=min({n/4,a,b,c,d});
    int ans=0;

    for(int k=0;k<=kmax;k++){
        int t=n-4*k;
        int da=min(a-k,t);
        int db=min(b-k,t);
        int dc=min(c-k,t);
        int dd=min(d-k,t);

        int len=1;;
        while(len<=(da+db+dc+dd)){
            len<<=1;
        }

        for(int i=0;i<len;i++){
            A[i]=B[i]=C[i]=D[i]=0;
        }

        for(int i=0;i<=da;i++){
            A[i]=inv[i];
        }
        for(int i=0;i<=db;i++){
            B[i]=inv[i];
        }
        for(int i=0;i<=dc;i++){
            C[i]=inv[i];
        }
        for(int i=0;i<=dd;i++){
            D[i]=inv[i];
        }

        NTT(A,len,1);
        NTT(B,len,1);
        NTT(C,len,1);
        NTT(D,len,1);
        for(int i=0;i<len;i++){
            A[i]=(((A[i]*B[i])%P)*((C[i]*D[i])%P))%P;
        }
        NTT(A,len,-1);

        int coef=A[t]*qpow(len,P-2)%P;
        int term=coef*fac[n-3*k]%P*inv[k]%P;
        if(k&1){
            ans=(ans-term+P)%P;
        }
        else{
            ans=(ans+term)%P;
        }
    }
    cout<<ans<<endl;
    return 0;
}