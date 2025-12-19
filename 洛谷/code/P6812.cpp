#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;

int arr[MAXN],Min[MAXN<<2],diff[MAXN];
int n,m;


void up(int i){
    Min[i]=min(Min[i<<1],Min[i<<1|1]);
}

void build(int l,int r,int i){
    if(l==r){
        Min[i]=diff[l];
    }else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

void update(int jobl,int jobv,int l,int r,int i){
    if(l==r){
        Min[i]+=jobv;
    }else{
        int mid=(l+r)/2;
        if(jobl<=mid){
            update(jobl,jobv,l,mid,i<<1);
        }else{
            update(jobl,jobv,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

int query(int jobl,int jobr,int l,int r,int i){
    if (jobl <= l && r <= jobr) {
        return Min[i];
    }
    int mid = (l + r) >> 1;
    int ans = 1;
    if (jobl <= mid) {
        ans =min(ans, query(jobl, jobr, l, mid, i << 1));
    }
    if (jobr > mid) {
        ans =min(ans, query(jobl, jobr, mid + 1, r, i << 1 | 1));
    }
    return ans;
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        diff[i]=arr[i]-arr[i-1];
    }
    build(1,n,1);
    for(int i=1,op,l,r,v;i<=m;i++){
        cin>>op>>l>>r;
        if(op==1){
            cin>>v;
            update(l,v,1,n,1);
            update(r+1,-v,1,n,1);
        }else{
            if(query(l,r,1,n,1)>0)
                cout<<"Yes\n";
            else
                cout<<"No\n";
        }
    }
    return 0;
}
