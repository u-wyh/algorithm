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

int lst[MAXN + 1];
int nxt[MAXN + 1];
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
    return a.r > b.r;
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
    }
    sort(nums+1,nums+m+1,cmp);
}

inline void del(int num) {
    int less = lst[num], more = nxt[num];
    if (less != 0) {
        sum -= abs(pos[num] - pos[less]);
    }
    if (more != n + 1) {
        sum -= abs(pos[more] - pos[num]);
    }
    if (less != 0 && more != n + 1) {
        sum += abs(pos[more] - pos[less]);
    }
    nxt[less] = more;
    lst[more] = less;
}

// 加数字的顺序，就是删数字顺序的回滚，才能这么方便的更新
// 在加操作的时候  完全也可以用于收集答案  但是compute不用回滚
// 其实不使用backup也是可以的
inline void add(int num) {
    nxt[lst[num]] = num;
    lst[nxt[num]] = num;
}

void compute(){
    for(int i=1;i<=n;i++){
        lst[i]=i-1;
        nxt[i]=i+1;
    }
    nxt[0]=1,lst[n+1]=n;
    for(int v=2;v<=n;v++){
        sum+=abs(pos[v]-pos[v-1]);
    }
    int winl=1,winr=n;
    for (int block = 1, qi = 1; block <= bnum && qi <= m; block++) {
        while (winl < bl[block]) {
            del(val[winl++]);
        }
        long long beforeJob = sum;
        for (; qi <= m && bi[nums[qi].l] == block; qi++) {
            int jobl = nums[qi].l;
            int jobr = nums[qi].r;
            int id = nums[qi].id;
            while (winr > jobr) {
                del(val[winr--]);
            }
            long long backup = sum;
            while (winl < jobl) {
                del(val[winl++]);
            }
            ans[id] = sum;
            sum = backup;
            while (winl > bl[block]) {
                add(val[--winl]);
            }
        }
        while (winr < n) {
            add(val[++winr]);
        }
        sum = beforeJob;
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