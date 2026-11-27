// https://www.luogu.com.cn/problem/P3245
// 题意：输入素数 p、数字串 S（长度 n，允许前导 0）、询问数 m，以及 m 个区间询问 [fr, to]。
// 对每个询问区间，统计 S[fr..to] 的所有非空连续子串中有多少个对应的十进制整数是 p 的倍数（0 也是 p 的倍数）。
// 输出 m 行，依次为每次询问满足条件的子串个数。
// 数据范围：1 <= n, m <= 2*10^5，2 <= p <= 10^9 且 p 为素数。
#include<bits/stdc++.h>
// 算法标签：莫队、离散化、前缀和
using namespace std;
#define int long long
const int MAXN = 2e5+5;
const int MAXB = 505;

int p,q,n,m;
char s[MAXN];

int f[MAXN];
int g[MAXN];

int blen;
int bi[MAXN];

int val[MAXN];
int arr[MAXN];
int cnt[MAXN];
int res;

struct node{
    int l,r,id;
};
node nums[MAXN];
int ans[MAXN];

bool cmp(node &a, node &b) {
    if (bi[a.l] != bi[b.l]) {
        return bi[a.l] < bi[b.l];
    }
    if ((bi[a.l] & 1) == 1) {
        return a.r < b.r;
    } else {
        return a.r > b.r;
    }
}

int find(int val){
    int l=1,r=m,ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(arr[mid]>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

void add(int val){
    res+=cnt[val];
    cnt[val]++;
}

void del(int val){
    cnt[val]--;
    res-=cnt[val];
}

signed main()
{
    scanf("%lld %s",&p,s+1);
    n=strlen(s+1);
    scanf("%lld",&q);
    if(p==2||p==5){
        for(int i=1;i<=n;i++){
            int val=s[i]-'0';
            if(val%p==0){
                f[i]=f[i-1]+1;
                g[i]=g[i-1]+i;
            }
            else{
                f[i]=f[i-1];
                g[i]=g[i-1];
            }
        }
        for(int i=1;i<=q;i++){
            int l,r;
            scanf("%lld %lld",&l,&r);
            int ans=(g[r]-g[l-1])-(l-1)*(f[r]-f[l-1]);
            printf("%lld\n",ans);
        }
    }
    else{
        val[n+1]=0;
        int power=1;
        for(int i=n;i>=1;i--){
            val[i]=((val[i+1]+(s[i]-'0')*power%p)%p+p)%p;
            power=(power*10)%p;
        }
        n++;
        for(int i=1;i<=n;i++){
            arr[i]=val[i];
        }
        sort(arr+1,arr+n+1);
        m=1;
        for(int i=2;i<=n;i++){
            if(arr[i]!=arr[i-1]){
                arr[++m]=arr[i];
            }
        }
        for(int i=1;i<=n;i++){
            val[i]=find(val[i]);
        }
        for(int i=1;i<=q;i++){
            int l,r;
            scanf("%lld %lld",&l,&r);
            nums[i]={l,r+1,i};
        }
        blen=sqrt(n);
        for(int i=1;i<=n;i++){
            bi[i]=(i-1)/blen+1;
        }
        sort(nums+1,nums+q+1,cmp);
        int winl=1,winr=0;
        for(int i=1;i<=q;i++){
            int jobl=nums[i].l;
            int jobr=nums[i].r;
            int jobi=nums[i].id;
            while(jobl<winl){
                add(val[--winl]);
            }
            while(jobl>winl){
                del(val[winl++]);
            }
            while(jobr>winr){
                add(val[++winr]);
            }
            while(jobr<winr){
                del(val[winr--]);
            }
            ans[jobi]=res;
        }
        for(int i=1;i<=q;i++){
            printf("%lld\n",ans[i]);
        }
    }
    return 0;
}