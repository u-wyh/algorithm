#include<bits/stdc++.h>
using namespace std;

int f1,f2,n,D;
int nums[2005],sum[2005];

int main()
{
    cin>>n>>f1>>f2>>D;
    int a,b;
    for(int i=1;i<=n;i++){
        cin>>a>>b;
        nums[a]+=1;
        if(b>=D)
            nums[D+1]+=-1;
        else
            nums[b+1]+=-1;
    }
    for(int i=1;i<=D;i++){
        nums[i]+=nums[i-1];
        sum[i]=sum[i-1]+nums[i];
    }
    int k;
    for(k=D;k>=1;k--){
        if(sum[D]-sum[k]==(f1-f2))
            break;
    }
    cout<<k+1;
    return 0;
}
