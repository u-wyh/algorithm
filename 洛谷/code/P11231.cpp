#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n;
int nums[MAXN];

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
    }
    sort(nums+1,nums+n+1);
    int u=1;
    for(int i=2;i<=n;i++){
        if(nums[i]>nums[u]){
            u++;
        }
    }
    cout<<(n-u+1)<<endl;
    return 0;
}