#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e7+5;
const int MAXK = 1<<11;
const int MAXM = 205;
const long long INF = 1e18;

unsigned int SA, SB, SC;
int p, A, B;

int n,k,m;
int a[MAXN];
int b[MAXN];
int id[MAXN];

long long f[MAXK][MAXM];
long long val[MAXK][MAXM];
long long cost[MAXK][MAXM];

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

// 随机数生成器
unsigned int rng61(){
    SA ^= SA << 16;
    SA ^= SA >> 5;
    SA ^= SA << 1;
    unsigned int t = SA;
    SA = SB;
    SB = SC;
    SC ^= t ^ SA;
    return SC;
}

void gen(){
    // 读取输入参数
    n = read(), k = read() + 1, m = read(), p = read();
    SA = read(), SB = read(), SC = read(), A = read(), B = read();
    
    // 读取前p个钻石的数据
    for(int i = 1; i <= p; i++) {
        a[i] = read() % m;  // 对m取模，因为我们只关心模m的结果
        b[i] = read();
    }
    // 生成剩余钻石的数据
    for(int i = p + 1; i <= n; i++){
        a[i] = rng61() % A + 1;
        b[i] = rng61() % B + 1;
        a[i] %= m;  // 对m取模
    }
}

int main()
{
    int T=read();
    while(T--){
        gen();
        for(int i=0;i<(1<<k);i++){
            for(int j=0;j<=m;j++){
                f[i][j]=INF;
                val[i][j]=0;
                cost[i][j]=0;
            }
        }

        for(int i=1;i<(1<<k);i++){
            id[i]=i;
        }
        for(int i=(1<<k);i<=n;i++){
            id[i]=id[i>>k];
        }
        for(int i=1;i<=n;i++){
            cost[id[i]][a[i]]+=b[i];
        }
        for(int i=1;i<(1<<k);i++){
            for(int j=0;j<m;j++){
                for(int p=0;p<m;p++){
                    if(p<=j){
                        val[i][j]+=cost[i][p]*(j-p);
                    }
                    else{
                        val[i][j]+=cost[i][p]*(j+m-p);
                    }
                }
            }
        }
        for(int i=(1<<(k-1));i<(1<<k);i++){
            for(int j=0;j<m;j++){
                f[i][j]=val[i][j];
            }
        }
        for(int i=(1<<(k-1))-1;i>=1;i--){
            for(int j=0;j<m;j++){
                for(int p=0;p<m;p++){
                    int target=(j-p+m)%m;
                    if(f[i<<1][p]<INF&&f[i<<1|1][p]<INF){
                        f[i][j]=min(f[i][j],f[i<<1][p]+f[i<<1|1][p]+val[i][target]);
                    }
                }
            }
        }
        printf("%lld\n",f[1][0]);
        for(int i=1;i<=n;i++){
            a[i]=0;
            b[i]=0;
        }
    }
    return 0;
}