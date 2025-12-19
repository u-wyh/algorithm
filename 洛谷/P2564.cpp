#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;
const int MAXK = 65;

int n,k;
struct node {
    int val,pos;
}nums[MAXN];
int sum[MAXK];

bool cmp(node a,node b){
    return a.pos<b.pos;
}

int main()
{
    cin>>n>>k;
    int m=1;
    for(int i=1;i<=k;i++){
        int t;
        cin>>t;
        for(int j=1;j<=t;j++){
            cin>>nums[m].pos;
            nums[m++].val=i;
        }
    }
    sort(nums+1,nums+n+1,cmp);
    int l=1,r=1,num=0,ans=n.l1,r1;
    while(r<=n+1){
        if(num<k){
            while(nums[r].pos==nums[l].pos){
                sum[nums[r].val]++;
                if(sum[nums[r].val]==1){
                    num++;
                }
                r++;
            }
            l1=l,r1=r;
        }else{
            ans=min(nums[r].pos-nums[l].pos);
        }
    }
    return 0;
}
