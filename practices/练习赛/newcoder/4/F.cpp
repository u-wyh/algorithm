#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;
const int MAXM = 65;

int n,m;

int val[MAXN];

int len;
int sorted[MAXN];
int lt[MAXN];
int rt[MAXN];

int dp[MAXM][MAXN];
int pre[MAXN];
int cur[MAXN];

int tree[MAXN<<2];

int find(int val){
    int l=1,r=len,ans=len+1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(sorted[mid]>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

int find2(int val){
    int l=1,r=len,ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(sorted[mid]<=val){
            ans=mid;
            l=mid+1;
        }
        else{
            r=mid-1;
        }
    }
    return ans;
}

void up(int i){
    tree[i]=max(tree[i<<1],tree[i<<1|1]);
}

void update(int pos,int jobv,int l,int r,int i){
    if(l==r){
        tree[i]=max(tree[i],jobv);
    }
    else{
        int mid=(l+r)>>1;
        if(pos<=mid){
            update(pos,jobv,l,mid,i<<1);
        }
        else{
            update(pos,jobv,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

int query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return tree[i];
    }
    else{
        int mid=(l+r)>>1;
        int ans=0;
        if(jobl<=mid){
            ans=max(ans,query(jobl,jobr,l,mid,i<<1));
        }
        if(jobr>mid){
            ans=max(ans,query(jobl,jobr,mid+1,r,i<<1|1));
        }
        return ans;
    }
}

void prepare(){
    sort(sorted+1,sorted+n+1);
    len=1;
    for(int i=2;i<=n;i++){
        if(sorted[i]!=sorted[i-1]){
            sorted[++len]=sorted[i];
        }
    }

    for(int i=1;i<=n;i++){
        lt[i]=(val[i]+2)/3;
        rt[i]=val[i]/2;

        val[i]=find(val[i]);
        lt[i]=find(lt[i]);
        rt[i]=find2(rt[i]);
    }

    for(int i=1;i<=n;i++){
        pre[i]=i;
        dp[1][i]=i;
    }
    for(int l=2;l<MAXM;l++){
        for(int i=1;i<=(len<<2);i++){
            tree[i]=0;
        }

        bool flag=false;

        for(int i=1;i<=n;i++){
            cur[i]=0;
            if(lt[i]<=rt[i]&&lt[i]>=1&&rt[i]<=len)
                cur[i]=query(lt[i],rt[i],1,len,1);

            if(cur[i]){
                flag=true;
            }

            update(val[i],pre[i],1,len,1);
        }

        for(int i=1;i<=n;i++){
            dp[l][i]=max(dp[l][i-1],cur[i]);
        }

        if(!flag){
            break;
        }
        swap(pre,cur);
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>val[i];
        sorted[i]=val[i];
    }

    prepare();

    for(int i=1;i<=m;i++){
        int l,r;
        cin>>l>>r;
        int ans=min(MAXM-1,r-l+1);
        for(int j=ans;j>=1;j--){
            if(dp[j][r]>=l){
                ans=j;
                break;
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}