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
    }
    int f=f1-f2;
    for(int i=D;i>=1;i--){
        f-=nums[i];
        if(f==0){
            cout<<i;
            return 0;
        }
    }
    return 0;
}
