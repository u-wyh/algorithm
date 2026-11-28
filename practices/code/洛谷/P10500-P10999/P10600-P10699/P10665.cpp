// https://www.luogu.com.cn/problem/P10665
// 题意：开始是一张 n×n 的完整网格图。
// 每次删除一条边，再问这条边的两个端点是否仍然连通，输出 TAK 或 NIE。
// 首问或上一答为 TAK 时用第一套删边参数，否则用第二套。
// N 表示 b 方向加一，E 表示 a 方向加一。
// 数据范围：2 ≤ n ≤ 1500，1 ≤ k ≤ 2n(n-1)，
// 1 ≤ a,b ≤ n，每条边最多删一次。
// 难度评分：2300（洛谷分级换算）
// 算法标签：并查集、平面对偶

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1505;
const int MAXM = MAXN*MAXN;

int n,m;
int fa[MAXM];

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

int main()
{
    scanf("%d %d",&n,&m);
    int all=(n-1)*(n-1)+1;
    for(int i=1;i<=all;i++){
        fa[i]=i;
    }
    bool ans=true;;
    for(int i=1;i<=m;i++){
        int x,y,x1,y1,x2,y2;
        char op,op1,op2;
        scanf("%d %d %c",&x1,&y1,&op1);
        scanf("%d %d %c",&x2,&y2,&op2);
        if(ans){
            x=x1;
            y=y1;
            op=op1;
        }
        else{
            x=x2;
            y=y2;
            op=op2;
        }

        int face1,face2;
        if(op=='E'){
            if(y!=1){
                face1=(x-1)*(n-1)+y-1;
            }
            else{
                face1=all;
            }

            if(y!=n){
                face2=(x-1)*(n-1)+y;
            }
            else{
                face2=all;
            }
        }
        else{
            if(x!=1){
                face1=(x-2)*(n-1)+y;
            }
            else{
                face1=all;
            }

            if(x!=n){
                face2=(x-1)*(n-1)+y;
            }
            else{
                face2=all;
            }
        }

        int fx=find(face1);
        int fy=find(face2);
        if(fx!=fy){
            ans=true;
            fa[fx]=fy;
        }
        else{
            ans=false;
        }

        if(ans){
            cout<<"TAK"<<endl;
        }
        else{
            cout<<"NIE"<<endl;
        }
    }
    return 0;
}