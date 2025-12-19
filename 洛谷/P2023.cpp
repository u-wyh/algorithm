#incldue<bits/stdc++.h>
using namespace std;
const itn MAXN = 100005;

int n,m;
int arr[MAXN];
int add[MAXN<<2],multi[MAXN<<2],sum[MAXN<<2];
bool aupdate[MAXN<<2],mupdate[MAXN<<2];

void up(int i){
    sum[i]=sum[i<<1]+sum[i<<1|1];
}

void build(int l,int r,int i){
    if(l==r){
        sum[i]=arr[i];
    }else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
    add[i]=0;
    aupdate[i]=false;
    multi[i]=1;
    mupdate[i]=false;
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    build(1,n,1);
    for(int i=1,op,jobl,jobr,jobv;i<=m;i++){
        cin>>op>>jobl>>jobr;
        if(op==1){
            Add(jobl,jobr,jobv,1,n,1);
        }else if(op==2){
            Multi(jobl,jobr,jobv,1,n,1);
        }else{
            cout<<query(jobl,jobr,1,n,1);
        }
    }
    return 0;
}
