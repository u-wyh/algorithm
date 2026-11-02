// https://www.luogu.com.cn/problem/P1153
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 15;

struct Point{
    int x,y;
};

int n,ans;
Point p[MAXN];
int ord[MAXN];
bool vis[MAXN];

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

long long operator*(Point a,Point b){
    return 1LL*a.x*b.y-1LL*a.y*b.x;
}

long long cross(Point a,Point b,Point c){
    return (b-a)*(c-a);
}

// 判断两条没有公共端点的线段是否相交
bool check(Point a,Point b,Point c,Point d){
    long long x1=cross(a,b,c);
    long long x2=cross(a,b,d);
    long long x3=cross(c,d,a);
    long long x4=cross(c,d,b);

    // 题目保证任意三点不共线
    return ((x1>0)!=(x2>0)) && ((x3>0)!=(x4>0));
}

// 判断当前排列是否构成简单多边形
bool judge(){
    ord[n+1]=ord[1];

    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            // 相邻边允许共享端点
            if(j==i+1 || (i==1 && j==n)){
                continue;
            }

            Point a=p[ord[i]];
            Point b=p[ord[i+1]];
            Point c=p[ord[j]];
            Point d=p[ord[j+1]];

            if(check(a,b,c,d)){
                return false;
            }
        }
    }

    return true;
}

// 枚举剩余点的排列
void dfs(int pos){
    if(pos==n+1){
        if(judge()){
            ans++;
        }
        return;
    }

    for(int i=2;i<=n;i++){
        if(!vis[i]){
            vis[i]=true;
            ord[pos]=i;

            dfs(pos+1);

            vis[i]=false;
        }
    }
}

int main(){
    // 最后一个 (0,0) 也属于点集
    while(cin>>p[n+1].x>>p[n+1].y){
        n++;
        if(p[n].x==0 && p[n].y==0){
            break;
        }
    }

    ord[1]=1;
    vis[1]=true;

    dfs(2);

    // 正向和反向重复计算
    cout<<ans/2<<endl;

    return 0;
}