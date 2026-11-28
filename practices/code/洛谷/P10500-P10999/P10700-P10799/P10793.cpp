// https://www.luogu.com.cn/problem/P10793
// 题意：给 n 个整数格子区间 [l,r]，把它们分成若干非空组。
// 每组所有区间共同覆盖的格子数必须至少为 w。求最少组数，无解输出 No。
// 数据范围：1 ≤ T ≤ 20，1 ≤ n ≤ 2 × 10^5，
// 0 ≤ w ≤ 10^6，1 ≤ l ≤ r ≤ 10^6。
// 难度评分：1300（洛谷分级换算）
// 算法标签：贪心、区间调度

#include<bits/stdc++.h>
using namespace std;

int T,n,w;
struct node{
    int lt,rt;
    bool friend operator < (const node &a,const node &b){
        return a.rt<b.rt;
    }
}A[200005];

int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&w);
        bool tag=true;
        for(int i=1;i<=n;i++){
            scanf("%d%d",&A[i].lt,&A[i].rt);
            if(A[i].rt-A[i].lt+1<w)tag=false;
        }
        if(!tag){
            puts("No");
            continue;
        }
        if(!w){
            puts("1");
            continue;
        }
        sort(A+1,A+1+n);
        int Max=-1;
        int pos=0;
        for(int i=1;i<=n;i++){
            if(Max<A[i].lt){
                pos++;
                Max=A[i].rt-w+1;
            }
        }
        printf("%d\n",pos);
    }
    return 0;
}
