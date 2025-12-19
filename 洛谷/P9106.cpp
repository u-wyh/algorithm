#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int n;
int arr[MAXN];
int nums[MAXN];
int l,r;
int sum=0;

int main()
{
    cin>>n;
    l=n/2,r=l+1;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
        if(sum>=n-i+1){
            arr[nums[i]=-1;
            continue;
        }
        if(nums[i]<=l){
            arr[nums[i]]=1;
            sum++;
            l--,r--;
        }
        else if(nums[i]>=r&&sum==0){
            arr[nums[i]]=1;
            l--,r--;
            sum++;
        }
        else{
            arr[nums[i]]=-1;
            sum--;
            l++,r++;
        }
        cout<<arr[nums[i]]<<' ';
        //cout<<nums[i]<<' '<<l<<' '<<r<<' '<<arr[nums[i]]<<endl;
    }
    cout<<endl;
    for(int i=1;i<=n;i++){
        cout<<arr[i]<<' ';
    }
    cout<<endl;
    sum=0;
    for(int i=1;i<=n;i++){
        sum+=arr[i];
        if(sum<0){
            cout<<"NIE"<<endl;
            return 0;
        }
    }
    for(int i=1;i<=n;i++){
        if(arr[i]==1){
            cout<<"(";
        }
        else{
            cout<<")";
        }
    }
    return 0;
}
