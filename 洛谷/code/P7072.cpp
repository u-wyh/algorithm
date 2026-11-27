// https://www.luogu.com.cn/problem/P7072
// 题意：逐一评出 n 个选手的成绩（0~600 的整数），若已评出 p 人，计划获奖人数为 max(1, floor(p * w%))（同分并列均可获奖）；
// 每次评出后输出即时获奖分数线。
// 数据范围：1 <= n <= 10^5，1 <= w <= 99，每名选手成绩为不超过 600 的非负整数。
// 算法标签：桶计数、模拟
#include<bits/stdc++.h>
using namespace std;

int t[610],n,w;

int main()
{
    int tmp;
    cin>>n>>w;
    for(int i=1;i<=n;i++){
        cin>>tmp;
        t[tmp]++;
        int sum=0;
        for(int j=600;j>=0;j--){
            sum+=t[j];
            if(sum>=max(1,i*w/100)){
                cout<<j<<' ';
                break;
            }
        }
    }
    return 0;
}
