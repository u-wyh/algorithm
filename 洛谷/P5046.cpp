#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 1e3+5;

int n,m;
int nums[MAXN];

struct node{
    int val,sub;
}arr[MAXN];

int blen,bnum;
int bl[MAXM];
int br[MAXM];
int bi[MAXN];

int tree[MAXN];

int pre[MAXN];
int suf[MAXN];
int cnt[MAXM][MAXN];
long long dp[MAXM][MAXM];

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

inline int f(int x,int xl,int xr,int y,int yl,int yr){
    int ans=0;
    int cnt=0;
    for(int p1=bl[x],p2=bl[y]-1;p1<=br[x];p1++){
        if(arr[p1].sub>=xl&&arr[p1].sub<=xr){
            while(p2+1<=br[y]&&arr[p2+1].val<arr[p1].val){
                p2++;
                if(yl<=arr[p2].sub&&yr>=arr[p2].sub){
                    cnt++;
                }
            }
            ans+=cnt;
        }
    }
    return ans;
}

long long query(int l,int r){
    if(bi[l]==bi[r]){
        if(l==bl[bi[l]]){
            return pre[r];
        }
        else if(r==br[bi[l]]){
            return suf[l];
        }
        else{
            return pre[r]-pre[l-1]-f(bi[l],bl[bi[l]],l-1,bi[l],l,r);
        }
    }
    else{
        int lb=bi[l],rb=bi[r];
        long long ans=0;
        ans=suf[l]+pre[r]+dp[lb+1][rb-1]+f(lb,l,br[lb],rb,bl[rb],r);
        for(int i=l;i<=br[lb];i++){
            ans+=cnt[rb-1][nums[i]]-cnt[lb][nums[i]];
        }
        for(int i=bl[rb];i<=r;i++){
            ans+=br[rb-1]-bl[lb+1]+1-(cnt[rb-1][nums[i]]-cnt[lb][nums[i]]);
        }
        return ans;
    }
}

bool cmp(node a,node b){
    return a.val<b.val;
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

void prepare(){
    blen=max(1,(int)sqrt(n/5));
    bnum=(n+blen-1)/blen;
    for(int i=1;i<=n;i++){
        bi[i]=(i-1)/blen+1;
    }
    for(int i=1;i<=bnum;i++){
        bl[i]=(i-1)*blen+1;
        br[i]=min(n,i*blen);
    }
    for(int i=1;i<=n;i++){
        arr[i].val=nums[i];
        arr[i].sub=i;
    }
    for(int i=1;i<=bnum;i++){
        sort(arr+bl[i],arr+br[i]+1,cmp);
    }
    for(int i=1;i<=bnum;i++){
        for(int j=bl[i];j<=br[i];j++){
            cnt[i][nums[j]]++;
            if(j!=bl[i]){
                pre[j]=pre[j-1]+query(n)-query(nums[j]);
            }
            add(nums[j],1);
        }
        for(int j=bl[i];j<=br[i];j++){
            add(nums[j],-1);
        }

        for(int j=br[i];j>=bl[i];j--){
            if(j!=br[i]){
                suf[j]=suf[j+1]+query(nums[j]);
            }
            add(nums[j],1);
        }
        for(int j=bl[i];j<=br[i];j++){
            add(nums[j],-1);
        }

        int tmp=0;
        for(int j=1;j<=n;j++){
            tmp+=cnt[i][j];
            cnt[i][j]=tmp+cnt[i-1][j];
        }
    }
    for (int l = bnum; l >= 1; l--) {
        dp[l][l] = pre[br[l]];
        for (int r = l + 1; r <= bnum; r++) {
            dp[l][r] = dp[l + 1][r] + dp[l][r - 1] - dp[l + 1][r - 1] + f(l, bl[l], br[l], r, bl[r], br[r]);
        }
    }
    // for(int i=1;i<=bnum;i++){
    //     dp[i][i]=pre[br[i]];
    // }
    // for(int len=2;len<=bnum;len++){
    //     for(int l=1;l<=bnum-len+1;l++){
    //         int r=len+l-1;
    //         dp[l][r]=(dp[l+1][r]+dp[l][r-1]-dp[l+1][r-1]+f(l,bl[l],br[l],r,bl[r],br[r]));
    //     }
    // }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        nums[i]=read();
    }
    prepare();
    long long ans=0;
    for(int i=1;i<=m;i++){
        int l,r;
        l=read()^ans;
        r=read()^ans;
        ans=query(l,r);
        printf("%lld\n",ans);
    }
    return 0;
}