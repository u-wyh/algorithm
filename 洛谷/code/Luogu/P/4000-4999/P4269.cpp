#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

struct snow{
    int dep,pos;
}nums[MAXN];
struct shoe{
    int dep,wid,sub;
}arr[MAXN];
int n,m;
int cnt=0,tot=0;
struct node{
    int len,llen,rlen,all;
}tree[MAXN<<2];
int ans[MAXN];

bool cmp1(shoe a,shoe b){
    return a.dep<b.dep;
}

bool cmp2(snow a,snow b){
    return a.dep<b.dep;
}

void up(int i){
    tree[i].len=max(max(tree[i<<1].len,tree[i<<1|1].len),tree[i<<1].rlen+tree[i<<1|1].llen);
    tree[i].llen=(tree[i<<1].llen==tree[i<<1].all)?(tree[i<<1].llen+tree[i<<1|1].llen):tree[i<<1].llen;
    tree[i].rlen=(tree[i<<1|1].rlen==tree[i<<1|1].all)?(tree[i<<1|1].rlen+tree[i<<1].rlen):tree[i<<1|1].rlen;
}

void build(int l,int r,int i){
    tree[i].all=r-l+1;
    if(l==r){
        tree[i].len=tree[i].llen=tree[i].rlen=1;
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

void add(int pos,int val,int l,int r,int i){
    if(l==r){
        tree[i].len=tree[i].llen=tree[i].rlen=0;
    }
    else{
        int mid=(l+r)/2;
        if(pos<=mid){
            add(pos,val,l,mid,i<<1);
        }
        else{
            add(pos,val,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>nums[i].dep;
        nums[i].pos=i;
    }
    for(int i=1;i<=m;i++){
        cin>>arr[i].dep>>arr[i].wid;
        arr[i].sub=i;
    }
    sort(nums+1,nums+n+1,cmp2);
    sort(arr+1,arr+m+1,cmp1);
//    cout<<endl;
//    for(int i=1;i<=n;i++){
//        cout<<nums[i].dep<<' '<<nums[i].pos<<endl;
//    }
//    for(int i=1;i<=m;i++){
//        cout<<arr[i].dep<<' '<<arr[i].wid<<' '<<arr[i].sub<<endl;
//    }
    build(1,n,1);
    int l=1;
    for(int i=1;i<=m;i++){
        while(nums[l].dep<=arr[i].dep&&l<=n){
            add(nums[l].pos,-1,1,n,1);
            l++;
        }
        //cout<<tree[1].len<<endl;
        if(tree[1].len>=arr[i].wid){
            ans[arr[i].sub]=0;
        }
        else{
            ans[arr[i].sub]=1;
        }
    }
    for(int i=1;i<=m;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}
