#include<bits/stdc++.h>
using namespace std;

int n,m,k;
int nums[505][505];
int sum[505][505];

//左上角x1 y1  右下角x2 y2  x1<=x2  y1<=y2
void Set(int a,int b,int c,int d,int v){
    nums[a][b]+=v;
    nums[a][d+1]-=v;
    nums[c+1][b]-=v;
    nums[c+1][d+1]+=v;
}

int fun(int X1,int Y1,int X2,int Y2){
    return sum[X2][Y2]+sum[X1-1][Y1-1]-sum[X2][Y1-1]-sum[X1-1][Y2];
}

void build(){
    //来一遍二维前缀和即可
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            nums[i][j]+=nums[i-1][j]+nums[i][j-1]-nums[i-1][j-1];
        }
    }
}

bool check(int limit){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(fun(max(1,i-limit),max(1,j-limit),min(n,i+limit),min(m,j+limit))==0){
                return true;
            }
        }
    }
    return false;
}

int main()
{
    cin>>n>>m>>k;
    for(int i=1;i<=k;i++){
        int x,y,w;
        cin>>x>>y>>w;
        Set(max(1,x-w),max(1,y-w),min(n,x+w),min(m,y+w),1);
    }
    build();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+nums[i][j];
        }
    }
    int l=0,r=max(n,m),ans=-1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)){
            ans=mid;
            l=mid+1;
        }
        else{
            r=mid-1;
        }
    }
    cout<<ans<<endl;
    return 0;
}