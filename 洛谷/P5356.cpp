#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 1e3+5;

int n,m;
int arr[MAXN];
int nums[MAXN];

int blen,bnum;
int bl[MAXM];
int br[MAXM];
int bi[MAXN];
int lazy[MAXM];

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

int getmax(int l,int r){
    int lb=bi[l],rb=bi[r],ans=INT_MIN;
    if(lb==rb){
        for(int i=l;i<=r;i++){
            ans=max(ans,arr[i]+lazy[lb]);
        }
    }
    else{
        for(int i=l;i<=br[lb];i++){
            ans=max(ans,arr[i]+lazy[lb]);
        }
        for(int i=bl[rb];i<=r;i++){
            ans=max(ans,arr[i]+lazy[rb]);
        }
        for(int i=lb+1;i<=rb;i++){
            ans=max(ans,nums[br[i]]+lazy[i]);
        }
    }
    return ans;
}

int getmin(int l,int r){
    int lb=bi[l],rb=bi[r],ans=INT_MAX;
    if(lb==rb){
        for(int i=l;i<=r;i++){
            ans=min(ans,arr[i]+lazy[lb]);
        }
    }
    else{
        for(int i=l;i<=br[lb];i++){
            ans=min(ans,arr[i]+lazy[lb]);
        }
        for(int i=bl[rb];i<=r;i++){
            ans=min(ans,arr[i]+lazy[rb]);
        }
        for(int i=lb+1;i<=rb;i++){
            ans=min(ans,nums[bl[i]]+lazy[i]);
        }
    }
    return ans;
}

int blockcnt(int i,int v){
    v-=lazy[i];
    int l=bl[i],r=br[i];
    if(nums[l]>v){
        return 0;
    }
    if(nums[r]<=v){
        return r-l+1;
    }
    int ans;
    while(l<=r){
        int mid=(l+r)>>1;
        if(nums[mid]<=v){
            ans=mid;
            l=mid+1;
        }
        else{
            r=mid-1;
        }
    }
    return ans-bl[i]+1;
}

int getcnt(int l,int r,int v){
    int ans=0;
    int lb=bi[l],rb=bi[r];
    if(lb==rb){
        for(int i=l;i<=r;i++){
            if(v>=lazy[lb]+arr[i]){
                ans++;
            }
        }
    }
    else{
        for(int i=l;i<=br[lb];i++){
            if(arr[i]+lazy[lb]<=v){
                ans++;
            }
        }
        for(int i=bl[rb];i<=r;i++){
            if(arr[i]+lazy[rb]<=v){
                ans++;
            }
        }
        for(int i=lb+1;i<=rb-1;i++){
            ans+=blockcnt(i,v);
        }
    }
    return ans;
}

int query(int l,int r,int k){
    if(k<1||k>(r-l+1)){
        return -1;
    }
    int lv=getmin(l,r);
    int rv=getmax(l,r);
    int ans;
    while(lv<=rv){
        int mid=(rv-lv)/2+lv;
        if(getcnt(l,r,mid)>=k){
            ans=mid;
            rv=mid-1;
        }
        else{
            lv=mid+1;
        }
    }
    return ans;
}

void add(int l,int r,int v){
    for(int i=l;i<=r;i++){
        arr[i]+=v;
    }
    for(int i=bl[bi[l]];i<=br[bi[r]];i++){
        nums[i]=arr[i];
    }
    sort(nums+bl[bi[l]],nums+br[bi[l]]+1);
}

void update(int l,int r,int v){
    int lb=bi[l],rb=bi[r];
    if(lb==rb){
        add(l,r,v);
    }
    else{
        add(l,br[bi[l]],v);
        add(bl[bi[r]],r,v);
        for(int i=lb+1;i<=rb-1;i++){
            lazy[i]+=v;
        }
    }
}

void prepare(){
    blen=max(1,(int)sqrt(n*2/3));
    bnum=(n+blen-1)/blen;
    for(int i=1;i<=n;i++){
        bi[i]=(i-1)/blen+1;
    }
    for(int i=1;i<=bnum;i++){
        bl[i]=(i-1)*blen+1;
        br[i]=min(n,i*blen);
    }
    for(int i=1;i<=n;i++){
        nums[i]=arr[i];
    }
    for(int i=1;i<=bnum;i++){
        sort(nums+bl[i],nums+br[i]+1);
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        arr[i]=read();
    }
    prepare();
    for(int i=1;i<=m;i++){
        int op,l,r,k;
        op=read(),l=read(),r=read(),k=read();
        if(op==1){
            printf("%d\n",query(l,r,k));
        }
        else{
            update(l,r,k);
        }
    }
    return 0;
}