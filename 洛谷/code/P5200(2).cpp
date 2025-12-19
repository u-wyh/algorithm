#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100005;

int tree[MAXN],arr[MAXN];
int n;

int lowbit(int x){
    return x & -x;
}

void add(int i,int v){
    while(i<=n){
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
//这个函数求的是从1到i所有数字的和


int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    int ans=0;
    for(int i=n;i>0;i--){
        if(arr[i]<arr[i-1]){
            ans=i-1;
            break;
        }
        add(arr[i],1);
    }
    add(arr[ans+1],1);
    cout<<ans<<endl;
    for(int i=1;i<=ans;i++){
        add(arr[i],1);
        cout<<ans-i+sum(arr[i]-1)<<' ';
    }
    return 0;
}
