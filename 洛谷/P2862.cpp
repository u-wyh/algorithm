#include<bits/stdc++.h>
using namespace std;
const int MAXN = 505;

int c,n;
int sum[MAXN<<1][MAXN<<1];
struct node{
    int x,y;
}nums[MAXN];
int help[MAXN<<1],cnt,m;

int getrank(int val){
    int l=1,r=m,ans;
    while(l<=r){
        int mid=(l+r)/2;
        if(help[mid]>=val){
            ans=mid;
            r=mid-1;
        }else{
            l=mid+1;
        }
    }
    return ans;
}

bool check(int len){
    for (int x1 = 0,x2 = 1; x2 <= m; x2++){
        while(help[x2] - help[x1 + 1] + 1 > len)
            x1++;
        for (int y1 = 0, y2 = 1; y2 <= m; y2++){
            while(help[y2] - help[y1 + 1] + 1 > len)
                y1++;
            if (sum[x2][y2] - sum[x1][y2] - sum[x2][y1] + sum[x1][y1] >= c)
                return true;
        }
    }
    return false;
}

int main()
{
    cin>>c>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i].x>>nums[i].y;
        help[++cnt]=nums[i].x;
        help[++cnt]=nums[i].y;
    }
    sort(help+1,help+cnt+1);
    for(int i=1;i<=cnt;i++){
        if(help[i]!=help[i-1]){
            help[++m]=help[i];
            //cout<<help[i]<<' ';
        }
    }
    //cout<<endl;
    for(int i=1;i<=n;i++){
        int x=getrank(nums[i].x);
        int y=getrank(nums[i].y);
        sum[x][y]++;
    }
    for(int i=1;i<=m;i++){
        for(int j=1;j<=m;j++){
            sum[i][j]+=sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
        }
    }
    int l=1,r=10005,ans=10005;
    while(l<=r){
        int mid=(l+r)/2;
        if(check(mid)){
            ans=mid;
            r=mid-1;
        }else{
            l=mid+1;
        }
    }
    cout<<ans<<endl;
    return 0;
}
