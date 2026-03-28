#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXT = MAXN*50;

int n,len;
int val[MAXN];
int sorted[MAXN];

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cntg=1;

int root[MAXN];
int ls[MAXT];
int rs[MAXT];
int maxv[MAXT];
int tag[MAXT];
int cnt;

void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

int find(int val){
    int l=1,r=len,ans=1;
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

void prepare(){
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
        val[i]=find(val[i]);
    }
}

void lazy(int i,int v){
    if(i){
        maxv[i]+=v;
        tag[i]+=v;
    }
}

void down(int i){
    if(tag[i]){
        lazy(ls[i],tag[i]);
        lazy(rs[i],tag[i]);
        tag[i]=0;
    }
}

int query(int jobl,int jobr,int l,int r,int i){
    if(i==0){
        return 0;
    }
    if(jobl<=l&&r<=jobr){
        return maxv[i];
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        int ans=0;
        if(jobl<=mid){
            ans=max(ans,query(jobl,jobr,l,mid,ls[i]));
        }
        if(jobr>mid){
            ans=max(ans,query(jobl,jobr,mid+1,r,rs[i]));
        }
        return ans;
    }
}

void up(int i){
    maxv[i]=max(maxv[ls[i]],maxv[rs[i]]);
}

int merge(int l,int r,int u,int v,int maxv1,int maxv2){
    if(u==0||v==0){
        lazy(u,maxv2);
        lazy(v,maxv1);
        return u+v;
    }
    if(l==r){
        maxv[u]+=max(maxv[v],maxv2);
    }
    else{
        down(u);
        down(v);
        int mid=(l+r)>>1;
        ls[u]=merge(l,mid,ls[u],ls[v],max(maxv1,maxv[rs[u]]),max(maxv2,maxv[rs[v]]));
        rs[u]=merge(mid+1,r,rs[u],rs[v],maxv1,maxv2);
        up(u);
    }
    return u;
}

int update(int jobi,int jobv,int l,int r,int i){
    int rt = i;
	if (rt == 0) {
		rt = ++cnt;
	}
	if (l == r) {
		maxv[rt] = max(maxv[rt], jobv);
	} else {
		down(rt);
		int mid = (l + r) >> 1;
		if (jobi <= mid) {
			ls[rt] = update(jobi, jobv, l, mid, ls[rt]);
		} else {
			rs[rt] = update(jobi, jobv, mid + 1, r, rs[rt]);
		}
		up(rt);
	}
	return rt;
}

void dfs(int u){
    int sum=0;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs(v);
        sum+=query(val[u],len,1,len,root[v]);
        root[u]=merge(1,len,root[u],root[v],0,0);
    }
    root[u]=update(val[u],sum+1,1,len,root[u]);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>val[i];
    }
    for(int i=2;i<=n;i++){
        int fa;
        cin>>fa;
        addedge(fa,i);
    }

    prepare();
    dfs(1);
    cout<<query(1,len,1,len,root[1])<<endl;
    return 0;
}