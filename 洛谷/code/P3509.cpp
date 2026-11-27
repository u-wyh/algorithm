// https://www.luogu.com.cn/problem/P3509
// 题意：输入石头数量 n、参数 k、跳跃次数 m，以及每块石头距源头的严格递增位置 p_1 < p_2 < ... < p_n。
// 青蛙每次跳向距离当前石头第 k 近的石头（若并列第 k 近则跳往更靠近源头即坐标更小的那块）。
// 输出一行 n 个整数，表示青蛙从第 1..n 块石头出发跳跃 m 次后各自停留的石头编号。
// 数据范围：1 <= k < n <= 10^6，1 <= m <= 10^18，1 <= p_1 < ... < p_n <= 10^18。
#include<bits/stdc++.h>
// 算法标签：倍增、双指针
using namespace std;
#define int long long
const int MAXN = 1e6+5;
const int LIMIT = 65;

int n,k,m;
int st[MAXN][LIMIT];
int pos[MAXN];
int power;

signed main()
{
    cin>>n>>k>>m;
    for(int i=1;i<=n;i++){
        cin>>pos[i];
    }
    power=log2(m);
    int head = 1, tail = k + 1;
    for(int i = 1; i <= n; i++) {
        while(tail + 1 <= n && pos[tail + 1] - pos[i] < pos[i] - pos[head])
            head++, tail++;
        if(pos[tail] - pos[i] > pos[i] - pos[head])
            st[i][0] = tail;
        else
            st[i][0] = head;
    }
    for(int i=1;i<=power;i++){
        for(int j=1;j<=n;j++){
            st[j][i]=st[st[j][i-1]][i-1];
        }
    }
    for(int i=1;i<=n;i++){
        int temp=m,ans=i;
        for(int j=power;j>=0;j--){
            if(temp<(1<<j)){
                continue;
            }
            temp-=(1<<j);
            ans=st[ans][j];
            if(temp==0){
                break;
            }
        }
        cout<<ans<<' ';
    }
    return 0;
}
