// https://www.luogu.com.cn/problem/P3902
// 题意：给定长度为 n 的整数序列 A_1..A_n，每次修改可以将序列中某个数改成任意实数。
// 求最少修改多少个数字，使得整个序列严格单调递增。
// 数据范围：1 <= n <= 10^5，1 <= A_i <= 10^9。
#include<bits/stdc++.h>
// 算法标签：最长上升子序列、二分查找
using namespace std;

int main()
{
    int n,ans=1;
    scanf("%d",&n);
    int a[n],sa[n];
    for(int i=0;i<n;i++)
        scanf("%d",&a[i]);
    sa[ans]=a[0];
    for(int tz,i=1;i<n;i++){
        if(sa[ans]<a[i]){
            ans++;
            sa[ans]=a[i];
        }else{
            tz=lower_bound(sa,sa+ans,a[i])-sa;
            //这里用tz临时存储找到的下标
            sa[tz]=a[i];
        }
    }
    printf("%d",n-ans);
    return 0;
}
