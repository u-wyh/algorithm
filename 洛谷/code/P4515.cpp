// https://www.luogu.com.cn/problem/P4515
// 输入：第一行一个整数 N，表示等腰直角三角形的数量。
// 输入：接下来 N 行，每行三个整数 X, Y, R，表示三角形直角顶点在左下角 (X,Y)，两腰分别平行于坐标轴且长度为 R。
// 题意：平面上被奇数个三角形覆盖的区域视为灰色，被偶数个三角形覆盖的区域视为白色。
// 题意：求所有灰色区域的总面积。
// 输出：输出一行一个实数，表示灰色部分面积，保留 1 位小数。
// 数据范围：1 <= N <= 10
// 数据范围：1 <= X, Y, R <= 10^6
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 11;
const int INF = 4e18;

int n;
struct Triangle{
    int x,y,r;
};
Triangle nums[MAXN];

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i].x>>nums[i].y>>nums[i].r;
    }
    int ans=0;
    for(int mask=1;mask<(1<<n);mask++){
        int maxx=0,maxy=0,minsum=INF;
        int cnt=0;
        for(int i=1;i<=n;i++){
            if(mask&(1<<(i-1))){
                cnt++;
                maxx=max(maxx,nums[i].x);
                maxy=max(maxy,nums[i].y);
                minsum=min(minsum,nums[i].x+nums[i].y+nums[i].r);
            }
        }
        // cout<<maxx<<' '<<maxy<<' '<<minsum<<endl;
        int r=minsum-maxx-maxy;
        if(r<=0){
            continue;
        }

        int v=1<<(cnt-1);
        if(cnt%2==0){
            v=-v;
        }

        ans+=v*r*r;
        // cout<<mask<<":   "<<cnt<<' '<<r<<endl;
    }
    // cout<<ans<<endl;
    cout<<ans/2<<(ans%2?".5":".0")<<endl;

    return 0;
}
