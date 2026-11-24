// 用途：随机权重集合哈希，判断区间里每个值的出现次数是否都能被 k 整除，支持单点赋值。
// 时间：离散化 O((n+q)log(n+q))，T 轮检验 O(T(n+q)log n)，这里 T=20。
// 空间：O(n+q)。
// 注意：蒙特卡洛算法；NO 一定正确，YES 有极小误判概率；k≥1，n,q≤300000。
// 例题：https://www.luogu.com.cn/problem/CF1746F
// 题意：单点修改数组，询问某区间中每种数字的出现次数是否都是 k 的倍数。
// 思路：给每个值赋独立随机权重；合法区间的权重和必被 k 整除，重复多轮排除误判。
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 3e5+5;
const int MOD = 1e9+7;

int n,q,m=1;
int nums[MAXN];
int tmp[MAXN<<1];
bool ans[MAXN];
int cnt;
int h[MAXN<<1];

int op[MAXN];
int l[MAXN],r[MAXN],k[MAXN];
int pos[MAXN],v[MAXN];

int tree[MAXN];
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

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

void add(int x,int v){
    while(x<=n){
        tree[x]+=v;
        x+=lowbit(x);
    }
}

int query(int x){
    int ans=0;
    while(x){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}

int find(int val){
    int l=1,r=m,ans=1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(tmp[mid]>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

signed main()
{
    n=read(),q=read();
    for(int i=1;i<=n;i++){
        nums[i]=read();
        tmp[i]=nums[i];
    }
    cnt=n;
    for(int i=1;i<=q;i++){
        ans[i]=true;
        op[i]=read();
        if(op[i]==1){
            pos[i]=read(),v[i]=read();
            tmp[++cnt]=v[i];
        }
        else{
            l[i]=read(),r[i]=read(),k[i]=read();
        }
    }
    sort(tmp+1,tmp+cnt+1);
    for(int i=2;i<=cnt;i++){
        if(tmp[i]!=tmp[i-1]){
            tmp[++m]=tmp[i];
        }
    }
    for(int i=1;i<=n;i++){
        nums[i]=find(nums[i]);
    }
    for(int i=1;i<=q;i++){
        if(op[i]==1){
            v[i]=find(v[i]);
        }
    }
    for(int i=1;i<=n;i++){
        tmp[i]=nums[i];
    }

    int T=20;
    while(T--){
        for(int i=1;i<=n;i++){
            tree[i]=0;
            nums[i]=tmp[i];
        }
        // 每轮重新给离散后的每个值赋随机权重，误判概率随轮数下降。
        for(int i=1;i<=m;i++){
            h[i]=rng()%MOD;
        }
        for(int i=1;i<=n;i++){
            add(i,h[nums[i]]);
        }
        for(int i=1;i<=q;i++){
            if(op[i]==1){
                add(pos[i],h[v[i]]-h[nums[pos[i]]]);
                nums[pos[i]]=v[i];
            }
            else{
                if(ans[i]){
                    if((r[i]-l[i]+1)%k[i]){
                        ans[i]=false;
                    }
                    // 频次都为 k 的倍数时，权重和必为 k 的倍数；逆命题仅概率成立。
                    int all=query(r[i])-query(l[i]-1);
                    if(all%k[i]){
                        ans[i]=false;
                    }
                }
            }
        }
    }

    for(int i=1;i<=q;i++){
        if(op[i]==2){
            if(ans[i]){
                cout<<"YES"<<endl;
            }
            else{
                cout<<"NO"<<endl;
            }
        }
    }
    return 0;
}
