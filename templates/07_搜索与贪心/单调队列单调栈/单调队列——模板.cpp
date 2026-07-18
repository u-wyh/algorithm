// 滑动窗口最大值（单调队列经典用法模版）
// 给你一个整数数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧
// 你只可以看到在滑动窗口内的 k 个数字。滑动窗口每次只向右移动一位。
// 返回 滑动窗口中的最大值 。
// 测试链接 : https://leetcode.cn/problems/sliding-window-maximum/
//这里也可以先建立一个k-1的滑动窗口  然后在加入第k个数字  判断并输出最大值
//注意这里的弹出压入操作都是根据h t的变化来进行的   事实上被“弹出”的数字依旧在序列中   只是不会被访问了
#include<bits/stdc++.h>
using namespace std;

int n,k;
int a[100000],q[100000];

int main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    int h=0,t=0;
    for(int i=1;i<=n;i++){
        while(h<t&&q[h]+k<=i){
            h++;
        }
        while(h<t&&a[q[t-1]]<a[i]){
            t--;
        }//h<t  保证了如果队列已经是空的  那么不在t--
        q[t]=i;
        t++;
        if(i>=k)
            cout<<a[q[h]]<<endl;
    }
    return 0;
}