#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int MAXVAL = 1e18;

int n,k;
struct node{
    int val,cnt;
};
int nums[MAXN];
node tree[MAXN];
int f[MAXN];
int g[MAXN];
// 统计答案
bool vis[MAXN];
int ans[MAXN];
int cnt;

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

inline int lowbit(int x){
    return x&-x;
}

node merge(node a,node b){
    if(a.val==b.val){
        return {a.val,min(a.cnt+b.cnt,MAXVAL)};
    }
    else if(a.val>b.val){
        return a;
    }
    else{
        return b;
    }
}

void update(int x,node v){
    while(x){
        tree[x]=merge(tree[x],v);
        x-=lowbit(x);
    }
}

node query(int x){
    node ans={0,0};
    while(x<=n){
        ans=merge(ans,tree[x]);
        x+=lowbit(x);
    }
    return ans;
}

signed main()
{
    n=read(),k=read();
    for(int i=1;i<=n;i++){
        nums[i]=read();
    }
    int len=0;
    for(int i=n;i>=1;i--){
        node ans=query(nums[i]);
        ans.val++;
        ans.val=min(ans.val,MAXVAL);
        ans.cnt=max(1ll,ans.cnt);
        f[nums[i]]=ans.val;
        g[nums[i]]=ans.cnt;
        len=max(len,ans.val);
        update(nums[i],ans);
    }
    int lst=0;
    for(int i=1;i<=n;i++){
        if(f[nums[i]]==len&&nums[i]>lst){
            if(g[nums[i]]<k){
                k-=g[nums[i]];
            }
            else{
                vis[i]=true;
                lst=nums[i];
                len--;
            }
        }
    }
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            ans[++cnt]=nums[i];
        }
    }
    sort(ans+1,ans+cnt+1);
    cout<<cnt<<endl;
    for(int i=1;i<=cnt;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}