// https://www.luogu.com.cn/problem/P14802
// 输入：第一行一个正整数 T，表示数据组数。
// 输入：每组数据第一行一个正整数 n，表示点的数量。
// 输入：接下来 n 行，每行两个整数 x_i, y_i，表示各点坐标。
// 输入：保证同组内所有点互不相同，且不存在三点共线。
// 题意：从给定的 n 个点中选择一部分点（可以全选），
// 按任意顺序依次连成闭合简单多边形（除共用端点外边不相交）。
// 题意：要求连成的多边形面积严格大于 0，且必须是凹多边形（即非凸多边形）。
// 题意：求出能形成的凹多边形的最大面积。
// 输出：每组数据输出一行。
// 输出：若无法形成面积严格大于 0 的凹多边形，输出 -1。
// 输出：否则输出一个正整数，表示最大凹多边形面积的两倍。
// 数据范围：1 <= T <= 10^4
// 数据范围：3 <= n <= 10^5
// 数据范围：-10^9 <= x_i, y_i <= 10^9
// 数据范围：所有测试数据组的 n 之和不超过 2 * 10^5
// 难度评分：2400（洛谷分级换算）
// 算法标签：凸包、旋转卡壳、计算几何
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int INF = 4e18;

int n;
bool vis[MAXN];

struct Point{
    int x,y,id;
};
Point p[MAXN];
Point hull1[MAXN];
int cnt1=0;
Point hull2[MAXN<<1];
int cnt2=0;

bool cmp(Point a,Point b){
    if(a.x!=b.x){
        return a.x<b.x;
    }
    return a.y<b.y;
}

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

int cross(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

void Andrew(Point *hull,int &cnt,int all){
    if(all<=2){
        for(int i=1;i<=n;i++){
            if(!vis[p[i].id]){
                hull[++cnt]=p[i];
            }
        }
        if(cnt>0){
            hull[cnt+1]=hull[1];
        }
        return ;
    }
    for(int i=1;i<=n;i++){
        if(vis[p[i].id]){
            continue;
        }
        while(cnt>1&&cross(hull[cnt]-hull[cnt-1],p[i]-hull[cnt-1])<=0){
            cnt--;
        }
        hull[++cnt]=p[i];
    }
    int t=cnt;
    for(int i=n-1;i>=1;i--){
        if(vis[p[i].id]){
            continue;
        }
        while(cnt>t && cross(hull[cnt]-hull[cnt-1],p[i]-hull[cnt-1])<=0){
            cnt--;
        }
        hull[++cnt]=p[i];
    }
    cnt--;
    hull[cnt+1]=hull[1];
    for(int i=1;i<=cnt;i++){
        vis[hull[i].id]=true;
    }
}

void solve(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>p[i].x>>p[i].y;
        p[i].id=i;
        vis[i]=false;
    }
    sort(p+1,p+n+1,cmp);

    cnt1=cnt2=0;
    Andrew(hull1,cnt1,n);
    if(cnt1==n){
        cout<<-1<<endl;
        return ;
    }
    Andrew(hull2,cnt2,n-cnt1);
    for(int i=1;i<=cnt2;i++){
        hull2[i+cnt2]=hull2[i];
    }

    int ans=INF;
    int pos=1;
    for(int i=1;i<=cnt2;i++){
        int v=cross(hull1[2]-hull1[1],hull2[i]-hull1[1]);
        if(v<ans){
            ans=v;
            pos=i;
        }
    }

    for(int i=2;i<=cnt1;i++){
        while(pos+1<=2*cnt2&& cross(hull1[i+1]-hull1[i],hull2[pos]-hull1[i])>=cross(hull1[i+1]-hull1[i],hull2[pos+1]-hull1[i])){
            pos++;
        }
        ans=min(ans,cross(hull1[i+1]-hull1[i],hull2[pos]-hull1[i]));
    }

    ans=-ans;
    for(int i=2;i<cnt1;i++){
        ans+=cross(hull1[i]-hull1[1],hull1[i+1]-hull1[1]);
    }
    cout<<ans<<endl;
}

signed main()
{
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
