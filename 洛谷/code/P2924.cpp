// https://www.luogu.com.cn/problem/P2924
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 255;

int n;
struct Point{
    int x,y;
};
Point p[MAXN];

int cross(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

int cross(Point a, Point b, Point c){
    return (b.x-a.x)*(c.y-a.y) - (b.y-a.y)*(c.x-a.x);
}

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

bool cmp1(Point a,Point b){
    if(a.x!=b.x){
        return a.x<b.x;
    }
    return a.y<b.y;
}

int now;
bool cmp(int a,int b){
    int cr=cross(p[a]-p[now],p[b]-p[now]);
    return cr>0;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>p[i].x>>p[i].y;
    }
    sort(p+1,p+n+1,cmp1);
    int ans = 3;
    int ord[MAXN];
    int dp[MAXN][MAXN];

    // 枚举最左点 s
    for(int s=1; s<=n-2; s++){
        int m = 0;
        for(int j=s+1; j<=n; j++) ord[++m] = j;

        now=s;
        // 相对 s 按极角升序（逆时针）
        sort(ord+1, ord+m+1, cmp);

        memset(dp, 0, sizeof(dp));

        for(int i=1; i<=m; i++){
            for(int j=i+1; j<=m; j++){
                dp[i][j] = 3;   // 链 s -> ord[i] -> ord[j]
                for(int k=1; k<i; k++){
                    // 在 ord[i] 处左转
                    if(cross(p[ord[k]], p[ord[i]], p[ord[j]]) > 0){
                        dp[i][j] = max(dp[i][j], dp[k][i] + 1);
                    }
                }
                // 在 ord[j] 处左转，能连回 s
                if(cross(p[ord[i]], p[ord[j]], p[s]) > 0){
                    ans = max(ans, dp[i][j]);
                }
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}