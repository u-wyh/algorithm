// https://www.luogu.com.cn/problem/P1899
// 题意：有 N 件物品（分普通与魔法两类），已知 1 个鉴定卷轴价格 P_i，
// 初始钱为 0。
// 普通物品售价 P；
// 魔法物品鉴定前售价 P_1，花 P_i 买卷轴鉴定后售价 P_2。
// 随时可卖任意物品换钱，有钱即可买卷轴，最终需卖出所有物品。
// 输出最多能获得多少钱。
// 数据范围：
// 1 <= N <= 1000（物品数）
// 1 <= P_i <= 5000（卷轴价格）
// 1 <= P <= 10000（普通物品价值）
// 1 <= P_1 < P_2 <= 10000（魔法物品鉴定前后价值）
// 难度评分：1800（洛谷分级换算）
// 算法标签：0-1背包、动态规划、贪心
#include<bits/stdc++.h>
using namespace std;
const int INF = 2e9;
const int MAXP = 5005;
const int MAXN = 1005;

int n,p,m=1;//m表示的是有效魔法物品的个数
int a[MAXN],b[MAXN];
int f[MAXP];//表示为了凑够i的钱  最少要浪费多少本来该有的利润
int v;//表示目前的利润
int sv;//sv纯粹是为了特判  表示根本买不起一个图鉴的情况

signed main()
{
    cin>>n>>p;
    for(int i=1;i<=n;i++){
        int x,y;
        cin>>x;
        if(getchar()==' '){
            cin>>y;
            if(x>=y-p){
                //表示的是无效的魔法物品
                v+=x;
            }
            else{
                a[m]=x,b[m++]=y;
            }
        }
        else
            v+=x;
    }
    for(int i=v+1;i<=p;i++){
        f[i]=INF;
    }
    sv=v;
    for(int i=1;i<=m;i++){
        v+=b[i]-p,sv+=a[i];
    }
    //此时的v是最大的利润
    for(int i=1;i<=m;i++){
        for(int j=p;j>=a[i];j--){
            f[j]=min(f[j],f[j-a[i]]+b[i]-p-a[i]);
            //表示一个魔法物品直接卖了 造成的利润损失
        }
    }
    cout<<(sv<=p?sv:v-f[p])<<endl;
    return 0;
}
