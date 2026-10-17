// https://www.luogu.com.cn/problem/P4199
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int MAXT = 4e5+5;
const int MOD = 1e9+7;
const int P = 998244353;
const int g = 3;
const int gi = 332748118;

int n,m;
int A[MAXT];
int B[MAXT];
char a[MAXN];
char ss[MAXN<<1];
int p[MAXN<<1];
int pw[MAXN];

// 快速幂（NTT 模数）
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
        A[i]=(A1[i]+A2[i]*gk%P)%P;
        A[i+n/2]=(A1[i]-A2[i]*gk%P+P)%P;
        gk=gk*g1%P;
    }
}

void manacherss(){
    n=2*m+1;
    for(int i=0,j=0;i<n;i++){
        ss[i]=(i&1)?a[j++]:'#';
    }
}

int manacher(){
    manacherss();
    int ans=0;
    for(int i=0,r=0,c=0,len;i<n;i++){
        len=(r>i)?min(p[2*c-i],r-i):1;
        while(i+len<n&&i-len>=0&&ss[i+len]==ss[i-len]){
            len++;
        }
        if(i+len>r){
            r=i+len;
            c=i;
        }
        p[i]=len;
        ans+=len/2;
    }
    return ans;
}

signed main()
{
    scanf("%s",a);
    m=strlen(a);
    for(int i=0;i<m;i++){
        A[i]=a[i]=='a';
        B[i]=a[i]=='b';
    }

    int len=1;
    while(len<(2*m-1)){
        len<<=1;
    }
    NTT(A,len,1);
    NTT(B,len,1);
    for(int i=0;i<len;i++){
        A[i]=(A[i]*A[i]%P+B[i]*B[i]%P)%P;
    }
    NTT(A,len,-1);
    int invn=qpow(len,P-2);
    for(int i=0;i<len;i++){
        A[i]=A[i]*invn%P;
    }

    pw[0]=1;
    for(int i=1;i<=m;i++){
        pw[i]=pw[i-1]*2%MOD;
    }
    int ans=0;
    for(int t=0;t<=2*m-2;t++){
        int k=(A[t]+1)/2;
        ans=(ans+pw[k]-1+MOD)%MOD;
    }

    ans=(ans-manacher()+MOD)%MOD;
    ans=(ans+MOD)%MOD;
    cout<<ans<<endl;
    return 0;
}