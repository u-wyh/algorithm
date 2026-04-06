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

long long ans[MAXN];

long long sum;
int nxt[MAXN];
int lst[MAXN];

int blen,bnum;
int bi[MAXN];
int bl[MAXB];
int br[MAXB];

bool cmp(node a,node b){
    if(bi[a.l]!=bi[b.l]){
        return bi[a.l]<bi[b.l];
    }
    return a.r>b.r;
}

void prepare(){
    blen=sqrt(n);
    bnum=(n+blen-1)/blen;
    for(int i=1;i<=n;i++){
        bi[i]=(i+blen-1)/blen;
    }
    for(int i=1;i<=bnum;i++){
        bl[i]=(i-1)*blen+1;
        br[i]=min(n,i*blen);
    }

    sort(nums+1,nums+m+1,cmp);
}

void del(int val){
    int pre=lst[val];
    int suf=nxt[val];
    if(pre!=0){
        sum-=abs(pos[val]-pos[pre]);
    }
    if(suf!=n+1){
        sum-=abs(pos[val]-pos[suf]);
    }
    if(pre!=0&&suf!=n+1){
        sum+=abs(pos[pre]-pos[suf]);
    }
    nxt[pre]=suf;
    lst[suf]=pre;
}

void add(int val){
    nxt[lst[val]]=val;
    lst[nxt[val]]=val;
}

void compute(){
    for(int i=1;i<=n;i++){
        nxt[i]=i+1;
        lst[i]=i-1;
    }
    nxt[0]=1;
    lst[n+1]=n;

    int winl=1,winr=n;
    for(int i=2;i<=n;i++){
        sum+=abs(pos[i]-pos[i-1]);
    }

    for(int block=1,qi=1;block<=bnum&&qi<=m;block++){
        while(winl<bl[block]){
            del(val[winl++]);
        }
        long long beforejob=sum;
        for(;qi<=m&&bi[nums[qi].l]==block;qi++){
            int l=nums[qi].l;
            int r=nums[qi].r;
            int id=nums[qi].id;

            while(winr>r){
                del(val[winr--]);
            }
            long long backup=sum;
            while(winl<l){
                del(val[winl++]);
            }
            ans[id]=sum;
            while(winl>bl[block]){
                add(val[--winl]);
            }
            sum=backup;
        }
        while(winr<n){
            add(val[++winr]);
        }
        sum=beforejob;
    }
}

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

inline void write(long long x)
{
    if(x<0)
        putchar('-'),x=-x;
    if(x>9)
        write(x/10);
    putchar(x%10+'0');
    return;
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
        pos[val[i]]=i;
    }
    for(int i=1;i<=m;i++){
        nums[i].l=read(),nums[i].r=read();
        nums[i].id=i;
    }

    prepare();
    compute();

    for(int i=1;i<=m;i++){
        write(ans[i]);
        putchar('\n');
    }
    return 0;
}