// https://www.luogu.com.cn/problem/P7865
// 题意：在 n * m 的矩形区域内给出 s 个覆盖矩形（左下角 (a1, b1)，右上角 (a2, b2)）
// 求这 s 个矩形的并是否完全覆盖后续给出的 L 个查询矩形（左下角 (r1, c1)，右上角 (r2, c2)）。
// 输入 n, m，然后 s 及 s 行覆盖矩形，再 L 及 L 行查询矩形。
// 输出 L 行，完全在并集内输出 Yes，否则输出 No。
// 数据范围：1 <= n, m <= 3*10^3，1 <= s, L <= 10^6，1 <= a1 < a2 <= n
// 1 <= b1 < b2 <= m，1 <= r1 < r2 <= n
// 1 <= c1 < c2 <= m（题面数据范围中写作 x1 < x2, y1 < y2）。
// 算法标签：二维差分、二维前缀和
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3005;

int n,m,s,t;
int nums[MAXN][MAXN];

int fun(int X1,int Y1,int X2,int Y2){
    return nums[X2][Y2]+nums[X1-1][Y1-1]-nums[X2][Y1-1]-nums[X1-1][Y2];
}

int main()
{
    cin>>n>>m>>s;
    for(int i=1,a,b,c,d;i<=s;i++){
        cin>>a>>b>>c>>d;
        nums[a][b]+=1;
        nums[a][d+1]-=1;
        nums[c+1][b]-=1;
        nums[c+1][d+1]+=1;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            nums[i][j]+=nums[i-1][j]+nums[i][j-1]-nums[i-1][j-1];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(nums[i][j]>=1)
                nums[i][j]=1;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            nums[i][j]+=nums[i-1][j]+nums[i][j-1]-nums[i-1][j-1];
        }
    }
    cin>>t;
    for(int i=1,a,b,c,d;i<=t;i++){
        cin>>a>>b>>c>>d;
        if(fun(a,b,c,d)==((c-a+1)*(d-b+1)))
            cout<<"Yes\n";
        else
            cout<<"No\n";
    }
    return 0;
}
