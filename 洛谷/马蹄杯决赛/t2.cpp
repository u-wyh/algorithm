#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n,m,k;
int nums[MAXN];

int main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
    }
    sort(nums+1,nums+n+1);
    m=1;
    for(int i=2;i<=n;i++){
        if(nums[i]!=nums[i-1]){
            nums[++m]=nums[i];
        }
    }
    if(m<k){
        cout<<-1<<endl;
    }
    else{
        cout<<nums[k]<<endl;
    }
    return 0;
}