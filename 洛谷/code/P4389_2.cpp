// https://www.luogu.com.cn/problem/P4389
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN=1e5+5;
const int MAXT=4e5+5;
const int P=998244353;
const int g=3;
const int gi=332748118;

int n,m;
int val[MAXN];
int cnt[MAXN];
int sorted[MAXN];
int A[MAXT];
int B[MAXT];
int a[MAXN<<1];
int b[MAXN<<1];
int inv[MAXN<<1];

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

void merge(int l,int mid,int r){
    int len=mid-l+1;
    len<<=1;
    for(int i=0;i<len;i++){
        B[i]=b[i];
        A[i]=(i<len/2)?a[l+i]:0;
    }
    NTT(A,len,1);
    NTT(B,len,1);
    for(int i=0;i<len;i++){
        A[i]=A[i]*B[i]%P;
    }
    NTT(A,len,-1);
    int invlen=qpow(len,P-2);
    for(int i=0;i<len;i++){
        A[i]=A[i]*invlen%P;
    }
    for(int i=mid+1;i<=r;i++){
        int pos=i-l;
        a[i]=(a[i]+A[pos])%P;
    }
}

void cdq(int l,int r){
    if(l==r){
        if(l!=0){
            a[l]=a[l]*inv[l]%P;
        }
        return ;
    }
    int mid=(l+r)>>1;
    cdq(l,mid);
    merge(l,mid,r);
    cdq(mid+1,r);
}

signed main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>val[i];
    }

    sort(val+1,val+n+1);
    int valcnt=0;
    for(int i=1;i<=n;i++){
        if(val[i]!=val[i-1]){
            sorted[++valcnt]=val[i];
        }
        cnt[val[i]]++;
    }

    for(int i=1;i<=valcnt;i++){
        int v=sorted[i];
        for(int j=v-1;j<=m;j+=v){
            b[j+1]+=v*cnt[v];
        }
    }

    int len=1;
    while(len<(m+1)){
        len<<=1;
    }
    inv[1]=1;
    for(int i=2;i<=len;i++){
        inv[i]=(P-P/i*inv[P%i]%P+P)%P;
    }
    a[0]=1;
    cdq(0,len-1);

    for(int i=1;i<=m;i++){
        cout<<a[i]<<endl;
    }
    return 0;
}