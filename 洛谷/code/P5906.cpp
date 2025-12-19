#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXB = 505;

int n,q,m;
int val[MAXN];
int arr[MAXN];

struct node{
    int l,r,id;
};
node nums[MAXN];

int blen,bnum;
int bi[MAXN];
int br[MAXB];

int first[MAXN];
int mostright[MAXN];
int maxdis;

int ans[MAXN];

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

bool cmp(node &a,node &b){
    if(bi[a.l]!=bi[b.l]){
        return bi[a.l]<bi[b.l];
    }
    return a.r<b.r;
}

void prepare(){
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
    blen=sqrt(n);
    bnum=(n+blen-1)/blen;
    for(int i=1;i<=n;i++){
        bi[i]=(i-1)/blen+1;
    }
    for(int i=1;i<=bnum;i++){
        br[i]=min(n,i*blen);
    }
    sort(nums+1,nums+q+1,cmp);
}

int force(int l,int r){
    int res=0;
    for(int i=l;i<=r;i++){
        if(first[val[i]]==0){
            first[val[i]]=i;
        }
        else{
            res=max(res,i-first[val[i]]);
        }
    }
    for(int i=l;i<=r;i++){
        first[val[i]]=0;
    }
    return res;
}

void addright(int pos){
    int v=val[pos];
    mostright[v]=pos;
    if(first[v]==0){
        first[v]=pos;
    }
    maxdis=max(maxdis,pos-first[v]);
}

void addleft(int pos){
    int v=val[pos];
    if(mostright[v]==0){
        mostright[v]=pos;
    }
    else{
        maxdis=max(maxdis,mostright[v]-pos);
    }
}

void delleft(int pos){
    int v=val[pos];
    if(mostright[v]==pos){
        mostright[v]=0;
    }
}

void compute(){
    for(int b=1,qi=1;qi<=q&&b<=bnum;b++){
        maxdis=0;
        for(int i=1;i<=m;i++){
            first[i]=0;
            mostright[i]=0;
        }
        int winl=br[b]+1,winr=br[b];
        for(;qi<=q&&bi[nums[qi].l]==b;qi++){
            int jobl=nums[qi].l;
            int jobr=nums[qi].r;
            int jobi=nums[qi].id;
            if(jobr<=br[b]){
                ans[jobi]=force(jobl,jobr);
            }
            else{
                while(winr<jobr){
                    addright(++winr);
                }
                int backup=maxdis;
                while(winl>jobl){
                    addleft(--winl);
                }
                ans[jobi]=maxdis;
                maxdis=backup;
                while(winl<=br[b]){
                    delleft(winl++);
                }
            }
        }
    }
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    q=read();
    for(int i=1;i<=q;i++){
        nums[i].l=read(),nums[i].r=read();
        nums[i].id=i;
    }
    prepare();
    compute();
    for(int i=1;i<=q;i++){
        printf("%d\n",ans[i]);
    }
    return 0;
}