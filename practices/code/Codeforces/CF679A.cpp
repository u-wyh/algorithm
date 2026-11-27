// https://codeforces.com/problemset/problem/679/A
// 题意：交互题，系统心里想一个 [2, 100] 内的整数 x。
// 规则：至多询问 20 次，每次问一个 q 是否整除 x。
// 系统回答 yes 或 no，据此判断 x 是质数还是合数。
// 输出：交互结束后输出 prime 或 composite。
// 数据范围：2 <= x, q <= 100，最多 20 次询问。
// 算法标签：质数枚举、整除判定
#include<bits/stdc++.h>
using namespace std;

int prime[]={2,  3,  4,  5,  7,  9,  11, 13, 17, 19, 23, 25, 29, 31, 37, 41, 43, 47, 49};
char s[4];

int main()
{
    int cnt=0;
    for(int i:prime){
        printf("%d\n",i);
        fflush(stdout);
        scanf("%s",s);
        if(s[0]=='y'){
            cnt++;
            if(cnt==2){
                printf("composite");
                return 0;
            }
        }
    }
    printf("prime");
    return 0;
}