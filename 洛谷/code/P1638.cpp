#include<bits/stdc++.h>
using namespace std;

int n,m;
int a[1000005];
int sum[2005];

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    int l=1,r=1,num=0,ans=n,ans1=1,ans2=n;
    while(l<=r&&r<=n+1){
        if(num<m){
            r++;
            sum[a[r-1]]++;
            if(sum[a[r-1]]==1)
                num++;
        }else{
            if(ans>r-l){
                ans=r-l;
                ans1=l;
                ans2=r-1;
            }
            sum[a[l]]--;
            if(sum[a[l]]==0)
                num--;
            l++;
        }
    }
    cout<<ans1<<' '<<ans2;
    return 0;
}
