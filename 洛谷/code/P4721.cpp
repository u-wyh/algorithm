// https://www.luogu.com.cn/problem/P4721
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN=1e5+5;
const int MAXT=4e5+5;
const int P=998244353;
const int g=3;
const int gi=332748118;

int n,m;
int A[MAXT],B[MAXT];

int a[MAXT];
int b[MAXT];

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

// 迭代 NTT
int rev[MAXT];
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

// // 递归 NTT
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

void merge(int l,int mid,int r){
    int len=(mid-l+1);
    len<<=1;

    for(int i=0;i<len/2;i++){
        A[i]=a[l+i];
    }
    for(int i=len/2;i<len;i++){
        A[i]=0;
    }

    for(int i=0;i<len;i++){
        B[i]=b[i];
    }

    NTT(A,len,1);
    NTT(B,len,1);
    for(int i=0;i<len;i++){
        A[i]=A[i]*B[i]%P;
    }
    NTT(A,len,-1);

    int invlen=qpow(len,P-2);
    for(int i=len/2;i<len;i++){
        int pos=mid+1+i-len/2;
        a[pos]=(a[pos]+A[i]*invlen)%P;
    }
}

void cdq(int l,int r){
    // cout<<l<<' '<<r<<endl;
    if(l==r){
        return ;
    }
    int mid=(l+r)>>1;
    cdq(l,mid);
    merge(l,mid,r);
    cdq(mid+1,r);
}

signed main()
{
    cin>>n;
    a[0]=1;
    for(int i=1;i<n;i++){
        cin>>b[i];
    }
    int m=1;
    while(m<n){
        m<<=1;
    }

    cdq(0,m-1);

    for(int i=0;i<n;i++){
        cout<<a[i]<<' ';
    }
    return 0;
}