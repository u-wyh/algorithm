#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MOD = 10007;

struct node{
    int pos,num,col;
}nums[MAXN];
int n,m;

bool cmp(node a,node b){
    return a.col<b.col;
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>nums[i].num;
        nums[i].pos=i;
    }
    for(int i=1;i<=n;i++){
        cin>>nums[i].col;
    }
    sort(nums+1,nums+n+1,cmp);
    int l=1,r=1;
    int ans=0;
    int sum1=0,sum2=0;

    while(r<=n){
        if(nums[l].pos%2){
            sum1+=nums[l].pos;
        }
        else{
            sum2+=nums[l].pos;
        }
        r++;
        //cout<<sum1<<' '<<sum2<<' ';
        while(nums[r].col==nums[l].col&&r<=n){
            if(nums[r].pos%2){
                sum1+=nums[r].pos;
            }
            else{
                sum2+=nums[r].pos;
            }
            r++;
        }
        //cout<<sum1<<' '<<sum2<<' ';
        for(int i=l;i<r;i++){
            if(nums[i].pos%2){
                sum1-=nums[i].pos;
                ans+=sum1*nums[i].pos;
            }
            else{
                sum2-=nums[i].pos;
                ans+=sum2*nums[i].pos;
            }
        }
        //cout<<sum1<<' '<<sum2<<endl;
        l=r;
    }
    for(int i=l;i<r;i++){
        if(nums[i].pos%2){
            sum1-=nums[i].pos;
            ans+=sum1*nums[i].pos;
        }
        else{
            sum2-=nums[i].pos;
            ans+=sum2*nums[i].pos;
        }
    }
    cout<<ans<<endl;
    return 0;
}
