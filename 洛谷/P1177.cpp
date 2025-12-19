#include<bits/stdc++.h>
using namespace std;

int n;
int nums[100005];

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>nums[i];
    sort(nums+1,nums+n+1);
    for(int i=1;i<=n;i++)
        printf("%d ",nums[i]);
    return 0;
}
