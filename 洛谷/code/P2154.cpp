#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int MAXK = 12;
const int MOD = 2147483648ll;

int n,m,w,k;
struct node{
    int x,y;
}nums[MAXN];
int arr[MAXN<<1];
int ysz[MAXN<<1];
int upy[MAXN<<1];
int yval[MAXN<<1];
int comb[MAXN][MAXK];

int tree[MAXN<<1];

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

int find(int val){
    int l=1,r=m,ans=m;
    while(l<=r){
        int mid=(l+r)>>1;
        if(arr[mid]>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

inline int lowbit(int x){
    return x&-x;
}

void add(int x,int v){
    while(x<=m){
        tree[x]=(tree[x]+v)%MOD;
        x+=lowbit(x);
    }
}

int query(int x){
    int ans=0;
    while(x){
        ans=(ans+tree[x])%MOD;
        x-=lowbit(x);
    }
    return ans;
}

bool cmp(node a,node b){
    return a.x==b.x?a.y<b.y:a.x<b.x;
}

signed main()
{
    n=read(),m=read(),w=read();
    for(int i=1;i<=w;i++){
        nums[i].x=read(),nums[i].y=read();
        arr[2*i-1]=nums[i].x;
        arr[2*i]=nums[i].y;
    }
    k=read();
    for(int i=0;i<=w;i++){
        comb[i][0]=1;
        for(int j=1;j<=min(i,k);j++){
            comb[i][j]=(comb[i-1][j-1]+comb[i-1][j])%MOD;
        }
    }
    sort(arr+1,arr+2*w+1);
    m=1;
    for(int i=2;i<=2*w;i++){
        if(arr[i]!=arr[i-1]){
            arr[++m]=arr[i];
        }
    }
    for(int i=1;i<=w;i++){
        nums[i].x=find(nums[i].x);
        nums[i].y=find(nums[i].y);
        ysz[nums[i].y]++;
    }
    sort(nums+1,nums+w+1,cmp);
    int l=1,r=1;
    int ans=0;
    while(l<=w){
        r=l;
        // cout<<l<<' '<<r<<endl;
        // system("pause");
        while(r<=w&&nums[r].x==nums[l].x){
            r++;
        }
        r--;
        for(int i=l+1;i<=r;i++){
            ans=(ans+((comb[i-l][k]*comb[r-i+1][k])%MOD*((query(nums[i].y-1)-query(nums[i-1].y)+MOD)%MOD))%MOD)%MOD;
        }
        for(int i=l;i<=r;i++){
            upy[nums[i].y]++;
            add(nums[i].y,((comb[upy[nums[i].y]][k]*comb[ysz[nums[i].y]-upy[nums[i].y]][k])%MOD-yval[nums[i].y]+MOD)%MOD);
            yval[nums[i].y]=(comb[upy[nums[i].y]][k]*comb[ysz[nums[i].y]-upy[nums[i].y]][k])%MOD;
        }
        l=r+1;
    }
    ans=(ans+MOD)%MOD;
    cout<<ans<<endl;
    return 0;
}