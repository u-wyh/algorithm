// https://www.luogu.com.cn/problem/P1706
// 题意：给定 n，按字典序输出 1 到 n 的全部排列，每行一个排列，
// 每个数占 5 个字符宽。
// 数据范围：1 ≤ n ≤ 9。
// 算法标签：全排列、枚举

#include<cstdio>
#include<iostream>
#include<algorithm>

using namespace std;

int a[10],n;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        a[i]=i;
    }
    do{
        for(int i=1;i<=n;i++)
            printf("%5d",a[i]);
        puts("");
    }while(next_permutation(a+1,a+n+1));
    return 0;
}
