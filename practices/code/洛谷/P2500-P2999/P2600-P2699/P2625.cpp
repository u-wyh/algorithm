// https://www.luogu.com.cn/problem/P2625
// 题意：给定 n 条移动
// 或转向指令（right/left/forward/backward X）。
// 重排指令顺序，使最终位置到起点的欧几里得距离最大。
// 输出最大距离，四舍五入保留 6 位小数。
// 数据范围：1 <= n <= 50，角度 in [1, 719]，
// 距离 in [1, 1000]。
// 算法标签：背包动态规划、计算几何
#include<bits/stdc++.h>
using namespace std;
const double pi = 3.1415926535;

int n,m;
int x,y;
int cir[55];
bool f[55][365];

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        string s;
        int val;
        cin>>s>>val;
        if(s=="forward"){
            x+=val;
        }
        else if(s=="backward"){
            y+=val;
        }
        else if(s=="left"){
            cir[++m]=-val;
        }
        else{
            cir[++m]=val;
        }
    }
    f[0][0]=1;
    for(int i=1;i<=m;i++){
        for(int j=0;j<360;j++){
            if(f[i-1][j]){
                f[i][j]=1,f[i][(j+cir[i]+3600)%360]=1;
            }
        }
    }
    int ans=360;
    for(int i=0;i<360;i++){
        if(f[m][i]){
            ans=min(ans,abs(i-180));
        }
    }
    double s=sqrt(x*x+y*y+2*x*y*cos(ans*pi/180));
    printf("%.6lf",s);
    return 0;
}
