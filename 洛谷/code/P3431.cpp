#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m,k;
struct node{
    int x,y,w;
}nums[MAXN];
map<int,int>mpx,mpy;
int x[MAXN],y[MAXN];
int tree[MAXN];
int dp[MAXN];
int tot;

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
    return a.x==b.x?a.y<b.y:a.x<b.x;
}

int lowbit(int i) {
	return i & -i;
}

void add(int i, int v) {
    while (i <= tot) {
        tree[i] = max(tree[i],v);
        i += lowbit(i);
    }
}

// 1~i·¶Î§µÄÀÛ¼ÓºÍ
int sum(int i) {
    int ans = 0;
    while (i > 0) {
        ans = max(tree[i],ans);
        i -= lowbit(i);
    }
    return ans;
}

int main()
{
    n=read(),m=read(),k=read();
    for(int i=1;i<=k;i++){
        nums[i].x=read();
        nums[i].y=read();
        nums[i].w=read();
        x[i]=nums[i].x,y[i]=nums[i].y;
    }
    sort(x+1,x+k+1);
    sort(y+1,y+k+1);
    tot=1;
    mpx[x[1]]=tot;
    for(int i=2;i<=k;i++){
        if(x[i]!=x[i-1]){
            mpx[x[i]]=++tot;
        }
    }
    tot=1;
    mpy[y[1]]=tot;
    for(int i=2;i<=k;i++){
        if(y[i]!=y[i-1]){
            mpy[y[i]]=++tot;
        }
    }
    for(int i=1;i<=k;i++){
        nums[i].x=mpx[nums[i].x];
        nums[i].y=mpy[nums[i].y];
    }
    int ans=0;
    sort(nums+1,nums+k+1,cmp);
    for(int i=1;i<=k;i++){
        dp[i]=nums[i].w+sum(nums[i].y);
        add(nums[i].y,dp[i]);
        ans=max(ans,dp[i]);
    }
    cout<<ans<<endl;
    return 0;
}
