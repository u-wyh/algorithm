// https://www.luogu.com.cn/problem/P3089
// 题意：输入目标点数量 N，以及每个目标点的坐标 x_i 和得分 p_i。
// 贝西从任意一个目标点出发，
// 选定一个方向（一直向左或一直向右）连续跳跃到其他目标点。
// 每次跳跃距离必须大于等于上一次跳跃的距离，求经过的所有目标点得分之和的最大值。
// 输出一个整数表示最大得分。
// 数据范围：1 <= N <= 1000，
// 0 <= x_i, p_i <= 10^6。
// 难度评分：1800（洛谷分级换算）
// 算法标签：动态规划、双指针、排序
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
        //枚举跳点
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
