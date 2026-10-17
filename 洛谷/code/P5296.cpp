// https://www.luogu.com.cn/problem/P5926
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int INF = 1e9;

int n,m;
int val[MAXN];
int len;
int sorted[MAXN];
int tree[MAXN<<2];
int f[MAXN];

int ans[MAXN];

int head[MAXN];
int nxt[MAXN];
int idg[MAXN];
int to[MAXN];
int cntg=1;

inline void addedge(int u,int id,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    idg[cntg]=id;
    head[u]=cntg++;
}

inline int lowbit(int x){
    return x&-x;
}

int query(int x){
    int ans=INF;
    while(x<=n){
        ans=min(ans,f[x]);
        x+=lowbit(x);
    }
    return ans;
}

void update(int x,int v){
    while(x){
        f[x]=min(f[x],v);
        x-=lowbit(x);
    }
}

void up(int x){
    tree[x]=max(tree[x<<1],tree[x<<1|1]);
}

void update(int pos,int jobv,int l,int r,int i){
    if(l==r){
        tree[i]=jobv;
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
    if(jobr<jobl){
        return 0;
    }
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

int find1(int x){
    int l=1,r=len,ans=len+1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(sorted[mid]>=x){
            ans=mid;
            r=mid-1; 
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

int find2(int x){
    int l=1,r=len,ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(sorted[mid]<=x){
            ans=mid;
            l=mid+1;
        }
        else{
            r=mid-1;
        }
    }
    return ans;
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>val[i];
    }
    for(int i=1;i<=m;i++){
        int l,r;
        cin>>l>>r;
        addedge(r,i,l);
    }

    for(int i=1;i<=n;i++){
        f[i]=INF;
    }
    for(int i=1;i<=n;i++){
        sorted[i]=val[i];
    }
    sort(sorted+1,sorted+n+1);
    len=1;
    for(int i=2;i<=n;i++){
        if(sorted[i]!=sorted[i-1]){
            sorted[++len]=sorted[i];
        }
    }
    for(int i=1;i<=n;i++){
        val[i]=find1(val[i]);
    }

    for(int r=1;r<=n;r++){
        update(val[r],r,1,len,1);

        int rtval=INF;
        int l=r-1;
        while(l>0){
            int rt=find2(rtval);
            l=query(val[r]+1,rt,1,len,1);
            if(l==0){
                break ;
            }
            update(l,abs(sorted[val[r]]-sorted[val[l]]));
            rtval=(rtval+sorted[val[r]]-1)/2;
            l--;
        }

        l=r-1;
        rtval=0;
        while(l>0){
            int rt=find1(rtval);
            l=query(rt,val[r]-1,1,len,1);
            if(l==0){
                break ;
            }
            update(l,abs(sorted[val[r]]-sorted[val[l]]));
            rtval=(sorted[val[r]]+rtval)/2+1;
            l--;
        }

        for(int i=head[r];i;i=nxt[i]){
            int id=idg[i];
            int l=to[i];
            ans[id]=query(l);
        }
    }

    for(int i=1;i<=m;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}