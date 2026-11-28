// https://www.luogu.com.cn/problem/P2671
// 题意：n 个格子各有数字 number_i 和颜色 color_i。
// 求所有满足 x < y < z、y-x = z-y
// 且 color_x = color_z 的三元组
// (x+z)*(number_x+number_z)
// 之和。
// 输出总和对 10007 取模的结果。
// 数据范围：1 <= n, m <= 10^5，
// 1 <= color_i <= m，1 <= number_i <= 10^5。
// 难度评分：1300（洛谷分级换算）
// 算法标签：排序分组、奇偶分类
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MOD = 10007;

struct node{
    int pos,num,col;
}nums[MAXN];
int n,m;

bool cmp(node a,node b){
    return a.col<b.col;
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>nums[i].num;
        nums[i].pos=i;
    }
    for(int i=1;i<=n;i++){
        cin>>nums[i].col;
    }
    sort(nums+1,nums+n+1,cmp);
    int l=1,r=1;
    int ans=0;
    int sum1=0,sum2=0;

    while(r<=n){
        if(nums[l].pos%2){
            sum1+=nums[l].pos;
        }
        else{
            sum2+=nums[l].pos;
        }
        r++;
        //cout<<sum1<<' '<<sum2<<' ';
        while(nums[r].col==nums[l].col&&r<=n){
            if(nums[r].pos%2){
                sum1+=nums[r].pos;
            }
            else{
                sum2+=nums[r].pos;
            }
            r++;
        }
        //cout<<sum1<<' '<<sum2<<' ';
        for(int i=l;i<r;i++){
            if(nums[i].pos%2){
                sum1-=nums[i].pos;
                ans+=sum1*nums[i].pos;
            }
            else{
                sum2-=nums[i].pos;
                ans+=sum2*nums[i].pos;
            }
        }
        //cout<<sum1<<' '<<sum2<<endl;
        l=r;
    }
    for(int i=l;i<r;i++){
        if(nums[i].pos%2){
            sum1-=nums[i].pos;
            ans+=sum1*nums[i].pos;
        }
        else{
            sum2-=nums[i].pos;
            ans+=sum2*nums[i].pos;
        }
    }
    cout<<ans<<endl;
    return 0;
}
