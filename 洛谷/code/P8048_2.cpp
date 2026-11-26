// https://www.luogu.com.cn/problem/P8048
// 题意：长为 L 的棍子上有 n 只变色龙，第 i 只初始位置 d_i（距左端距离，严格递增）、颜色 b_i ∈ [0, k)、朝向 L（左）或 D（右）
// 以 1 单位/秒匀速移动直到离开棍子两端 [0, L]。
// 两只变色龙碰撞时各自掉头 180 度：原向左者（色 a）颜色变为原向右者颜色 b，原向右者（色 b）颜色变为 (a + b) mod k。
// 对每种颜色 0..k-1，求所有变色龙采用该颜色期间的总行程。
// 第一行输入 n, k, L，接下来 n 行每行 d_i, b_i 及字符 L/D。
// 输出 k 行，第 i 行输出颜色 i-1 的总行程，保留 1 位小数。
// 数据范围：1 <= n <= 10^5，1 <= k <= 40，1 <= L <= 10^6，0 <= d_i <= L，0 <= b_i < k
// d_{i-1} < d_i。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;
const int MAXB = 805;

int n,m;
int val[MAXN];
int pos[MAXN];

struct node{
    int l,r,id;
};
node nums[MAXN];

int blen,bnum;
int bi[MAXN];
int bl[MAXB];
int br[MAXB];

int pre[MAXN];
int suf[MAXN];
long long sum;
long long ans[MAXN];

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

void prepare(){
    for(int i=1;i<=n;i++){
        pos[val[i]]=i;
    }
    blen=sqrt(n);
    bnum=(n+blen-1)/blen;
    for(int i=1;i<=n;i++){
        bi[i]=(i-1)/blen+1;
    }
    for(int i=1;i<=bnum;i++){
        bl[i]=(i-1)*blen+1;
        br[i]=min(n,i*blen);
    }
    sort(nums+1,nums+m+1,cmp);
}

inline void del(int val){
    int less=pre[val],more=suf[val];
    if(less!=0){
        sum -= abs(pos[val] - pos[less]);
    }
    if(more!=n+1){
        sum -= abs(pos[more] - pos[val]);
    }
    if(less!=0&&more!=n+1){
        sum += abs(pos[more] - pos[less]);
    }
    suf[less]=more;
    pre[more]=less;
}

inline void add(int val){
    int less=pre[val],more=suf[val];
    if(less!=0){
        sum+=abs(pos[val]-pos[less]);
    }
    if(more!=n+1){
        sum+=abs(pos[val]-pos[more]);
    }
    if(less!=0&&more!=n+1){
        sum-=abs(pos[less]-pos[more]);
    }
    suf[less]=val;
    pre[more]=val;
}

void compute(){
    for(int i=1;i<=n;i++){
        pre[i]=i-1;
        suf[i]=i+1;
    }
    suf[0]=1,pre[n+1]=n;
    for(int v=2;v<=n;v++){
        sum+=abs(pos[v]-pos[v-1]);
    }
    int winl=1,winr=n;
    for(int i=1;i<=m;i++){
        int jobl=nums[i].l;
        int jobr=nums[i].r;
        while(winl>jobl){
            add(val[--winl]);
        }
        while(winr<jobr){
            add(val[++winr]);
        }
        while(winl<jobl){
            del(val[winl++]);
        }
        while(winr>jobr){
            del(val[winr--]);
        }
        ans[nums[i].id]=sum;
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    for(int i=1;i<=m;i++){
        nums[i].l=read(),nums[i].r=read();
        nums[i].id=i;
    }
    prepare();
    compute();
    for(int i=1;i<=m;i++){
        printf("%lld\n",ans[i]);
    }
    return 0;
}