#include<bits/stdc++.h>
using namespace std;
const int MAXN = 35005;
const int INF = 1e9;

int n;
int nums[MAXN];
int f[MAXN];
int g[MAXN];

int arr[MAXN];
int len=0;

int find(int val){
    int l=1,r=n,ans=-1;
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

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
        nums[i]-=i;
    }
    nums[0]=-INF;
    nums[n+1]=INF;

    arr[++len]=nums[0];
    f[0]=1;
    for(int i=1;i<=n+1;i++){
        if(nums[i]>=arr[len]){
            arr[++len]=nums[i];
            f[i]=len;
        }
        else{
            int sub=find(nums[i]);
            f[i]=sub;
            arr[sub]=nums[i];
        }
    }
    cout<<(n+2-len)<<endl;

    
    return 0;
}