// https://www.luogu.com.cn/problem/P3156
// 题意：输入同学总数 n、询问次数 m，按进入顺序给出的 n 个学号，
// 以及 m 个位置编号 i。
// 每次询问第 i 个进入教室的同学的学号是多少（下标从 1 开始）。
// 依次输出 m 个整数表示每次询问的学号，用换行隔开。
// 数据范围：1 <= n <= 2*10^6，1 <= m <= 10^5，
// 学号在 [1, 10^9] 之间。
// 算法标签：模拟
#include<iostream>
#include<vector>

using namespace std;

int n,m,tmp;

int main()
{
    vector<int>stu(11,0);
    scanf("%d %d",&n,&m);
    for(int i=0;i<n;i++){
        scanf("%d",&tmp);
        stu.push_back(tmp);
    }
    stu[0]=2;
    for(int i=0;i<m;i++){
        cin>>tmp;
        printf("%d\n",stu[tmp-1]);
    }
    cout<<stu.size()<<"\n";
    return 0;
}
