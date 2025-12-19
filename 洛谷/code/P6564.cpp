#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n;
int tree[MAXN];
struct node{
    int val,sub;
}nums[MAXN];

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

bool cmp(node a,node b){
    return ((a.val-a.sub)==(b.val-b.sub))?(a.sub<b.sub):((a.val-a.sub)>(b.val-b.sub));
}

int lowbit(int x){
    return x&(-x);
}

int query(int x){
    int ans=0;
    while(x){
        ans=max(tree[x],ans);
        x-=lowbit(x);
    }
    return ans;
}

void update(int x,int val){
    while(x<=n){
        tree[x]=max(tree[x],val);
        x+=lowbit(x);
    }
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        nums[i].val=read();
        nums[i].sub=i;
    }
    sort(nums+1,nums+n+1,cmp);
    int ans=0;
    for(int i=1;i<=n;i++){
        if(nums[i].sub-nums[i].val<0)
            continue;
        int val=query(nums[i].val-1)+1;
        update(nums[i].val,val);
        ans=max(ans,val);
    }
    cout<<ans<<endl;
    return 0;
}
