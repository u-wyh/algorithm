#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 4e6+5;
const int g = 3;
const int P = 998244353;

int n,m,invg,invn;
int A[MAXN],B[MAXN],G[MAXN];
char s[MAXN];

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

void change(int x){
    for(int i=0;i<n;i++){
        B[i]=G[i];
    }
    B[0]+=x;
    NTT(A,n,1);
    NTT(B,n,1);
    for(int i=0;i<n;i++){
        A[i]=(A[i]*B[i])%P;
    }
    NTT(A,n,-1);
    for(int i=0;i<n;i++){
        A[i]=A[i]*invn%P;
    }

    int now=0;
    for(int i=0;i<n;i++){
        now=A[i]+now;
        A[i]=now%10;
        now/=10;
    }
}

signed main()
{
    scanf("%s",s);
    int len=strlen(s);
    for(int i=0;i<len;i++){
        G[i]=s[len-i-1]-'0';
    }
    n=1;
    while(n<=len*4){
        n<<=1;
    }
    for(int i=0;i<n;i++){
        rev[i]=(rev[i>>1]>>1)+((i&1)?(n>>1):0);
    }
    invg=power(g,P-2);
    invn=power(n,P-2);

    A[0]=1;
    for(int i=0;i<n;i++){
        A[i]+=G[i];
    }

    change(2);
    change(3);
    change(4);

    int now=0;
    for(int i=0;i<n;i++){
        now=A[i]+now;
        A[i]=now%10;
        now/=10;
    }

    for(int i=n-1;i>=1;i--){
        A[i-1]+=(A[i]%24)*10;
        A[i]/=24;
    }
    A[0]/=24;

    int k=n;
    while(k>1&&!A[k-1]){
        k--;
    }
    for(int i=k-1;i>=0;i--){
        cout<<A[i];
    }
    return 0;
}