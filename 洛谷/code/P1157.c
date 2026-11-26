// https://www.luogu.com.cn/problem/P1157
// 题意：从自然数 1..n 中任取 r 个数，按要求输出所有组合。
// 输入：一行输入两个自然数 n 和 r。
// 输出：每行输出一个组合，组合内元素升序，所有组合按字典序排列。
// 输出：每个数字占 3 个字符场宽输出。
// 数据范围：1 < n < 21。
// 数据范围：0 <= r <= n。
#include<stdio.h>

int a[30];

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    for(int s=(1<<n)-1;s>=0;s--){
        int cnt=0;
        for(int i=0;i<n;i++){
            if(s&(1<<i))
                a[cnt++]=i;
        }
        if(cnt==m){
            for(int i=m-1;i>=0;i--){
                printf("%3d",n-a[i]);
            }
            printf("\n");
        }
    }
    return 0;
}
