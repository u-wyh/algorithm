#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 19961993;
const int MAXN = 1e5+5;

int n,m;

int tree[61][MAXN];
// int p[61][61];
int prime[61]={0,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,
            139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281};
int val[MAXN];

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

inline int lowbit(int x){
    return x&-x;
}

void add(int x,int y,int v){
    while(y<=n){
        tree[x][y]+=v;
        y+=lowbit(y);
    }
}

int sum(int x,int y){
    int ans=0;
    while(y){
        ans+=tree[x][y];
        y-=lowbit(y);
    }
    return ans;
}

int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%MOD;
        }
        a=(a*a)%MOD;
        b>>=1;
    }
    return ans;
}

signed main()
{
    n=100000;
    m=read();
    for(int i=1;i<=n;i++){
        val[i]=3;
        add(2,i,1);
    }
    // for(int i=1;i<=60;i++){
    //     p[i][0]=p[i][1]=1;
    //     for(int j=2;j<=60;j++){
    //         p[i][j]=(p[i][j-1]*prime[i])%MOD;
    //     }
    //     for(int j=1;j<=60;j++){
    //         p[i][j]=(p[i][j]*(prime[i]-1))%MOD;
    //     }
    // }
    while(m--){
        int op,u,v;
        op=read(),u=read(),v=read();
        if(op==0){
            int ans=1;
            for(int i=1;i<=60;i++){
                int k=sum(i,v)-sum(i,u-1);
                if(k>0)
                    ans=(ans*power(prime[i],k-1)%MOD*(prime[i]-1))%MOD;
            }
            cout<<ans<<endl;
        }
        else{
            int tmp=val[u];
            for(int i=1;i<=60;i++){
                int k=0;
                while(tmp%prime[i]==0){
                    k++;
                    tmp/=prime[i];
                }
                if(k){
                    add(i,u,-k);
                }
            }
            val[u]=v;
            for(int i=1;i<=60;i++){
                int k=0;
                while(v%prime[i]==0){
                    k++;
                    v/=prime[i];
                }
                if(k){
                    add(i,u,k);
                }
            }
        }
    }
    return 0;
}