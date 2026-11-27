// https://www.luogu.com.cn/problem/P3194
// 题意：输入直线数量 N，以及 N 条互不重合直线 y = A_i x + B_i 的参数 A_i 和 B_i。
// 若从 y = +∞ 处垂直向下看时能看到某条直线的至少一段非退化子线段（即存在某个开区间 x 上该直线严格高于其他所有直线），则称该直线可见。
// 按编号从小到大输出所有可见直线的编号，空格分隔且末尾需有一个空格。
// 数据范围：0 < N <= 50000，|A_i|, |B_i| <= 500000。
#include<bits/stdc++.h>
// 算法标签：凸包、单调栈、计算几何
using namespace std;
const int MAXN = 5e4+5;

struct Point{
    double x,y;
    int id;
};
Point nums[MAXN];
int n;
int top;
Point sta[MAXN];

bool cmp(Point &a,Point &b){
    if(a.x!=b.x){
        return a.x<b.x;
    }
    return a.y<b.y;
}

double cross(Point a,Point b,Point c){
    return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);
}

double dis(Point a,Point b){
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

int ans[MAXN];
void Andrew(){
    sort(nums+1,nums+n+1,cmp);
    for(int i=n;i>=1;i--){
        if(i<n && nums[i].x==nums[i+1].x){
            continue;
        }
        while(top>1 && cross(sta[top-1],sta[top],nums[i])<=0){
            top--;
        }
        sta[++top]=nums[i];
    }
    double res=0;
    for(int i=1;i<=top;i++){
        // res+=dis(sta[i],sta[i+1]);
        ans[i]=sta[i].id;
    }
    sort(ans+1,ans+top+1);
    for(int i=1;i<=top;i++){
        cout<<ans[i]<<' ';
    }
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i].x>>nums[i].y;
        nums[i].id=i;
    }
    Andrew();
    return 0;
}