// https://www.luogu.com.cn/problem/P4876
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,k;

struct node{
    int x,y,v;
};
node nums[MAXN];

int sorted[MAXN];
int len;

int tree[MAXN<<2];
int tag[MAXN<<2];

bool cmp(node &a,node &b){
    return a.x<b.x;
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

void lazy(int i,int v){
    tree[i]+=v;
    tag[i]+=v;
}

void down(int i){
    if(tag[i]){
        lazy(i<<1,tag[i]);
        lazy(i<<1|1,tag[i]);
        tag[i]=0;
    }
}

void update(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        lazy(i,jobv);
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        if(jobl<=mid){
            update(jobl,jobr,jobv,l,mid,i<<1);
        }
        if(jobr>mid){
            update(jobl,jobr,jobv,mid+1,r,i<<1|1);
        }
        tree[i]=max(tree[i<<1],tree[i<<1|1]);
    }
}

void add(int id,int v){
    int y=nums[id].y;
    int l=find1(sorted[y]-2*k);
    int r=y;
    update(l,r,v,1,len,1);
}

int main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        int v,a,b;
        cin>>v>>a>>b;
        nums[i]={a+b,a-b,v};
        sorted[i]=a-b;
    }

    sort(sorted+1,sorted+n+1);
    len=1;
    for(int i=2;i<=n;i++){
        if(sorted[i]!=sorted[i-1]){
            sorted[++len]=sorted[i];
        }
    }

    for(int i=1;i<=n;i++){
        nums[i].y=find1(nums[i].y);
    }
    sort(nums+1,nums+n+1,cmp);
    int l=1;
    int ans=0;
    for(int r=1;r<=n;r++){
        add(r,nums[r].v);
        while(nums[r].x-nums[l].x>2*k){
            add(l,-nums[l].v);
            l++;
        }
        ans=max(ans,tree[1]);
    }
    cout<<ans<<endl;
    return 0;
}