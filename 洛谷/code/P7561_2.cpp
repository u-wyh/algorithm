#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 3e5+5;
const int MAXK = 5e5+5;
const int INF = 4e9+5;

int n,k;
struct node{
    int x,y;
};
node nums[MAXN];
int sorted[MAXN];
int len;

int tree[MAXN];

int lowbit(int x){
    return x&-x;
}

int query(int x){
    if(x==0){
        return 0;
    }
    int ans=0;
    while(x){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}

void add(int x,int v){
    while(x<=len){
        tree[x]+=v;
        x+=lowbit(x);
    }
}

bool cmp(node &a,node &b){
    return a.x<b.x;
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

bool check(int limit){
    int cnt=0;
    for(int i=1;i<=len;i++){
        tree[i]=0;
    }
    int l=1;
    for(int r=1;r<=n;r++){
        int v=sorted[nums[r].y];
        int lt=find1(v-limit);
        int rt=find2(v+limit)-1;
        while(nums[r].x-nums[l].x>limit){
            add(nums[l].y,-1);
            l++;
        }
        cnt+=query(rt)-query(lt-1);
        if(cnt>=k){
            return true;
        }
        add(nums[r].y,1);
    }
    return false;
}

multiset<pair<int,int> > mst;
int res[MAXN];
int cntres;
// 枚举所有距离 <= limit 的点对
// 实际调用 limit = 第k小距离 - 1
void compute(int limit){
    if(limit<0){
        return ;
    }

    int l=1;
    for(int r=1;r<=n;r++){
        while(nums[r].x-nums[l].x>limit){
            int yl=sorted[nums[l].y];
            mst.erase(mst.find({yl,l}));
            l++;
        }

        int yr=sorted[nums[r].y];
        auto it1=mst.lower_bound({yr-limit,-INF});
        auto it2=mst.upper_bound({yr+limit,INF});
        for(auto it=it1;it!=it2;it++){
            int j=it->second;
            int yj=it->first;
            int d=max(nums[r].x-nums[j].x,abs(yr-yj));
            res[++cntres]=d;
        }

        mst.insert({yr,r});
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>k;
    for(int i=1;i<=n;i++){
        int x,y;
        cin>>x>>y;
        nums[i]={x+y,x-y};
        sorted[i]=x-y;
    }
    sort(nums+1,nums+n+1,cmp);

    sort(sorted+1,sorted+n+1);
    len=1;
    for(int i=2;i<=n;i++){
        if(sorted[i]!=sorted[i-1]){
            sorted[++len]=sorted[i];
        }
    }

    for(int i=1;i<=n;i++){
        nums[i].y=find1(nums[i].y);
    }

    int l=0,r=INF,ans=0;
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
    compute(ans-1);

    sort(res+1,res+cntres+1);
    for(int i=1;i<=cntres;i++){
        cout<<res[i]<<endl;
    }
    for(int i=cntres+1;i<=k;i++){
        cout<<ans<<endl;
    }
    return 0;
}