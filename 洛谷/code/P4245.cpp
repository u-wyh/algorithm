// https://www.luogu.com.cn/problem/P4245
#include<bits/stdc++.h>
using namespace std;
#define int long long
typedef __int128 i128;
const int MAXN = 1e5+5;
const int MAXT = 4e5+5;
const int P[3]={998244353,1004535809,469762049};
const int g=3;
const int gi[3]={332748118,334845270,156587350};

int n,m,len,mod;
int A[MAXT];
int B[MAXT];
int a[MAXN];
int b[MAXN];
int r[3][MAXT];
int ans[MAXT];
i128 val[MAXT];

int qpow(int a,int b,int P){
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
void NTT(int A[],int n,int op,int P,int g,int gi){
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
    NTT(A1,n/2,op,P,g,gi);
    NTT(A2,n/2,op,P,g,gi);

    // 单位根
    int g1=qpow(op==1?g:gi,(P-1)/n,P);
    int gk=1;

    // 蝶形运算
    for(int i=0;i<n/2;i++){
        A[i]=(A1[i]+A2[i]*gk)%P;
        A[i+n/2]=(A1[i]-A2[i]*gk%P+P)%P;
        gk=gk*g1%P;
    }
}

i128 d, x, y, px, py;
void exgcd(i128 a, i128 b) {
    if (b == 0) {
        d = a;
        x = 1;
        y = 0;
    } else {
        exgcd(b, a % b);
        px = x;
        py = y;
        x = py;
        y = px - py * (a / b);
    }
}

void crt(){
    i128 lcm=1;
    for (int i = 0; i < 3; i++) {
        lcm = lcm * P[i];
    }
    i128 ai;
    for(int op=0;op<3;op++){
        ai=lcm/P[op];
        exgcd(ai,P[op]);
        int t=(x%P[op]+P[op])%P[op];
        for(int i=0;i<=n+m;i++){
            i128 ci=(r[op][i]*ai)%lcm*t%lcm;
            val[i]=(val[i]+ci)%lcm;
        }
    }

    for(int i=0;i<=n+m;i++){
        ans[i]=val[i]%mod;
    }
}

signed main()
{
    cin>>n>>m>>mod;
    for(int i=0;i<=n;i++){
        cin>>a[i];
    }
    for(int i=0;i<=m;i++){
        cin>>b[i];
    }

    len=1;
    while(len<(n+m+1)){
        len<<=1;
    }

    for(int op=0;op<3;op++){
        for(int i=0;i<len;i++){
            A[i]=B[i]=0;
        }

        for(int i=0;i<=n;i++){
            A[i]=a[i]%P[op];
        }
        for(int i=0;i<=m;i++){
            B[i]=b[i]%P[op];
        }

        NTT(A,len,1,P[op],g,gi[op]);
        NTT(B,len,1,P[op],g,gi[op]);
        for(int i=0;i<len;i++){
            A[i]=A[i]*B[i]%P[op];
        }
        NTT(A,len,-1,P[op],g,gi[op]);
        int invlen=qpow(len,P[op]-2,P[op]);
        for(int i=0;i<len;i++){
            r[op][i]=A[i]*invlen%P[op];
        }
    }

    crt();

    for(int i=0;i<=n+m;i++){
        cout<<(ans[i]%mod)<<' ';
    }
    return 0;
}