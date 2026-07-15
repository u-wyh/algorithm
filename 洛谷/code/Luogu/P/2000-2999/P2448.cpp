#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;

int nums[MAXN][2];
struct node{
    int x;
    int weight;
}arr[MAXN<<2];
int n;
int tot=0;
int cnt=0;
map<int,int>mp,mpy;
int tree[MAXN<<2];

bool cmp1(node a,node b){
    return a.x<b.x;
}

int lowbit(int i){
    return i&-i;
}

void add(int i,int  v){
    while(i<=tot){
        tree[i]+=v;
        i+=lowbit(i);
        //每一次都加上自己最右侧的1
    }
}

int sum(int i){
    int ans=0;
    while(i>0){
        ans+=tree[i];
        i-=lowbit(i);
        //每一次都减去自己最右侧的1
    }
    return ans;
}

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i][0]>>nums[i][1];
        arr[++tot].x=nums[i][0];
        arr[tot].weight=1;
        arr[++tot].x=nums[i][1];
        arr[tot].weight=1;
    }
    sort(arr+1,arr+2*n+1,cmp1);
    for(int i=2;i<=2*n;i++){
        if(arr[i].x>arr[i-1].x+1){
            arr[++tot].x=arr[i-1].x+1;
            arr[tot].weight=arr[i].x-arr[i-1].x-1;
        }
    }
    cnt=tot;
    //cout<<tot<<endl;
    sort(arr+1,arr+tot+1,cmp1);
    tot=0;
    mp[arr[1].x]=++tot;
    for(int i=2;i<=cnt;i++){
        if(arr[i].x!=arr[i-1].x){
            mp[arr[i].x]=++tot;
            //cout<<arr[i].x<<' '<<tot<<endl;
        }
    }
    //cout<<tot<<endl;
    for(int i=1;i<=n;i++){
        nums[i][0]=mp[nums[i][0]];
        nums[i][1]=mp[nums[i][1]];
        //cout<<nums[i][0]<<' '<<nums[i][1]<<endl;
    }
    for(int i=1;i<=cnt;i++){
        arr[i].x=mp[arr[i].x];
        //cout<<arr[i].x<<endl;
    }
    //cout<<endl;
    tot=0;
    mpy[arr[1].x]=++tot;
    for(int i=2;i<=cnt;i++){
        if(arr[i].x!=arr[i-1].x){
            arr[++tot].x=arr[i].x;
            arr[tot].weight=arr[i].weight;
            mpy[arr[i].x]=tot;
            //cout<<arr[tot].x<<' '<<arr[tot].weight<<endl;
        }
    }
    //cout<<tot<<endl;
    //cout<<endl;
    for(int i=1;i<=n;i++){
        //cout<<nums[i][0]<<' '<<nums[i][1]<<endl;
        //swap(arr[mpy[nums[i][0]]],arr[mpy[nums[i][0]]]);
        node temp=arr[mpy[nums[i][0]]];
        arr[mpy[nums[i][0]]]=arr[mpy[nums[i][1]]];
        arr[mpy[nums[i][1]]]=temp;
    }
    int ans=0;
    for(int i=1;i<=tot;i++){
        //cout<<arr[i].x<<' '<<arr[i].weight<<endl;
        ans+=(sum(tot)-sum(arr[i].x))*arr[i].weight;
        add(arr[i].x,arr[i].weight);
    }
    cout<<ans<<endl;
    return 0;
}
