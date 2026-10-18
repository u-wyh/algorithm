// https://www.luogu.com.cn/problem/P9060
#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int MAXN = 1e5+5;
const int MOD = 998244353;
const int MAXB = 316;

int n,m;
int val[MAXN];

int prime[MAXN];
int primecnt;
bool vis[MAXN];
int minprime[MAXN];

struct node{
    int l,r,id;
};
node nums[MAXN];
int ans[MAXN];

int con[MAXN];
int pre[MAXN];

void prepare(int n){
    for(int i=2;i<=n;i++){
        if(!vis[i]){
            prime[++primecnt]=i;
            minprime[i]=i;
        }
        for(int j=1;j<=primecnt&&i*prime[j]<=n;j++){
            vis[i*prime[j]]=true;
            minprime[i*prime[j]]=prime[j];
            if(i%prime[j]==0){
                break;
            }
        }
    }
}

void solve_small(){
    for(int i=1;i<=primecnt;i++){
        int v=prime[i];

        if(v>MAXB){
            break;
        }
        
        con[0]=1;
        for(int i=1;i<=n;i++){
            con[i]=con[i-1]*con[i-1]%MOD*v%MOD;
        }

        for(int j=v;j<=100000;j*=v){
            pre[0]=0;
            for(int p=1;p<=n;p++){
                pre[p]=pre[p-1];
                if(val[p]%j==0){
                    pre[p]++;
                }
            }

            for(int q=1;q<=m;q++){
                int l=nums[q].l;
                int r=nums[q].r;
                int id=nums[q].id;
                ans[id]=(ans[id]*con[pre[r]-pre[l-1]])%MOD;
            }
        }

    }
}

int sorted[MAXN];
int offset[MAXN];
int mul[MAXN];
int inv[MAXN];
int pos[MAXN];
int len[MAXN];
int bi[MAXN];

int cnt[MAXN];
int res=1;

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

void calc(int st,int len,int val){
    mul[st]=val;
    inv[st]=power(mul[st],MOD-2);
    for(int i=1;i<len;i++){
        mul[st+i]=mul[st+i-1]*mul[st+i-1]%MOD;
        inv[st+i]=power(mul[st+i],MOD-2);
    }
}

bool cmp(node &a,node &b){
    if (bi[a.l] != bi[b.l]) {
        return bi[a.l] < bi[b.l];
    }
    if ((bi[a.l] & 1) == 1) {
        return a.r < b.r;
    } else {
        return a.r > b.r;
    }
}

void add(int x){
    int v=val[x];
    int c=cnt[v];
    res=(res*mul[offset[v]+c])%MOD;
    cnt[v]++;
}

void del(int x){
    int v=val[x];
    int c=cnt[v];
    res=(res*inv[offset[v]+c-1])%MOD;
    cnt[v]--;
}

void compute(){
    int winl=1,winr=0;
    for (int i = 1; i <= m; i++) {
        int jobl = nums[i].l;
        int jobr = nums[i].r;
        // 先扩张后收缩，避免空窗口时删掉未加入的元素。
        while (winl > jobl) {
            add(--winl);
        }
        while (winr < jobr) {
            add(++winr);
        }
        while (winl < jobl) {
            del(winl++);
        }
        while (winr > jobr) {
            del(winr--);
        }
        ans[nums[i].id] *=res;
        ans[nums[i].id]%=MOD;
    }
}

void solve_big(){
    for(int i=1;i<=n;i++){
        while(true){
            if(val[i]==1){
                break;
            }
            if(minprime[val[i]]>MAXB){
                break;
            }
            val[i]/=minprime[val[i]];
        }
        sorted[i]=val[i];
    }

    sort(sorted+1,sorted+n+1);
    int now=0;
    for(int i=1;i<=n;i++){
        now++;
        if(sorted[i]!=sorted[i-1]){
            len[sorted[i]]=1;
            offset[sorted[i]]=now;
        }
        else{
            len[sorted[i]]++;
        }
    }
    for(int i=1;i<=n;i++){
        if(sorted[i]!=sorted[i-1]){
            calc(offset[sorted[i]],len[sorted[i]],sorted[i]);
        }
    }

    int blen=sqrt(n);
    for(int i=1;i<=n;i++){
        bi[i]=(i-1)/blen+1;
    }
    sort(nums+1,nums+m+1,cmp);
    compute();
}

signed main()
{
    prepare(100000);

    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>val[i];
    }
    for(int i=1;i<=m;i++){
        cin>>nums[i].l>>nums[i].r;
        nums[i].id=i;
        ans[i]=1;
    }

    solve_small();
    solve_big();
    
    for(int i=1;i<=m;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}