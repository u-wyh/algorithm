#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;

int n;
int nums[MAXN];

int main()
{
    cin>>n;
    for(int i=1;i<n;i++){
        cin>>nums[i];
    }
    int l=0,r=0;
    for(int i=1;i<n;i++){
        if(nums[i]!=i){
            l=i;
            break;
        }
    }
    for(int i=n-1;i>=1;i--){
        if(nums[i]!=i){
            r=i;
            break;
        }
    }
    if(l==0&&r==0){
        cout<<0<<endl;
        return 0;
    }
    int flag=0;
    for(int i=l+1;i<=r;i++){
        if(nums[i]!=nums[i-1]+1){
            flag++;
        }
    }
    if(flag<=1){
        cout<<1<<endl;
    }
    else{
        cout<<2<<endl;
    }
    return 0;
}