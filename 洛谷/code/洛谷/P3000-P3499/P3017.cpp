// https://www.luogu.com.cn/problem/P3017
// 题意：输入网格行数 R、列数 C、横分块数 A、竖分块数 B，
// 以及每格的巧克力豆数 N_{ij}。
// 先沿水平整数线切 A-1 刀将矩形分成 A 条水平带，
// 再对每条水平带独立沿垂直整数线切 B-1 刀，最终共得 A*B 块；
// 其他牛拿走豆最多的 A*B-1 块，留下豆最少的一块给 Bessie。
// 合理选择切法，使 Bessie 最终能分到的最少那块的巧克力豆数尽可能大。
// 输出一行一个整数，表示 Bessie 能保证获得的最多巧克力豆数。
// 数据范围：对于 100% 的数据，1 <= R, C <= 500，
// 0 <= N_{ij} <= 4000，1 <= A <= R
// 1 <= B <= C。
// 算法标签：二分答案、二维前缀和、贪心
#include<bits/stdc++.h>
using namespace std;
const int N = 505;

int r,c,A,B;
int a[N][N],s[N][N];

int fun(int X1,int Y1,int X2,int Y2){
    return s[X2][Y2]+s[X1-1][Y1-1]-s[X2][Y1-1]-s[X1-1][Y2];
}

bool check(int m){
    int col=1,row=1;
    int cnta=0;
    for(int i=1;i<=r;i++){
        int cntb=0;
        col=1;
        for(int j=1;j<=c;j++){
            if(fun(row,col,i,j)>=m){
                col=j+1;
                cntb++;
            }
        }
        if(cntb>=B){
            row=i+1;
            cnta++;
        }
    }
    return cnta>=A;
}

int main()
{
    cin>>r>>c>>A>>B;
    int L=0,R=0,mid,ans=0;
    for(int i=1;i<=r;i++){
        for(int j=1;j<=c;j++){
            cin>>a[i][j];
            s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+a[i][j];
        }
    }
    R=s[r][c];
    while(L<=R){
        mid=L+((R-L)/2);
        if(check(mid)){
            ans=mid;
            L=mid+1;
        }else{
            R=mid-1;
        }
    }
    cout<<ans;
    return 0;
}
