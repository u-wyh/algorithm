// https://www.luogu.com.cn/problem/P1863
// 题意：兔子先从最靠左的胡萝卜的正左方走向它，再依次直线走向选中的胡萝卜。
// 每次转向不能右转，后续路线不能与走过的路线相交。
// 输出最多能吃的数量及其原编号顺序。
// 数据范围：n ≤ 1000，横纵坐标均在 [1,10^4]，各点横坐标互异，
// 纵坐标也互异。
// 难度评分：1900（洛谷分级换算）
// 算法标签：计算几何、贪心

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e3+5;

int n;
struct Point{
    int x,y;
};
Point p[MAXN];

int ans[MAXN];
int cnt;
bool vis[MAXN];

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

int cross(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

int len(Point a){
    return a.x*a.x+a.y*a.y;
}

int choose(int u){
    int v=0;
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            v=i;
            break;
        }
    }
    for(int i=1;i<=n;i++){
        if(vis[i]){
            continue;
        }
        int val=cross(p[v]-p[u],p[i]-p[u]);
        if(val<0){
            v=i;
        }
        else if(val==0){
            if(len(p[u]-p[v])>len(p[u]-p[i])){
                v=i;
            }
        }
    }
    return v;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>p[i].x>>p[i].y;
    }

    int first=1;
    for(int i=2;i<=n;i++){
        if(p[i].y<=p[first].y){
            first=i;
        }
    }
    vis[first]=true;
    ans[++cnt]=first;
    while(cnt<n){
        int u=ans[cnt];
        ans[++cnt]=choose(u);
        vis[ans[cnt]]=true;
    }
    cout<<n<<' ';
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<' ';
    }
    return 0;
}