// https://www.luogu.com.cn/problem/P1783
// 题意：在横坐标 0 到 N 的带状区域内给出 M 个信号塔，每座塔覆盖相同半径的圆。求能封住所有从海滩通往内地的连续路径的最小半径，保留两位小数。
// 数据范围：1 ≤ N ≤ 1000，1 ≤ M ≤ 800，0 ≤ X_i ≤ N，0 ≤ Y_i ≤ 10^5。

#include<bits/stdc++.h>
using namespace std;
const int MAXM = 805;
const double sml = 1e-5;

int n,m;
double dis[MAXM][MAXM];
bool vis[MAXM];

struct node{
    int x,y;
}nums[MAXM];

bool cmp(node a,node b){
    return a.x<b.x;
}

bool dfs(int u,double x){
    //cout<<u<<endl;
    if(nums[u].x==nums[m].x){
        return true;
    }
    for(int i=1;i<=m;i++){
        if(vis[i]||dis[u][i]>2*x){
            continue;
        }
        vis[i]=true;
        if(dfs(i,x)){
            return true;
        }
    }
    return false;
}

bool check(double x){
    //cout<<x<<endl;
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=m;i++){
        if(nums[i].x==nums[1].x){
            if(vis[i]){
                continue;
            }
            vis[i]=true;
            if(dfs(i,x)){
                return true;
            }
        }
        else{
            break;
        }
    }
    return false;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>nums[i].x>>nums[i].y;
    }
    sort(nums+1,nums+m+1,cmp);
    for(int i=1;i<=m;i++){
        for(int j=i+1;j<=m;j++){
            dis[i][j]=sqrt(pow(nums[i].x-nums[j].x,2)+pow(nums[i].y-nums[j].y,2));
            dis[j][i]=dis[i][j];
        }
    }
//    for(int i=1;i<=m;i++){
//        for(int j=1;j<=m;j++){
//            cout<<dis[i][j]<<' ';
//        }
//        cout<<endl;
//    }
    double l=1.0*max(nums[1].x,n-nums[m].x);
    double r=1.0*n;
    double ans=n;
    while(r-l>sml){
//        cout<<l<<' '<<r<<' '<<(r-l)<<endl;
//        system("pause");
        double mid=(l+r)/2;
        if(check(mid)){
            ans=mid;
            r=mid-sml;
        }
        else{
            l=mid+sml;
        }
    }
    cout << fixed << setprecision(2) << ans << endl;
    return 0;
}
