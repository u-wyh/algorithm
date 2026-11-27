// https://www.luogu.com.cn/problem/P2921
// 题意：输入隔间数 N，以及每个隔间 i 指向的下一个隔间编号 next_i。
// 第 i 头牛从 i 号隔间出发，
// 不断沿着当前隔间的 next 指针走到下一个隔间，
// 直到即将回到自己已经访问过的隔间时停止。
// 计算每头牛在停止前访问过的隔间总数（包含起点）。
// 输出共 N 行，第 i 行一个整数表示第 i 头牛要前往的隔间数。
// 数据范围：对于 100% 的数据，1 <= N <= 10^5，
// 1 <= next_i <= N。
// 算法标签：基环树、记忆化搜索
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n;
int nxt[MAXN];
int color[MAXN];
int sucdfn[MAXN];
int dfn[MAXN];
int minc[MAXN];

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nxt[i];
    }
    for(int i=1;i<=n;i++){
        for(int j=i,cnt=0;;cnt++,j=nxt[j]){
            if(!color[j]){
                color[j]=i;
                dfn[j]=cnt;
            }
            else if(color[j]==i){
                minc[i]=cnt-dfn[j];
                sucdfn[i]=dfn[j];
                cout<<cnt<<endl;
                break;
            }
            else{
                minc[i]=minc[color[j]];
                sucdfn[i]=cnt+max(0,sucdfn[color[j]]-dfn[j]);
                cout<<minc[i]+sucdfn[i] <<endl;
                break;
            }
        }
    }
    return 0;
}
