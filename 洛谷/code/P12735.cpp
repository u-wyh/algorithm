// https://www.luogu.com.cn/problem/P12735
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN=1e6+5;
const int MAXT=4e6+5;
const int P=998244353;
const int g=3;
const int gi=332748118;

int n,a,b,m;
int A[MAXT];
int B[MAXT];
int fac[MAXN];
int inv[MAXN];

int rev[MAXT];
// 快速幂
inline int qpow(int a,int b){
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

// 递归 NTT
// void NTT(int A[],int n,int op){
//     if(n==1){
//         return;
//     }

//     int A1[n/2],A2[n/2];
//     // 拆分奇偶项
//     for(int i=0;i<n/2;i++){
//         A1[i]=A[i*2];
//         A2[i]=A[i*2+1];
//     }

//     // 递归分治
//     NTT(A1,n/2,op);
//     NTT(A2,n/2,op);

//     // 单位根
//     int g1=qpow(op==1?g:gi,(P-1)/n);
//     int gk=1;

//     // 蝶形运算
//     for(int i=0;i<n/2;i++){
//         A[i]=(A1[i]+A2[i]*gk)%P;
//         A[i+n/2]=(A1[i]-A2[i]*gk%P+P)%P;
//         gk=gk*g1%P;
//     }
// }

signed main()
{
    cin>>n>>a>>b;

    fac[0]=1;
    for(int i=1;i<=n;i++){
        fac[i]=fac[i-1]*i%P;
    }
    inv[n]=qpow(fac[n],P-2);
    for(int i=n-1;i>=0;i--){
        inv[i]=(inv[i+1]*(i+1))%P;
    }

    int inva=qpow(a,P-2);
    int aaa=inva;
    for(int i=1;i*a<=n;i++){
        int res=1;
        if(i&1){
            res=P-1;
        }

        res=(res*fac[a*i])%P;
        res=(res*inv[i])%P;
        res=(res*aaa)%P;
        aaa=(aaa*inva)%P;

        A[i*a]=res;
    }
    int invb=qpow(b,P-2);
    int bbb=invb;
    for(int i=1;i*b<=n;i++){
        int res=1;
        if(i&1){
            res=P-1;
        }

        res=(res*fac[b*i])%P;
        res=(res*inv[i])%P;
        res=(res*bbb)%P;
        bbb=(bbb*invb)%P;
        B[i*b]=res;
    }

    m=1;
    while(m<=2*n){
        m<<=1;
    }

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

    int ans=0;
    for(int i=0;i<=n;i++){
        int res=inv[i];
        res=res*A[i]%P;
        ans=(ans+res)%P;
    }
    ans=(ans*fac[n])%P;

    cout<<ans<<endl;
    return 0;
}