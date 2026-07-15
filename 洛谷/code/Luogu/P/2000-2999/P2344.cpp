#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+9;
const int MAXN = 1e5+5;

int n,m;
int arr[MAXN];
int temp[MAXN];
int tree[MAXN];
map<int,int>mp;
int tot;

int lowbit(int i){
    return i&-i;
}

void add(int i,int v){
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
    arr[1]=0;
    for(int i=2;i<=1+n;i++){
        cin>>arr[i];
        arr[i]+=arr[i-1];
        temp[i]=arr[i];
        //cout<<arr[i]<<endl;
    }
    sort(temp+1,temp+n+2);
    mp[temp[1]]=++tot;
    for(int i=2;i<=n+1;i++){
        if(temp[i]!=temp[i-1]){
            mp[temp[i]]=++tot;
        }
    }
    for(int i=1;i<=n+1;i++){
        arr[i]=mp[arr[i]];
    }
    int ans=0,tmp=0;
    add(arr[1],1);
    for(int i=2;i<=n+1;i++){
        ans=sum(arr[i]);
        ans%=MOD;
        add(arr[i],ans);
        //cout<<arr[i]<<' '<<ans<<endl;
    }
    cout<<ans<<endl;
    return 0;
}
