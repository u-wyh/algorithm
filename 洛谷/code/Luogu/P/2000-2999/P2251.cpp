#include<bits/stdc++.h>
using namespace std;

int n,k;
int minh=0,mint=0;
int minq[1000005];
int nums[1000005];

int main()
{
    cin>>n>>k;
    for(int i=0;i<n;i++)
        cin>>nums[i];
    for(int i=0;i<n;i++){
        while(minh<mint&&i-minq[minh]>=k){
            minh++;
        }
        while(minh<mint&&nums[i]<=nums[minq[mint-1]]){
            mint--;
        }
        minq[mint++]=i;
        if(i>=k-1)
            cout<<nums[minq[minh]]<<endl;
    }
    return 0;
}

