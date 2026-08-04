#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXG = 45;
const int MAXB = 1e4+5;

int n,m;

struct node{
    int l,r,len;
    long long val;
};
node nums[MAXN<<2];
int cntn;

int cntg;
int glen[MAXG];
// 表示这个组管理的树上节点的左右边界
int gl[MAXG];
int gr[MAXG];
// 表示这个组管理的块的左右边界
int gL[MAXG];
int gR[MAXG];

int cntb;
// 表示这个块实际管理的树上节点的范围
int bl[MAXB];
int br[MAXB];
// 表示这个块实际管理的树上节点的覆盖点的范围
int bL[MAXB];
int bR[MAXB];
long long tag[MAXB];

void build(int l,int r){
    nums[++cntn]={l,r,r-l+1};
    if(l!=r){
        int mid=(l+r)>>1;
        build(l,mid);
        build(mid+1,r);
    }
}

bool cmp(node &a,node &b){
    if(a.len!=b.len){
        return a.len>b.len;
    }
    return a.l<b.l;
}

void prepare(){
    cntn=0;
    build(1,n);

    sort(nums+1,nums+cntn+1,cmp);

    for(int l=1,r=1;l<=cntn;l=r+1){
        while(r+1<=cntn&&nums[r+1].len==nums[l].len){
            r++;
        }

        ++cntg;
        glen[cntg]=nums[l].len;
        gl[cntg]=l;
        gr[cntg]=r;
        gL[cntg]=cntb+1;

        int bsz=max(1,(int)(sqrt(r-l+1)*0.55));
        for(int i=l;i<=r;i+=bsz){
            ++cntb;
            bl[cntb]=i;
            br[cntb]=min(i+bsz-1,r);
            bL[cntb]=nums[i].l;
            bR[cntb]=nums[br[cntb]].r;
        }

        gR[cntg]=cntb;
    }
}

// 找到g这个组中的第一个右边界不小于x的组的编号
int firstblock(int g,int x){
    int l=gL[g],r=gR[g],ans=r+1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(bR[mid]>=x){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

bool cmpval(node &a,node &b){
    return a.val<b.val;
}

void rebuild(int b){
    sort(nums+bl[b],nums+br[b]+1,cmpval);
}

void partadd(int b,int l,int r,int x){
    for(int i=bl[b];i<=br[b];i++){
        int lt=max(nums[i].l,l);
        int rt=min(nums[i].r,r);
        if(lt<=rt){
            nums[i].val+=1ll*(rt-lt+1)*x;
        }
    }
    rebuild(b);
}

void add(int g,int l,int r,int x){
    int b=firstblock(g,l);
    if(b>gR[g]||bL[b]>r){
        // 如果说这个组中根本没有包含l  直接退出
        return ;
    }

    // 处理左边散块
    if(bL[b]<l){
        partadd(b,l,min(r,bR[b]),x);
        b++;
    }
    // 处理中间块
    while(b<=gR[g]&&r>=bR[b]){
        tag[b]+=1ll*x*glen[g];
        b++;
    }
    // 处理右边散块
    if(b<=gR[g]&&bL[b]<=r){
        partadd(b,max(l,bL[b]),r,x);
    }
}

int partquery(int b,int l,int r,int x){
    int ans=0;
    for(int i=bl[b];i<=br[b];i++){
        if(l<=nums[i].l&&nums[i].r<=r&&nums[i].val+tag[b]<=x){
            ans++;
        }
    }
    return ans;
}

int fullquery(int b,long long x){
    x-=tag[b];
    int l=bl[b],r=br[b];
    int ans=bl[b]-1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(nums[mid].val<=x){
            ans=mid;
            l=mid+1;
        }
        else{
            r=mid-1;
        }
    }
    return ans-bl[b]+1;
}

int query(int g,int l,int r,int x){
    int b=firstblock(g,l);
    if(b>gR[g]||bL[b]>r){
        // 如果说这个组中根本没有包含l  直接退出
        return 0;
    }

    int ans=0;
    // 处理左边散块
    if(bL[b]<l){
        ans+=partquery(b,l,min(r,bR[b]),x);
        b++;
    }
    // 处理中间块
    while(b<=gR[g]&&r>=bR[b]){
        ans+=fullquery(b,x);
        b++;
    }
    // 处理右边散块
    if(b<=gR[g]&&bL[b]<=r){
        ans+=partquery(b,max(l,bL[b]),r,x);
    }
    return ans;
}

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

void write(int x)
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
    prepare();

    for(int i=1;i<=m;i++){
        int op,l,r,a;
        op=read(),l=read(),r=read(),a=read();
        if(op==1){
            for(int g=1;g<=cntg;g++){
                add(g,l,r,a);
            }
        }
        else{
            int ans=0;
            for(int g=1;g<=cntg;g++){
                ans+=query(g,l,r,a);
            }
            write(ans);
            putchar('\n');
        }
    }
    return 0;
}