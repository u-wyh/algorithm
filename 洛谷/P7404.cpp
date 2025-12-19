#include<bits/stdc++.h>
using namespace std;

int n;
int nums[200005],d[200005];
long long x[200005],y[200005];

int main()
{
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>nums[i];
    }
    for(int i=1;i<n;i++){
        d[i]=nums[i]-nums[i-1];
    }
    for(int i=1;i<n;i++){
        if(d[i]<=0)
            x[i]=x[i-1]+1-d[i];
        else
            x[i]=x[i-1];
    }
    for(int i=n-1;i>=0;i--){
        if(d[i]>=0)
            y[i]=y[i+1]+d[i]+1;
        else
            y[i]=y[i+1];
    }
    long long  ans=1e15;
    for(int i=0;i<n;i++)
        ans=min(ans,max(x[i],y[i+1]));
    cout<<ans;
    //这道题是L到R区间  所以d[L]++  d[R+1]--但是我们不考虑一加一减
    //我们只在乎一个加或者减   到最后取最大值  即在完成一个任务时候顺便实现第二个目标
    return 0;
}
