#include<bits/stdc++.h>
using namespace std;

int n,c;
int nums[200005];

int main()
{
    cin>>n>>c;
    for(int i=1;i<=n;i++)
        cin>>nums[i];
    sort(nums+1,nums+n+1);
    int l=1,r=1;
    long long sum=0;
    for(int i=1;i<=n;i++){
        while(nums[l]<nums[i]-c&&l<n)
            l++;
        while(nums[r]<=nums[i]-c&&r<n)
            r++;
        if(nums[r]-nums[l]==c)
            sum+=r-l;
    }
    cout<<sum;
    return 0;
}
