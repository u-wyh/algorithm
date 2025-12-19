#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3005;

int n,m,s,t;
int nums[MAXN][MAXN];

int fun(int X1,int Y1,int X2,int Y2){
    return nums[X2][Y2]+nums[X1-1][Y1-1]-nums[X2][Y1-1]-nums[X1-1][Y2];
}

int main()
{
    cin>>n>>m>>s;
    for(int i=1,a,b,c,d;i<=s;i++){
        cin>>a>>b>>c>>d;
        nums[a][b]+=1;
        nums[a][d+1]-=1;
        nums[c+1][b]-=1;
        nums[c+1][d+1]+=1;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            nums[i][j]+=nums[i-1][j]+nums[i][j-1]-nums[i-1][j-1];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(nums[i][j]>=1)
                nums[i][j]=1;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            nums[i][j]+=nums[i-1][j]+nums[i][j-1]-nums[i-1][j-1];
        }
    }
    cin>>t;
    for(int i=1,a,b,c,d;i<=t;i++){
        cin>>a>>b>>c>>d;
        if(fun(a,b,c,d)==((c-a+1)*(d-b+1)))
            cout<<"Yes\n";
        else
            cout<<"No\n";
    }
    return 0;
}
