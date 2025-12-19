#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n;
int nums[MAXN][2];
int tmp[MAXN<<1];
int m;

int val[MAXN<<1];
int arr[MAXN<<1];
int help[MAXN<<1];
int tree[MAXN<<3];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

inline int find(int val){
    int l=1,r=m,ans=m;
    while(l<=r){
        int mid=(l+r)/2;
        if(tmp[mid]>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

void build(int l,int r,int i){
    if(l==r){
        tree[i]=help[l];
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        tree[i]=tree[i<<1]+tree[i<<1|1];
    }
}

int query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return tree[i];
    }
    else{
        int ans=0;
        int mid=(l+r)/2;
        if(jobl<=mid){
            ans+=query(jobl,jobr,l,mid,i<<1);
        }
        if(jobr>mid){
            ans+=query(jobl,jobr,mid+1,r,i<<1|1);
        }
        return ans;
    }
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        nums[i][0]=read(),nums[i][1]=read();
        tmp[i*2-1]=nums[i][0],tmp[i*2]=nums[i][1];
    }
    sort(tmp+1,tmp+2*n+1);
    tmp[0]=tmp[1]-1;
    for(int i=1;i<=2*n;i++){
        if(tmp[i]!=tmp[i-1]){
            tmp[++m]=tmp[i];
        }
    }
    for(int i=1;i<m;i++){
        val[i]=tmp[i+1]-tmp[i];
    }
    for(int i=1;i<=n;i++){
        nums[i][0]=find(nums[i][0]);
        nums[i][1]=find(nums[i][1]);
        help[nums[i][0]]++;
        help[nums[i][1]]--;
    }
    int sum=0;
    for(int i=1;i<=m;i++){
        help[i]+=help[i-1];
    }
    for(int i=1;i<=m;i++){
        if(help[i]){
            sum+=val[i];
        }
        if(help[i]==1){
            help[i]=val[i];
        }
        else{
            help[i]=0;
        }
    }
    build(1,m,1);
    int ans=INT_MAX;
    for(int i=1;i<=n;i++){
        ans=min(ans,query(nums[i][0],nums[i][1]-1,1,m,1));
    }
    cout<<(sum-ans)<<endl;
    return 0;
}