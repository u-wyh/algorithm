#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e6+5;
const int MOD = 998244353;

int a,b,c,d;
int prime[MAXN];
int num[MAXN];
int cnt=0;

int gcd(int a,int b){
    return b==0?a:gcd(b,a%b);
}

int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%MOD;
        }
        b>>=1;
        a=(a*a)%MOD;
    }
    return ans;
}

int euler(int n){
    for(int i=2;i<=n;i++){
        if(num[i]==0){
            prime[++cnt]=i;
            num[i]=i;
        }

        for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
            num[i*prime[j]]=prime[j];
            if(i%prime[j]==0){
                break; 
            }
        }
    }
    return cnt;
}

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

bool isprime(int n){
    for(int i=1;prime[i]*prime[i]<=n;i++){
        if(n%prime[i]==0){
            return false;
        }
    }
    return true;
}

signed main()
{
    euler(MAXN-1);
    int T=read();
    while(T--){
        int ans=1;
        a=read(),b=read(),c=read(),d=read();
        int g=gcd(a,c);
        int A=a/g;
        int C=c/g;
        int ga=gcd(A,g);
        int gc=gcd(C,g);
        int p1=0,p2=0;

        for(int i=1;i<=cnt&&prime[i]*prime[i]<=ga&&ga>1000000;i++){
            int p=prime[i];
            p1=0,p2=0;
            if(ga%p==0){
                while(ga%p==0){
                    ga/=p;
                }
                while(A%p==0){
                    p1++;
                    A/=p;
                }
                if(g%p==0){
                    while(g%p==0){
                        p1++,p2++;
                        g/=p;
                    }
                }
                ans=(ans*power(p,min(p1*b,p2*d)))%MOD;
            }
        }
        if(ga>1000000&&isprime(ga)){
            g/=ga;
            ans=(ans*power(ga,min(2*b,d)))%MOD;
        }
        
        for(int i=1;i<=cnt&&prime[i]<=1000&&gc>1000000;i++){
            int p=prime[i];
            p1=0,p2=0;
            if(gc%p==0){
                while(gc%p==0){
                    gc/=p;
                }
                while(C%p==0){
                    p2++;
                    C/=p;
                }
                if(g%p==0){
                    while(g%p==0){
                        p1++,p2++;
                        g/=p;
                    }
                }
                ans=(ans*power(p,min(p1*b,p2*d)))%MOD;
            }
        }
        if(gc>1000000&&isprime(gc)){
            g/=gc;
            ans=(ans*power(gc,min(b,2*d)))%MOD;
        }

        while(ga!=1){
            p1=0,p2=0;
            int p=num[ga];
            while(ga%p==0){
                ga/=p;
            }
            while(A%p==0){
                p1++;
                A/=p;
            }
            if(g%p==0){
                while(g%p==0){
                    p1++,p2++;
                    g/=p;
                }
            }
            ans=(ans*power(p,min(p1*b,p2*d)))%MOD;
        }
        while(gc!=1){
            p1=0,p2=0;
            int p=num[gc];
            while(gc%p==0){
                gc/=p;
            }
            while(C%p==0){
                p2++;
                C/=p;
            }
            if(g%p==0){
                while(g%p==0){
                    p1++,p2++;
                    g/=p;
                }
            }
            ans=(ans*power(p,min(p1*b,p2*d)))%MOD;
        }
        ans=(ans*power(g,min(b,d)))%MOD;
        ans=(ans%MOD+MOD)%MOD;
        cout<<ans<<endl;
    }
    return 0;
}