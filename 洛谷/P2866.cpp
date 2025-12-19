#include<bits/stdc++.h>
using namespace std;

int n;
int nums[80005];
int q[80005];
int r=0;
long long ans=0;

int main()
{
    cin>>n;
    for(int i=0;i<n;i++)
        cin>>nums[i];
    for(int i=0;i<n;i++){
        while(r>0&&nums[q[r-1]]<=nums[i]){
            ans+=(i-q[--r]-1);
            //printf("%d\n",ans);
        }
        q[r++]=i;
    }
    while(r>0){
        ans+=(n-1-q[--r]);
        //printf("%d\n",ans);
    }
    cout<<ans;
    return 0;
}
