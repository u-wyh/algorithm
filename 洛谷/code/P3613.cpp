// https://www.luogu.com.cn/problem/P3613
// 题意：输入寄包柜数量 n 和操作次数 q，柜子编号 1..n，每个柜子有未知个格子（编号从 1 开始）。
// 操作 1 i j k 表示将第 i 个柜子第 j 格存入物品 k（k=0 表示清空）；操作 2 i j 表示查询第 i 个柜子第 j 格当前物品编号。
// 对每次查询输出对应物品编号并换行。
// 数据范围：1 <= n, q <= 10^5，0 <= a_i <= 10^5，全超市寄包格子总数不超过 10^7，0 <= k <= 10^9。
#include<iostream>
#include<vector>
// 算法标签：模拟、动态数组

using namespace std;

int n,q,opt,i,j,k;

int main()
{
    cin>>n>>q;
    vector<vector<int>>locker(n+1);
    while(q--){
        cin>>opt;
        if(opt==1){
            cin>>i>>j>>k;
            if(locker[i].size()<j+1)
                locker[i].resize(j+1);
            locker[i][j]=k;
        }else{
            cin>>i>>j;
            cout<<locker[i][j]<<endl;
        }
    }
    return 0;
}
