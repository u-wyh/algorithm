// https://www.luogu.com.cn/problem/P3460
// 题意：输入符号种数 n，以及一个自底向上长度为 2n 的栈，
// 每种符号 1..n 在栈中恰好出现两次，初始无相邻相同元素。
// 每次可交换相邻两个元素位置；
// 若相邻两元素相同则同时消去，上方元素下落并可触发连锁消去。
// 第一行输出清空栈所需的最少交换次数 m，
// 接下来 m 行依次输出每次交换的下标 p_i（交换 p_i 与 p_i+1）。
// 数据范围：1 <= n <= 50000，1 <= a_i <= n，
// 保证存在不超过 10^6 次操作的方案。
// 难度评分：1900（洛谷分级换算）
// 算法标签：树状数组、贪心
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e4+5;
const int MAXM = 1e6+5;

int step[MAXM],cnt;
int n,m;
int tree[MAXN<<1];
int nums[MAXN<<1];
int pos[MAXN];

inline int lowbit(int x){
    return x&-x;
}

void add(int x,int v){
    while(x<=2*n){
        tree[x]+=v;
        x+=lowbit(x);
    }
}

int query(int x){
    int ans=0;
    while(x){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}

int main()
{
    cin>>n;
    for(int i=1;i<=2*n;i++){
        cin>>nums[i];
        add(i,1);
    }
    for(int i=1;i<=2*n;i++){
        if(pos[nums[i]]){
            int dis=query(i-1)-query(pos[nums[i]]);
            int now=i;
            while(dis){
                step[++cnt]=now-1-m;
                now--;
                dis--;
            }
            add(pos[nums[i]],-1);
            add(i,-1);
            m+=2;
        }   
        else{
            pos[nums[i]]=i;
        }
    }
    cout<<cnt<<endl;
    for(int i=1;i<=cnt;i++){
        cout<<step[i]<<endl;
    }
    return 0;
}