#include<bits/stdc++.h>
using namespace std;

int n;

struct node{
    int l,r;
}nums[2005];

bool cmp(node a,node b){
    return a.r==b.r?a.l>b.l:a.r<b.r;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        int h1,m1,s1,h2,m2,s2;
        scanf("%d:%d:%d %d:%d:%d",&h1,&m1,&s1,&h2,&m2,&s2);
        nums[i].l=h1*3600+m1*60+s1;
        nums[i].r=h2*3600+m2*60+s2;
        // cout<<nums[i].l<<' '<<nums[i].r<<endl;
    }
    sort(nums+1,nums+n+1,cmp);
    int ans=0;
    int lst=-1;
    for(int i=1;i<=n;i++){
        if(nums[i].l>=lst){
            ans++;
            lst=nums[i].r;
        }
    }
    cout<<ans<<endl;
    return 0;
}