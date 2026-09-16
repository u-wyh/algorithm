// https://www.luogu.com.cn/problem/P3722
// 那么对于区间L[i]到R[i]有p1的贡献.①
// 对于左端点在L[i]+1到i-1,右端点为R[i]的区间有p2的贡献.②
// 对于左端点为L[i],右端点为i+1到R[i]-1的区间也有p2的贡献.③
// 所以我们离线排序处理好.
// 对于①情况,我们在扫到R[i]时,更新点L[i]的贡献
// 对于②情况,我们在扫到R[i]时,更新区间L[i]+1到i-1的贡献
// 对于③情况,我们在扫到L[i]时,更新区间i+1到R[i]-1的贡献
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;

int n,m,p1,p2;
int nums[MAXN];
int l[MAXN];
int r[MAXN];
int st[MAXN],top;
int ans[MAXN];
struct node{
    int l,r;
    int x;
    int id;
    int v;
};
node arr1[MAXN*2];
node arr2[MAXN*3];
int cnt1,cnt2;
int tree1[MAXN];
int tree2[MAXN];

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
    return a.x<b.x;
}

inline int lowbit(int x){
    return x&-x;
}

void add(int x,int v){
    int t=x;
    while(x<=n){
        tree1[x]+=v;
        tree2[x]+=t*v;
        x+=lowbit(x);
    }
}

int query(int x){
    int ans=0;
    int t=x;
    while(x){
        ans+=(t+1)*tree1[x]-tree2[x];
        x-=lowbit(x);
    }
    return ans;
}

signed main()
{
    n=read(),m=read(),p1=read(),p2=read();
    for(int i=1;i<=n;i++){
        nums[i]=read();
    }
    // 记录左右两边第一个大于这个数字的位置 如果是0  表示不存在
    nums[n+1]=n+1;
    for(int i=1;i<=n+1;i++){
        while(top&&nums[st[top]]<nums[i]){
            r[st[top]]=i;
            top--;
        }
        l[i]=st[top];
        st[++top]=i;
    }
    for(int i=1;i<=m;i++){
        int x,y;
        x=read(),y=read();
        ans[i]=(y-x)*p1;
        if(x!=1){
            arr1[++cnt1]={x,y,x-1,i,-1};
        }
        arr1[++cnt1]={x,y,y,i,1};
    }
    sort(arr1+1,arr1+cnt1+1,cmp);
    for(int i=1;i<=n;i++){
        if(l[i]>=1&&r[i]<=n){
            arr2[++cnt2]={l[i],l[i],r[i],0,p1};
        }
        if(l[i]>=1){
            arr2[++cnt2]={i+1,r[i]-1,l[i],0,p2};
        }
        if(r[i]<=n){
            arr2[++cnt2]={l[i]+1,i-1,r[i],0,p2};
        }
    }
    sort(arr2+1,arr2+cnt2+1,cmp);

    int p1=1,p2=1;
    for(int i=1;i<=n;i++){
        while(p2<=cnt2&&arr2[p2].x==i){
            add(arr2[p2].l,arr2[p2].v);
            add(arr2[p2].r+1,-arr2[p2].v);
            p2++;
        }

        while(p1<=cnt1&&arr1[p1].x==i){
            ans[arr1[p1].id]+=arr1[p1].v*(query(arr1[p1].r)-query(arr1[p1].l-1));
            p1++;
        }
    }

    for(int i=1;i<=m;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}