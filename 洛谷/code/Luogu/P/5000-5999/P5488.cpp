#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 4e5+5;
const int g = 3;
const int P = 1004535809;

int n,op,m,invg,invn;
char s[MAXN];
int A[MAXN],B[MAXN];
int inv[MAXN];

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
    scanf("%lld",&n);
    scanf("%s",s);
    scanf("%lld",&op);
    for(int i=0;i<n;i++){
        scanf("%lld",&A[i]);
    }

    m=0;
    int len=strlen(s);
    for(int i=0;i<len;i++){
        m=(m*10+s[i]-'0')%P;
    }

    len=n;
    n=1;
    while(n<=2*len){
        n<<=1;
    }
    invg=power(g,P-2);
    invn=power(n,P-2);

    inv[1]=1;
    for(int i=2;i<=len;i++){
        inv[i]=(P-(inv[P%i]*(P/i)%P))%P;
    }

    B[0]=1;
    if(op==0){
        for(int i=1;i<len;i++){
            B[i]=(B[i-1]*(m+i-1))%P;
            B[i]=(B[i]*inv[i])%P;
        }
    }
    else{
        for(int i=1;i<len;i++){
            B[i]=(-B[i-1]*(m-i+1+P)%P)%P;
            B[i]=(B[i]*inv[i])%P;
        }
        // for(int i=1;i<len;i++){
        //     cout<<B[i]<<' ';
        // }
        // cout<<endl;
    }

    NTT(A,n,1);
    NTT(B,n,1);
    for(int i=0;i<n;i++){
        A[i]=(A[i]*B[i])%P;
    }
    NTT(A,n,-1);
    for(int i=0;i<len;i++){
        printf("%lld ",A[i]*invn%P);
    }
    return 0;
}