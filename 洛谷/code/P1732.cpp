#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e4+5;
const int MAXM = 2e5+5;

int n,m,p,q;
struct node{
    int val,cost,id;
};
node nums[MAXM];
node tmp[MAXM];

int nums1[MAXN];
int nums2[MAXN];

struct compare1{
    bool operator()(int a,int b){
        return nums[a].cost<nums[b].cost;
    }
};
struct compare2{
    bool operator()(int a,int b){
        return tmp[a].cost>tmp[b].cost;
    }
};
priority_queue<int,vector<int>,compare1>heap1;
priority_queue<int,vector<int>,compare2>heap2;
bool vis[MAXM];

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

bool cmp(int a,int b){
    return a>b;
}

bool cmp1(node a,node b){
    return a.val>b.val;
}

bool cmp2(node a,node b){
    return a.cost<b.cost;
}

bool check(int limit){
    for(int i=1;i<=m;i++){
        vis[i]=false;
    }
    while(!heap1.empty()){
        heap1.pop();
    }
    while(!heap2.empty()){
        heap2.pop();
    }

    int now=1;
    for(int i=1;i<=p;i++){
        while(now<=m&&nums[now].val>=nums1[i]){
            heap1.push(now);
            now++;
        }
        int k=limit;
        while(k--){
            if(heap1.empty()){
                break;
            }
            int u=heap1.top();
            heap1.pop();
            vis[nums[u].id]=true;
        }
    }

    now=1;
    for(int i=1;i<=q;i++){
        while(now<=m&&tmp[now].cost<=nums2[i]){
            if(!vis[tmp[now].id]){
                heap2.push(now);
            }
            now++;
        }
        int k=limit;
        while(k--){
            if(heap2.empty()){
                break;
            }
            int u=heap2.top();
            heap2.pop();
            vis[tmp[u].id]=true;
        }
    }
    int all=0;
    for(int i=1;i<=m;i++){
        if(!vis[i]){
            all++;
        }
    }
    return 1ll*(n-p-q)*limit>=all;
}

int main()
{
    n=read(),m=read(),p=read(),q=read();
    for(int i=1;i<=m;i++){
        nums[i].val=read(),nums[i].cost=read();
        nums[i].id=i;
        tmp[i]=nums[i];
    }
    for(int i=1;i<=p;i++){
        nums1[i]=read();
    }
    for(int i=1;i<=q;i++){
        nums2[i]=read();
    }
    sort(nums1+1,nums1+p+1,cmp);
    sort(nums2+1,nums2+1+q);
    sort(nums+1,nums+m+1,cmp1);
    sort(tmp+1,tmp+m+1,cmp2);
    int l=1,r=m,ans=-1;
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
    cout<<ans<<endl;
    return 0;
}