#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 3e5+5;
const int MAXT = MAXN*40;

int n,m,q,limit;

int root[MAXN];
int colroot;

int sz[MAXT];
int ls[MAXT];
int rs[MAXT];
int cntt;

vector<int>vec[MAXN];
vector<int>colvec;

int insert(int pos,int l,int r,int i){
    int rt=++cntt;
    ls[rt]=ls[i];
    rs[rt]=rs[i];
    sz[rt]=sz[i]+1;
    if(l<r){
        int mid=(l+r)>>1;
        if(pos<=mid){
            ls[rt]=insert(pos,l,mid,ls[rt]);
        }
        else{
            rs[rt]=insert(pos,mid+1,r,rs[rt]);
        }
    }
    return rt;
}

int query(int k,int l,int r,int i){
    if(l==r){
        return l;
    }
    else{
        int mid=(l+r)>>1;
        int ltlen=mid-l+1;
        if(ltlen-sz[ls[i]]>=k){
            return query(k,l,mid,ls[i]);
        }
        else{
            return query(k+sz[ls[i]]-ltlen,mid+1,r,rs[i]);
        }
    }
}

int removerow(int x,int y){
    int pos=query(y,1,limit,root[x]);
    int val;
    if(pos<m){
        val=(x-1)*m+pos;
    }
    else{
        val=vec[x][pos-m];
    }
    root[x]=insert(pos,1,limit,root[x]);
    return val;
}

int removecol(int x){
    int pos=query(x,1,limit,colroot);
    colroot=insert(pos,1,limit,colroot);
    if(pos<=n){
        return pos*m;
    }
    else{
        return colvec[pos-n-1];
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m>>q;
    limit=max(n,m)+q;
    for(int i=1;i<=q;i++){
        int x,y;
        cin>>x>>y;
        if(y<m){
            int ans=removerow(x,y);
            int tmp=removecol(x);
            vec[x].push_back(tmp);
            colvec.push_back(ans);
            cout<<ans<<endl;
        }
        else{
            int ans=removecol(x);
            colvec.push_back(ans);
            cout<<ans<<endl;
        }
    }

    return 0;
}