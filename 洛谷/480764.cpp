#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

struct node{
    int gold,silver,copper;
    int rate;
    int sub;
}nums[MAXN];
int n;

bool cmp1(node a,node b){
    return a.gold>b.gold;
}

bool cmp2(node a,node b){
    return a.silver>b.silver;
}

bool cmp3(node a,node b){
    return a.copper>b.copper;
}

bool cmp4(node a,node b){
    return a.sub<b.sub;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i].gold>>nums[i].silver>>nums[i].copper;
        nums[i].rate=n;
        nums[i].sub=i;
    }
    sort(nums+1,nums+n+1,cmp1);
    nums[1].rate=1;
    int tmp=1,tmp2=nums[1].gold;
    for(int i=2;i<=n;i++){
        if(nums[i].gold==tmp2){
            nums[i].rate=tmp;
        }
        else
        {
            nums[i].rate=i;
            tmp=i;
            tmp2=nums[i].gold;
        }
    }
    sort(nums+1,nums+n+1,cmp2);
    nums[1].rate=1;
    tmp=1,tmp2=nums[1].silver;
    for(int i=2;i<=n;i++){
        if(nums[i].silver==tmp2){
            nums[i].rate=min(tmp,nums[i].rate);
        }
        else
        {
            nums[i].rate=min(i,nums[i].rate);
            tmp=i;
            tmp2=nums[i].silver;
        }
    }
    sort(nums+1,nums+n+1,cmp3);
    nums[1].rate=1;
    tmp=1,tmp2=nums[1].copper;
    for(int i=2;i<=n;i++){
        if(nums[i].copper==tmp2){
            nums[i].rate=min(tmp,nums[i].rate);
        }
        else
        {
            nums[i].rate=min(i,nums[i].rate);
            tmp=i;
            tmp2=nums[i].copper;
        }
    }
    sort(nums+1,nums+n+1,cmp4);
    for(int i=1;i<=n;i++){
        cout<<nums[i].rate<<endl;
    }
    return 0;
}
