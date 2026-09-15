#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;
const int INF = 2e10;

int n,a,b,d;

int x[MAXN];
int y[MAXN];

int idx[MAXN];
int idy[MAXN];

int sorted[MAXN];
int len;

set<pair<int,int>>sx[MAXN];
set<pair<int,int>>sy[MAXN];

bool vis[MAXN];
int q[MAXN];
int ql=1,qr=0;

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
    int l=1,r=len,ans=len+1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(sorted[mid]>x){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

void sterase(int i){
    sx[idx[i]].erase({y[i],i});
    sy[idy[i]].erase({x[i],i});
}

void queryx(int x,int yl,int yr){
    int idx=find1(x);
    if(sorted[idx]!=x){
        return ;
    }
    
    auto it=sx[idx].lower_bound({yl,-INF});
    while(it!=sx[idx].end()&&it->first<=yr){
        int u=it->second;
        it++;
        vis[u]=true;
        q[++qr]=u;
        sterase(u);
    }
}


void queryy(int y,int xl,int xr){
    int idy=find1(y);
    if(sorted[idy]!=y){
        return ;
    }
    
    auto it=sy[idy].lower_bound({xl,-INF});
    while(it!=sy[idy].end()&&it->first<=xr){
        int u=it->second;
        it++;
        vis[u]=true;
        q[++qr]=u;
        sterase(u);
    }
}

pair<int,int> arrx[MAXN];
pair<int,int> arry[MAXN];
int cnt;
int query(pair<int,int> arr[],int v,int l,int r){
    if(l>r){
        return 0;
    }

    int lt=lower_bound(
        arr+1,
        arr+cnt+1,
        make_pair(v,l)
    )-arr;

    int rt=upper_bound(
        arr+1,
        arr+cnt+1,
        make_pair(v,r)
    )-arr;

    return rt-lt;
}

signed main()
{
    cin>>n>>a>>b;
    for(int i=1;i<=n;i++){
        int xx,yy;
        cin>>xx>>yy;
        x[i]=xx+yy;
        y[i]=xx-yy;
        sorted[i]=x[i];
        sorted[i+n]=y[i];
    }
    d=max(abs(x[a]-x[b]),abs(y[a]-y[b]));

    sort(sorted+1,sorted+2*n+1);
    len=1;
    for(int i=2;i<=2*n;i++){
        if(sorted[i]!=sorted[i-1]){
            sorted[++len]=sorted[i];
        }
    }
    for(int i=1;i<=n;i++){
        idx[i]=find1(x[i]);
        idy[i]=find1(y[i]);

        sx[idx[i]].insert({y[i],i});
        sy[idy[i]].insert({x[i],i});
    }

    sterase(a);
    sterase(b);
    vis[a]=vis[b]=true;
    q[++qr]=a;
    q[++qr]=b;
    while(ql<=qr){
        int u=q[ql++];
        queryx(x[u]-d,y[u]-d,y[u]+d);
        queryx(x[u]+d,y[u]-d,y[u]+d);
        queryy(y[u]-d,x[u]-d,x[u]+d);
        queryy(y[u]+d,x[u]-d,x[u]+d);
    }

    for(int i=1;i<=n;i++){
        if(vis[i]){
            arrx[++cnt]={x[i],y[i]};
            arry[cnt]={y[i],x[i]};
        }
    }

    sort(arrx+1,arrx+cnt+1);
    sort(arry+1,arry+cnt+1);

    long long ans=0;
    for(int i=1;i<=n;i++){
        if(vis[i]){
            ans+=query(arrx,x[i]+d,y[i]-d,y[i]+d);
            ans+=query(arry,y[i]+d,x[i]-d+1,x[i]+d-1);
        }
    }
    cout<<ans<<endl;
    return 0;
}