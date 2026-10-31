// https://www.luogu.com.cn/problem/P10281、
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n;
struct node{
    int l,r,k,id;
};
node nums[MAXN];
node tmp[MAXN];

int sorted[MAXN*3];
int len;

int ans[MAXN];

int tree[MAXN*3];

int lowbit(int x){
    return x&-x;
}

void add(int x,int v){
    while(x<=len){
        tree[x]+=v;
        x+=lowbit(x);
    }
}

int query(int x){
    int ans=0;
    while(x){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}

bool cmp1(node &a,node &b){
    return a.r<b.r;
}

bool cmp2(node &a,node &b){
    return (a.l+a.k)<(b.l+b.k);
}

bool cmp3(node &a,node &b){
    return a.k<b.k;
}

bool cmp4(node &a,node &b){
    return (a.r-a.l)<(b.r-b.l);
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

void compute(){
    sort(tmp+1,tmp+n+1,cmp1);
    sort(nums+1,nums+n+1,cmp2);
    int p2=n;
    for(int i=n;i>=1;i--){
        while(p2 && (nums[i].k+nums[i].l<=tmp[p2].r)){
            add(find1(tmp[p2].l),1);
            p2--;
        }
        int id=nums[i].id;
        ans[id]+=query(find1(nums[i].l));
    }

    for(int i=1;i<=len;i++){
        tree[i]=0;
    }

    sort(tmp+1,tmp+n+1,cmp4);
    sort(nums+1,nums+n+1,cmp3);
    p2=n;
    for(int i=n;i>=1;i--){
        while(p2 && (nums[i].k<=tmp[p2].r-tmp[p2].l)){
            add(find1(tmp[p2].l),1);
            p2--;
        }
        int id=nums[i].id;
        ans[id]+=query(find2(nums[i].r-nums[i].k))-query(find1(nums[i].l));
    }
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        int l,r,k;
        cin>>l>>r>>k;
        nums[i]={l,r,k,i};
        tmp[i]=nums[i];
        sorted[i]=l;
        sorted[i+n]=r;
        sorted[i+2*n]=r-k;
    }

    sort(sorted+1,sorted+3*n+1);
    len=1;
    for(int i=2;i<=3*n;i++){
        if(sorted[i]!=sorted[i-1]){
            sorted[++len]=sorted[i];
        }
    }

    compute();

    for(int i=1;i<=n;i++){
        cout<<(ans[i]-1)<<endl;
    }
    return 0;
}