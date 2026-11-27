// https://www.luogu.com.cn/problem/P7181
// 题意：在 [0, xmax] x [0, ymax] 内
// 给定 n 个边平行于坐标轴的矩形，A=(0,0)
// 在折线 CE 与 DE 上选一点
// B（其中 C(xmax,0), D(0,ymax), E(xmax,ymax)）
// 使线段 AB 相交（含顶点相交）的矩形数最多，输出最多数及 B 坐标。
// 数据范围：1 <= n <= 10^4，
// 0 <= xmax, ymax <= 10^9，矩形顶点为非负整数坐标。
// 算法标签：扫描线、排序
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e4+5;

int n,xmax,ymax;

struct Rect{
    int x1,y1,x2,y2;
};
Rect rect[MAXN];

struct Event{
    int x;
    int op;
};
Event event[MAXN*2];
int cnt;

bool cmp(Event a,Event b){
    return a.x<b.x;
}

int best=0;
int bestx,besty;

void compute2(){
    cnt=0;
    for(int i=1;i<=n;i++){
        if(rect[i].x1){
            event[++cnt]={(xmax*rect[i].y2)/rect[i].x1+1,-1};
        }
        if(rect[i].x2){
            event[++cnt]={(xmax*rect[i].y1+rect[i].x2-1)/rect[i].x2,1};
        }
    }
    sort(event+1,event+cnt+1,cmp);
    int now=0;
    for(int i=1;i<=cnt;i++){
        if(event[i].x>ymax){
            break;
        }
        if(i!=cnt && event[i].x==event[i+1].x){
            now+=event[i].op;
            continue;
        }
        now+=event[i].op;
        if(now>best){
            best=now;
            bestx=xmax;
            besty=event[i].x;
        }
    }
}

void compute1(){
    cnt=0;
    for(int i=1;i<=n;i++){
        if(rect[i].y2){
            event[++cnt]={(ymax*rect[i].x1+rect[i].y2-1)/rect[i].y2,1};
        }
        if(rect[i].y1){
            event[++cnt]={(ymax*rect[i].x2)/rect[i].y1+1,-1};
        }
    }
    sort(event+1,event+cnt+1,cmp);
    int now=0;
    for(int i=1;i<=cnt;i++){
        if(event[i].x>xmax){
            break;
        }
        if(i!=cnt && event[i].x==event[i+1].x){
            now+=event[i].op;
            continue;
        }
        now+=event[i].op;
        if(now>best){
            best=now;
            bestx=event[i].x;
            besty=ymax;
        }
    }
}

signed main()
{
    cin>>xmax>>ymax>>n;
    for(int i=1;i<=n;i++){
        int x1,y1,x2,y2;
        cin>>x1>>y1>>x2>>y2;
        rect[i]={x1,y1,x2,y2};
    }
    bestx=xmax,besty=ymax;
    compute1();
    compute2();
    cout<<best<<' '<<bestx<<' '<<besty<<endl;
    return 0;
}