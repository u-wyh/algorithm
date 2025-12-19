#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int n;
int arr[MAXN];
int tree[MAXN<<2];
int lazy[MAXN<<2];
int nums[MAXN];

void up(int i){
    tree[i]=min(tree[i<<1],tree[i<<1|1]);
}

void build(int l,int r,int i){
    lazy[i]=0;
    if(l==r){
        tree[i]=l;
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

void downlazy(int i,int v){
    tree[i]+=v;
    lazy[i]+=v;
}

void down(int i){
    if(lazy[i]){
        downlazy(i<<1,lazy[i]);
        downlazy(i<<1|1,lazy[i]);
        lazy[i]=0;
    }
}

void add(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        downlazy(i,jobv);
    }
    else{
        int mid=(l+r)/2;
        down(i);
        if(jobl<=mid){
            add(jobl,jobr,jobv,l,mid,i<<1);
        }
        if(jobr>mid){
            add(jobl,jobr,jobv,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    build(1,n,1);
    for(int i=n;i>=1;i--){
        add(arr[i],n,-2,1,n,1);
        if(tree[1]<0){
            nums[arr[i]]=1;
            add(arr[i],n,2,1,n,1);
        }
        else{
            nums[arr[i]]=-1;
        }
    }
    int sum=0;
    for(int i=1;i<=n;i++){
        sum+=nums[arr[i]];
        if(sum<0){
            cout<<"NIE"<<endl;
            return 0;
        }
    }
    for(int i=1;i<=n;i++){
        if(nums[i]==1){
            cout<<'(';
        }
        else{
            cout<<')';
        }
    }
    return 0;
}
