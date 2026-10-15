// https://www.luogu.com.cn/problem/P6300
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int MAXT = 4e5+5;
const int P=998244353;
const int g=3;
const int gi=332748118;

int n,m,T=18;
int A[MAXT];
int B[MAXT];
int rev[MAXT];

int all[MAXT];

int cnt[MAXN];

int len;
int lenVal[MAXN];

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

void compute(int limit){
    int len=1;
    while(len<2*m+1){
        len<<=1;
    }

    for(int i=0;i<len;i++){
        A[i]=0;
    }
    for(int i=1;i<=m;i++){
        if(cnt[i]>=limit){
            A[i]=1;
        }
    }
    NTT(A,len,1);
    for(int i=0;i<len;i++){
        A[i]=A[i]*A[i]%P;
    }
    NTT(A,len,-1);
    int invlen=qpow(len,P-2);
    for(int i=0;i<len;i++){
        A[i]=A[i]*invlen%P;
    }

    for(int i=0;i<=2*m;i++){
        if(A[i]){
            all[i]+=A[i];
        }
    }
}

signed main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        int val;
        cin>>val;
        cnt[val]++;
    }

    for(int i=1;i<=T;i++){
        compute(i);
    }

    for(int i=1;i<=m;i++){
        if(cnt[i]>T){
            lenVal[++len]=i;
        }
    }
    for(int i=1;i<=len;i++){
        for(int j=1;j<=len;j++){
            int v1=lenVal[i];
            int v2=lenVal[j];
            all[v1+v2]+=(min(cnt[v1],cnt[v2])-T);
        }
    }

    for(int i=2;i<=2*m;i++){
        if((i%2==0)&&(cnt[i/2]&1)){
            all[i]--;
        }
        all[i]/=2;
    }

    int maxans=0,minval=0;
    for(int i=2;i<=2*m;i++){
        if(all[i]>maxans){
            maxans=all[i];
            minval=i;
        }
    }
    cout<<maxans<<' '<<minval<<endl;
    return 0;
}