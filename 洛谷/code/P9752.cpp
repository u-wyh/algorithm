// https://www.luogu.com.cn/problem/P9752
// 题意：密码锁有 5 个 0~9 循环拨圈。
// 从正确密码出发，随机转动仅一次（以任意非零幅度单独转动 1 个拨圈，或以相同幅度同时转动 2 个相邻拨圈），得到锁车状态。
// 给定 n 个互不为正确密码的锁车状态，求有多少种可能的正确密码能各自通过一次上述操作得到全部 n 个状态。
// 题意：第一行输入 n，接下来 n 行每行 5 个 0~9 的整数；输出一行一个整数。
// 数据范围：1 <= n <= 8。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100000;

int n;
int nums[10][6];
int tmp[6];
int vis[MAXN];

int fun(int *nums){
    int ans=0;
    for(int i=1;i<=5;i++){
        ans=ans*10+nums[i];
    }
    return ans;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=5;j++){
            cin>>nums[i][j];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=9;j++){
            //转动幅度
            for(int p=1;p<=5;p++){
                //转动位置
                for(int k=1;k<=5;k++){
                    tmp[k]=nums[i][k];
                }
                tmp[p]=(tmp[p]+j)%10;
                vis[fun(tmp)]++;
            }
            for(int p=1;p<=4;p++){
                for(int k=1;k<=5;k++){
                    tmp[k]=nums[i][k];
                }
                tmp[p]=(tmp[p]+j)%10;
                tmp[p+1]=(tmp[p+1]+j)%10;
                vis[fun(tmp)]++;
            }
        }
    }
    int cnt=0;
    for(int i=0;i<=99999;i++){
        if(vis[i]==n){
            cnt++;
        }
    }
    cout<<cnt<<endl;
    return 0;
}