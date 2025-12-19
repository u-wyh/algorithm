#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int n,m;
struct node{
    int l,r;
};
node nums[MAXN];

bool cmp(node a,node b){
    return a.r<b.r;
}

int main()
{
    int T;
    cin>>T;
    while(T--){
        cin>>n>>m;
        for(int i=1;i<=m;i++){
            cin>>nums[i].l>>nums[i].r;
        }
        sort(nums+1,nums+m+1,cmp);
        int lst=0;
        int nodecnt=0;
        for(int i=1;i<=m;i++){
            if(nums[i].l>lst){
                nodecnt++;
                lst=nums[i].r;
            }
        }
        int ans=0;
        while(((1<<ans)-1<nodecnt)){
            ans++;
        }
        cout<<ans<<endl;
    }
    return 0;
}