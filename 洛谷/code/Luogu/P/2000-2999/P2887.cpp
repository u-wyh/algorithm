#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2505;

struct node{
    int l,r;
}nums[MAXN];
int n,m;
struct point{
    int val,num;
}arr[MAXN];

bool cmp(node a,node b){
    return a.r<b.r;
}

bool cmp1(point a,point b){
    return a.val<b.val;
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>nums[i].l>>nums[i].r;
    }
    sort(nums+1,nums+n+1,cmp);
    for(int i=1;i<=m;i++){
        cin>>arr[i].val>>arr[i].num;
    }
    sort(arr+1,arr+m+1,cmp1);
    int ans=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(arr[j].num>0&&arr[j].val<=nums[i].r&&arr[j].val>=nums[i].l){
                arr[j].num--;
                ans++;
                break;
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}
