#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXB = 505;

int n,m;
int val[MAXN];

struct node{
    int l,r,id;
};
node nums[MAXN];
int ans[MAXN];

int blen,bnum;
int bi[MAXN];
int bl[MAXB];
int br[MAXB];

int mex;
int cnt[MAXN];

bool cmp(node &a,node &b){
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

void add(int val){
    cnt[val]++; 
}

void del(int val){
    cnt[val]--;
    if(val<mex&&cnt[val]==0){
        mex=val;
    }
}

void compute(){
    int winl=1,winr=n;
    for(int i=1;i<=n;i++){
        cnt[val[i]]++;
    }
    for(int i=0;i<=n;i++){
        if(cnt[i]==0){
            mex=i;
            break;
        }
    }

    for(int block=1,qi=1;block<=bnum&&qi<=m;block++){
        while(winl<bl[block]){
            del(val[winl++]);
        }
        int beforejob=mex;

        for(;qi<=m&&bi[nums[qi].l]==block;qi++){
            int l=nums[qi].l;
            int r=nums[qi].r;
            int id=nums[qi].id;

            while(winr>r){
                del(val[winr--]);
            }
            int backup=mex;
            while(winl<l){
                del(val[winl++]);
            }
            ans[id]=mex;
            while(winl>bl[block]){
                add(val[--winl]);
            }
            mex=backup;
        }
        while(winr<n){
            add(val[++winr]);
        }
        mex=beforejob;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>val[i];
    }
    for(int i=1;i<=m;i++){
        nums[i].id=i;
        cin>>nums[i].l>>nums[i].r;
    }

    prepare();
    compute();
    
    for(int i=1;i<=m;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}