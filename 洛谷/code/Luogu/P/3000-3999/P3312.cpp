#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 2e4+5;
const unsigned int MOD = 1U<<31;

int mu[MAXN];
int cnt;
bool vis[MAXN];
int prime[MAXN];

int primecnt[MAXN];  // 最小质因子的指数
int primesum[MAXN];  // 最小质因子的等比数列和
int sigma[MAXN];     // 约数之和

struct QUERY{
    int n,m,a,id;
};
QUERY query[MAXM];
int ans[MAXM];

struct node{
    int i,val;
};
node nums[MAXN];

unsigned int tree[MAXN];

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

void prepare(int n){
    cnt = 0;
    mu[1] = 1;
    sigma[1] = 1;
    primecnt[1] = 0;
    primesum[1] = 1;
    
    for(int i=2;i<=n;i++){
        if(!vis[i]){
            prime[++cnt] = i;
            mu[i] = -1;
            primecnt[i] = 1;
            primesum[i] = i + 1;
            sigma[i] = i + 1;
        }
        for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
            int p = prime[j];
            int num = i * p;
            vis[num]=true;
            
            if(i % p == 0){
                // p 是 i 的最小质因子
                mu[num] = 0;
                primecnt[num] = primecnt[i] + 1;
                primesum[num] = primesum[i] * p + 1;
                
                // 计算 sigma(num)
                // 令 i = p^k * m，其中 m 与 p 互质
                // 则 sigma(num) = sigma(m) * (1 + p + p^2 + ... + p^{k+1})
                int m = i;
                for(int k=0;k<primecnt[i];k++){
                    m /= p;
                }
                sigma[num] = sigma[m] * primesum[num];
                break;
            }
            else{
                // p 不是 i 的质因子
                mu[num] = -mu[i];
                primecnt[num] = 1;
                primesum[num] = p + 1;
                sigma[num] = sigma[i] * sigma[p];  // 积性函数性质
            }
        }
    }
}

bool cmp1(QUERY a,QUERY b){
    return a.a<b.a;
}

bool cmp2(node a,node b){
    return a.val<b.val;
}

int lowbit(int x){
    return x&-x;
}

void add(int x,int val){
    while(x<MAXN){
        tree[x]+=val;
        x+=lowbit(x);
    }
}

unsigned int sum(int x){
    unsigned int ans=0;
    while(x){
        ans+=tree[x];
        ans%=MOD;
        x-=lowbit(x);
    }
    return ans;
}

int main()
{
    prepare(MAXN-1);
    int Q=read();
    for(int i=1;i<=Q;i++){
        query[i].n=read(),query[i].m=read(),query[i].a=read();
        if(query[i].n>query[i].m){
            swap(query[i].n,query[i].m);
        }
        query[i].id=i;
    }
    sort(query+1,query+Q+1,cmp1);
    for(int i=1;i<MAXN;i++){
        nums[i]={i,sigma[i]};
    }
    sort(nums+1,nums+MAXN,cmp2);

    int now=1;
    for(int i=1;i<=Q;i++){
        int a=query[i].a;
        int n=query[i].n;
        int m=query[i].m;
        int id=query[i].id;

        while(now<MAXN&&nums[now].val<=a){
            int d=nums[now].i;
            int sigmad=nums[now].val;
             for(int T = d; T < MAXN; T += d){
                if(mu[T/d] != 0){
                    // 处理负号：如果 mu 为负，用 MOD - sigmad
                    if(mu[T/d] > 0){
                        add(T, sigmad);
                    } else {
                        add(T, (MOD - sigmad % MOD) % MOD);
                    }
                }
            }
            now++;
        }

        for(int l=1,r;l<=n;l=r+1){
            r=min(n/(n/l),m/(m/l));
            ans[id]+=1ull*(n/l)*(m/l)%MOD*((sum(r)-sum(l-1)+MOD)%MOD)%MOD;
            ans[id]%=MOD;
        }
    }

    for(int i=1;i<=Q;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}