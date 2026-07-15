#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005;

int n;
struct point{
    int pos,val;
}nums[MAXN];
int f[MAXN][MAXN];
int ans;

bool cmp(point a,point b){
    return a.pos<b.pos;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i].pos>>nums[i].val;
    }
    sort(nums+1,nums+n+1,cmp);
    for(int j=1;j<=n;j++){
        //Ã¶¾ÙÌøµã
        f[j][j]=nums[j].val;
        int now=j;
        for(int i=j+1;i<=n;i++){
            f[i][j]=f[i-1][j]-nums[i-1].val;
            while(now>=1&&nums[j].pos-nums[now].pos<=nums[i].pos-nums[j].pos){
                f[i][j]=max(f[i][j],f[j][now--]);
            }
            f[i][j]+=nums[i].val;
            ans=max(ans,f[i][j]);
        }
    }
    for(int j=n;j>=1;j--){
        f[j][j]=nums[j].val;
        int now=j;
        for(int i=j-1;i>=1;i--){
            f[i][j]=f[i+1][j]-nums[i+1].val;
            while(now<=n&&nums[now].pos-nums[j].pos<=nums[j].pos-nums[i].pos){
                f[i][j]=max(f[i][j],f[j][now++]);
            }
            f[i][j]+=nums[i].val;
            ans=max(ans,f[i][j]);
        }
    }
    if(n==1){
        ans=nums[1].val;
    }
    cout<<ans<<endl;
    return 0;
}
