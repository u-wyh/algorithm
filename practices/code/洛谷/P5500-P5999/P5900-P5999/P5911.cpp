// https://www.luogu.com.cn/problem/P5911
// 题意：桥最大承重为 W，有 n 个队员各有过桥时间 t_i 和重量 w_i；
// 队伍需分批过桥
// （每批总重 <= W，耗时取该批最大 t_i，整批通过后下一批再上），
// 求最短总时间。
// 输入 W, n 及每人的 (t, w)；输出最少总过桥时间。
// 数据范围：100 <= W <= 400，1 <= n <= 16，
// 1 <= t <= 50，10 <= w <= 100。
//P5911
//这道题的关键是枚举所有的子集
// 算法标签：状态压缩动态规划、子集枚举
#include<bits/stdc++.h>
using namespace std;
#define int long long

int weight,n;
struct node{
    int t,w;
}nums[16];
int f[1<<16];
int t[1<<16];//表示如果是这个状态 时间是多少
int w[1<<16];//表示如果是这个状态 重量是多少

signed main()
{
    cin>>weight>>n;
    for(int i=0;i<n;i++){
        cin>>nums[i].t>>nums[i].w;
    }
    for(int s=0;s<(1<<n);s++){
        //枚举子集
        for(int i=0;i<n;i++){
            if(s&(1<<i)){
                //表示这个状态存在这个人
                t[s]=max(t[s],nums[i].t);
                w[s]+=nums[i].w;
            }
        }
    }
    for(int i=0;i<(1<<n);i++){
        f[i]=INT_MAX;
    }
    f[0]=0;
    for(int s=1;s<(1<<n);s++){
        for(int s1=s;;s1=s&(s1-1)){
            //这样可以保证s1一定是s的子集
            int s2=s^s1;//表示这是s的最后一批
            if(w[s2]<=weight){
                f[s]=min(f[s],f[s1]+t[s2]);
            }
            if(s1==0){
                //这里不能放在循环中作为判断条件
                //因为或许最后一次就是全部过去了
                break;
            }
        }
        //cout<<f[s]<<endl;
    }
    cout<<f[(1<<n)-1];
    return 0;
}
