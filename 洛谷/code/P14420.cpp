#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int MAXB = 405;

int n,m;
int val[MAXN];
int len;
int sortv[MAXN];

struct node{
    int l,r,id;
};
node nums[MAXN];
int ans[MAXN];

int maxval;
int cnt[MAXN];

int blen,bnum;
int bi[MAXN];
int bl[MAXB];
int br[MAXB];

bool cmp(node &a,node &b){
    if(bi[a.l]!=bi[b.l]){
        return bi[a.l]<bi[b.l];
    }
    return a.r<b.r;
}

int find(int val){
    int l=1,r=len,ans=1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(sortv[mid]>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
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

    for(int i=1;i<=n;i++){
        sortv[i]=val[i];
    }
    sort(sortv+1,sortv+n+1);
    len=1;
    for(int i=2;i<=n;i++){
        if(sortv[i]!=sortv[i-1]){
            sortv[++len]=sortv[i];
        }
    }

    for(int i=1;i<=n;i++){
        val[i]=find(val[i]);
    }

    sort(nums+1,nums+m+1,cmp);
}

int force(int l,int r){
    int ans=0;
    for(int i=l;i<=r;i++){
        cnt[val[i]]++;
        ans=max(ans,cnt[val[i]]*sortv[val[i]]);
    }
    for(int i=l;i<=r;i++){
        cnt[val[i]]--;
    }
    return ans;
}

void add(int val){
    cnt[val]++;
    maxval=max(maxval,cnt[val]*sortv[val]);
}

void del(int val){
    cnt[val]--;
}

void compute(){
    for(int qi=1,block=1;block<=bnum&&qi<=m;block++){
        maxval=0;
        for(int i=1;i<=len;i++){
            cnt[i]=0;
        }

        int winl=br[block]+1,winr=br[block];
        for(;qi<=m&&bi[nums[qi].l]==block;qi++){
            int l=nums[qi].l;
            int r=nums[qi].r;
            int id=nums[qi].id;

            if(r<=br[block]){
                ans[id]=force(l,r);
            }
            else{
                while(winr<r){
                    add(val[++winr]);
                }
                int backup=maxval;
                while(winl>l){
                    add(val[--winl]);
                }
                ans[id]=maxval;
                maxval=backup;
                while(winl<=br[block]){
                    del(val[winl++]);
                }
            }
        }
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>val[i];
    }
    for(int i=1;i<=m;i++){
        cin>>nums[i].l>>nums[i].r;
        nums[i].id=i;
    }

    prepare();
    compute();

    for(int i=1;i<=m;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}