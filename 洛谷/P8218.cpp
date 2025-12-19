#include<bits/stdc++.h>
using namespace std;

int n,m;
int nums[100005];
long long sum[100005];

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
        sum[i]=sum[i-1]+nums[i];
    }
    int i,j;
    cin>>m;
    while(m--){
        cin>>i>>j;
        cout<<sum[j]-sum[i-1]<<endl;
    }
    return 0;
}
