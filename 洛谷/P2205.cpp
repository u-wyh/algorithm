#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,k;
int m=0,cnt=0;
int x[MAXN<<1];
struct node1{
    int l,r,len;
}nums[MAXN];
struct node{
    int val,occur;
};

int getrank(int val){
    int l=1,r=m,ans=m;
    while(l<=r){
        int mid=(l+r)/2;
        if(x[mid]>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

int main()
{
    cin>>n>>k;
    int pre=0;
    for(int i=1;i<=n;i++){
        int pos;
        char c;
        cin>>pos>>c;
        nums[i].len=pos;
        if(c=='L'){
            pos*=-1;
        }
        pos+=pre;
        nums[i].l=min(pre,pos);
        nums[i].r=max(pre,pos);
    }
    for(int i=1;i<=n;i++){
        x[++cnt]=nums[i].l;
        x[++cnt]=nums[i].r-1;
    }
    sort(x+1,x+cnt);
    x[++m]=x[1];
    for(int i=2;i<=cnt;i++){
        if(x[i]!=x[i-1]){
            x[++m]=x[i];
        }
    }
    for(int i=1;i<=n;i++){
        nums[i].l=getrank(nums[i].l);
        nums[i].r=getrank(nums[i].r-1);
    }
    return 0;
}
