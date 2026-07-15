#include<bits/stdc++.h>
using namespace std;

struct node{
    char u,v;
}nums[110];
int n;

bool cmp(node a,node b){
    return a.v==b.v?a.u<b.u:a.v<b.v;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i].u>>nums[i].v;
    }
    sort(nums+1,nums+n+1,cmp);
    int u=0,v=0,ans=0;
    for(int i=1;i<=n+1;i++){
        if(nums[i].v==nums[i-1].v){
            u++;
            if(nums[i].u==nums[i-1].u){
                v++;
            }
        }
        else{
            //cout<<u<<' '<<v<<endl;
            int k=u-2*v;
            if(k>v){
                ans+=v;
            }
            else{
                ans+=(k+(v-(u-2*v))*2/3);
            }
            u=1,v=0;
        }
    }
    cout<<ans<<endl;
    return 0;
}
