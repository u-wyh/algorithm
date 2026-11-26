// https://www.luogu.com.cn/problem/P3803
// 题意：第一行输入两个多项式次数 n, m，随后两行分别从低次到高次输入 F(x) 的 n+1 个系数和 G(x) 的 m+1 个系数。
// 计算多项式乘积 F(x) * G(x)。
// 一行输出 n+m+1 个整数，从低次到高次表示乘积多项式的系数。
// 数据范围：对于 100% 的数据，0 <= n, m <= 10^6，输入系数均为 0 到 9 的整数。
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 4e6+5;
const int g = 3;
const int P = 998244353;

int n,m,invg,invn;
int A[MAXN],B[MAXN];

int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%P;
        }
        b>>=1;
        a=(a*a)%P;
    }
    return ans;
}

// void NTT(int *A,int n,int op){
//     if(n==1){
//         return ;
//     }
//     int A1[n/2],A2[n/2];
//     for(int i=0;i<n/2;i++){
//         A1[i]=A[i*2];
//         A2[i]=A[i*2+1];
//     }
//     NTT(A1,n/2,op);
//     NTT(A2,n/2,op);
//     int g1=power(op==1?g:invg,(P-1)/n);
//     int gk=1;
//     for(int i=0;i<n/2;i++){
//         A[i]=(A1[i]+A2[i]*gk)%P;
//         A[i+n/2]=(A1[i]-A2[i]*gk%P+P)%P;
//         gk=gk*g1%P;
//     }
// }

int rev[MAXN];
void NTT(int *A,int n,int op){
    for(int i=0;i<n;i++){
        rev[i]=(rev[i>>1]>>1)+((i&1)?(n>>1):0);
    }
    for(int i=0;i<n;i++){
        if(i<rev[i]){
            swap(A[i],A[rev[i]]);
        }
    }
    for(int m=2;m<=n;m<<=1){
        int g1=power(op==1?g:invg,(P-1)/m);
        for(int i=0;i<n;i+=m){
            int gk=1;
            for(int j=i;j<i+m/2;j++){
                int x=A[j],y=gk*A[j+m/2]%P;
                A[j]=(x+y)%P;
                A[j+m/2]=(x-y+P)%P;
                gk=gk*g1%P;
            }
        }
    }
}

signed main()
{
    scanf("%lld %lld",&n,&m);
    for(int i=0;i<=n;i++){
        scanf("%lld",&A[i]);
    }
    for(int i=0;i<=m;i++){
        scanf("%lld",&B[i]);
    }
    for(m=n+m,n=1;n<=m;n<<=1);
    invg=power(g,P-2);
    invn=power(n,P-2);
    NTT(A,n,1);
    NTT(B,n,1);
    for(int i=0;i<n;i++){
        A[i]=A[i]*B[i]%P;
    }
    NTT(A,n,-1);
    for(int i=0;i<=m;i++){
        printf("%lld ",A[i]*invn%P);
    }
    return 0;
}