#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e6+5;

int n,m,k;
int arr[MAXN<<1];
int f[MAXN<<1];

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cntg=1;

int sta[MAXN];
int len;

void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

bool flag;

void dfs(int u){
    if(flag){
        return ;
    }
    sta[++len]=u;
    if(u<=n){
        if(len-1<=k || sta[len-k]>=u+n){
            flag=true;
            return;
        }
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs(v);
    }
    len--;
}

bool check(int limit){
    int r=1,sum=0;
    for(int l=1;l<=2*n;l++){
        while(r<=2*n&&sum+arr[r]<=limit){
            sum+=arr[r];
            r++;
        }
        f[l]=r;
        sum-=arr[l];
    }

    cntg=1;
    for(int i=1;i<=2*n+1;i++){
        head[i]=0;
    }
    for(int i=1;i<=2*n;i++){
        addedge(f[i],i);
    }

    flag=false;
    len=0;
    dfs(2*n+1);
    return flag;
}

void compute(){
    int l=0,r=0,sum=0;
    for(int i=1;i<=n;i++){
        l=max(l,arr[i]);
        sum+=arr[i];
    }
    if(m==1){
        cout<<sum<<endl;
        return ;
    }

    int ans=sum;
    r=sum;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    cout<<(ans*(m-1)+sum)<<endl;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m>>k;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        arr[i+n]=arr[i];
    }

    compute();

    return 0;
}