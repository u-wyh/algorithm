// https://atcoder.jp/contests/abc224/tasks/abc224_c
// 题意：平面上给定 N 个整数坐标点 (X_i, Y_i)。
// 输出：从中任选 3 个不同点能构成正面积三角形的方案数。
// 数据范围：3 <= N <= 300，
// -10^9 <= X_i, Y_i <= 10^9。
// 任意两点的位置不同。
// 难度评分：900（AtCoder Problems 换算）
// 算法标签：枚举、计算几何
#include<bits/stdc++.h>
using namespace std;

int n;
struct Point{
    long long x,y;
};
Point nums[305];
Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}
long long operator*(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}
long long cross(Point a,Point b,Point c){
    return (b-a)*(c-a);
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i].x>>nums[i].y;
    }

    int ans=0;
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            for(int k=j+1;k<=n;k++){
                if(cross(nums[i],nums[j],nums[k])!=0){
                    ans++;
                }
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}