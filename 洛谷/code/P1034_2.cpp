// https://www.luogu.com.cn/problem/P1034
// 题意：给平面上 n 个点，使用 k 个边平行于坐标轴的矩形覆盖全部点。矩形不能相交或接触，退化到点或线段时面积按 0 算。求矩形面积和最小值。
// 数据范围：1 ≤ n ≤ 50，1 ≤ k ≤ 4，0 ≤ x[i],y[i] ≤ 500。

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 55;
const int INF = 1e9;

int n,k;
struct Point{
    int x,y;
};
Point p[MAXN];

struct Rect{
    int minx,maxx,miny,maxy;
};
Rect rec[5];

int ans=INF;

int area(Rect a){
    return (a.maxx-a.minx)*(a.maxy-a.miny);
}

bool check(Rect a,Rect b){
    if(a.maxx<b.minx || b.maxx<a.minx){
        return true;
    }
    if(a.maxy<b.miny || b.maxy<a.miny){
        return true;
    }
    return false;
}

void addPoint(int i,int u,int used){
    if(i>used){
        rec[i]={p[u].x,p[u].x,p[u].y,p[u].y};
        return ;
    }
    rec[i].minx=min(rec[i].minx,p[u].x);
    rec[i].maxx=max(rec[i].maxx,p[u].x);
    rec[i].miny=min(rec[i].miny,p[u].y);
    rec[i].maxy=max(rec[i].maxy,p[u].y);
}

void dfs(int u,int used,int sum){
    if(sum>=ans){
        return ;
    }
    if(u>n){
        ans=min(ans,sum);
        return ;
    }

    for(int i=1;i<=k;i++){
        Rect old=rec[i];
        int before=(i<=used?area(rec[i]):0);

        addPoint(i,u,used);

        bool flag=true;
        for(int j=1;j<=used;j++){
            if(i==j){
                continue;
            }
            if(!check(rec[i],rec[j])){
                flag=false;
                break;
            }
        }

        if(flag){
            int now=sum-before+area(rec[i]);
            dfs(u+1,max(used,i),now);
        }

        rec[i]=old;
    }
}

int main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>p[i].x>>p[i].y;
    }

    dfs(1,0,0);

    cout<<ans<<endl;
    return 0;
}