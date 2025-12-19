// https://www.luogu.com.cn/problem/CF1746F
// 这道题的思路是进行T次独立检测 出现了k次的倍数 那么看看每次哈希值是否符合K倍的要求
// 这道题也是随机化的一道题目
// 思路是每次检测都是将原来的一个数字随机成另外一个数字，查询区间和是否可以整除k
// 这道题还有修改操作 所以不能预处理出前缀和数组
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
mt19937_64 rng(time(0));

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