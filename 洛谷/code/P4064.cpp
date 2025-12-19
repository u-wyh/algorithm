#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n,m,k,q;
struct node{
    int l,r;
}nums[MAXN];
int arr[MAXN];
int tree[MAXN];

struct compare{
    bool operator()(pair<int,int>&a,pair<int,int>&b){
        return a.second<b.second;
    }
};
priority_queue<pair<int,int>,vector<pair<int,int>>,compare>heap;//大根堆 按照右端点排序

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
    return (a.l==b.l)?(a.r>b.r):(a.l<b.l);
}

inline int lowbit(int x){
    return x&(-x);
}

void add(int x,int v){
    while(x<=n){
        tree[x]+=v;
        x+=lowbit(x);
    }
}

int sum(int x){
    int ans=0;
    while(x){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}

bool check(int limit){
    while(!heap.empty()){
        heap.pop();
    }
    for(int i=1;i<=n;i++){
        tree[i]=0;
    }
    for(int i=1;i<=n;i++){
        //维持差分数组
        add(i,arr[i]-arr[i-1]);
    }
    int cnt=0,tot=1;//tot表示当前来到了第几个区间  cnt表示已经使用了多少个区间
    for(int i=1;i<=n;i++){
        while(tot<=m&&nums[tot].l<=i){
            if(nums[tot].r>=i){
                heap.push({nums[tot].l,nums[tot].r});
            }
            tot++;
        }
        while(sum(i)<limit){
            if(heap.empty()){
                //表示已经没有任何区间可以帮助这个点达标
                return false;
            }
            if(cnt==k){
                //表示前面的点已经耗费了所有的指标
                return false;
            }
            if(heap.top().first<=i&&heap.top().second>=i){
                cnt++;
                add(heap.top().first,q);
                add(heap.top().second+1,-q);
            }
            heap.pop();
        }
    }
    return true;
}

int main()
{
    int T;
    T=read();
    while(T--){
        n=read(),m=read(),k=read(),q=read();
        int l=1e8,r=1e8;
        for(int i=1;i<=n;i++){
            arr[i]=read();
            l=min(l,arr[i]);
        }
        r=k*q+l;
        for(int i=1;i<=m;i++){
            nums[i].l=read(),nums[i].r=read();
        }
        sort(nums+1,nums+m+1,cmp);//按照左端点排序 左端点相同 按照右端点排序
        int ans=l;
        while(l<=r){
            int mid=(l+r)/2;
            if(check(mid)){
                ans=mid;
                l=mid+1;
            }
            else{
                r=mid-1;
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}