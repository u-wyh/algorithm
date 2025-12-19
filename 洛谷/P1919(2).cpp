// https://www.luogu.com.cn/problem/P3803
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXT = 8e6+5;
const int MAXN = 1e6+5;
const int g = 3;
const int P = 998244353;

int n,m,invg,invn;
char s1[MAXN];
char s2[MAXN];
int A[MAXT],B[MAXT];
int ans[MAXT];

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

int rev[MAXT];
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
    scanf("%s %s",s1,s2);
    n=strlen(s1)-1,m=strlen(s2)-1;
    for(int i=0;i<=n;i++){
        A[i]=s1[n-i]-'0';
    }
    for(int i=0;i<=m;i++){
        B[i]=s2[m-i]-'0';
    }
    // n的值至少要大于最高项  也就是n+m 同时必须是2的幂次
    for(m=n+m,n=1;n<=m;n<<=1);
    invg=power(g,P-2);
    invn=power(n,P-2);
    NTT(A,n,1);
    NTT(B,n,1);
    for(int i=0;i<n;i++){
        A[i]=A[i]*B[i];
    }
    NTT(A,n,-1);
    // 此时的A数组求出来的是新值  需要除以n才是真正的值
    for(int i=0;i<=m;i++){
        A[i]=(A[i]*invn)%P;
    }

    int k=0;
    for(int i=0,t=0;i<n||t;i++){
        t+=A[i];
        ans[k++]=t%10;
        t/=10;
    }
    while(k>1&&!ans[k-1]){
        k--;
    }

    for(int i=k-1;i>=0;i--){
        cout<<ans[i];
    }
    return 0;
}