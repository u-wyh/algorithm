// https://www.luogu.com.cn/problem/P3088
// 题意：输入奶牛数量 N、距离阈值 D，
// 以及每头奶牛的位置 x_i 和身高 h_i。
// 如果一头牛左侧距离 D 以内和右侧距离 D 以内（含距离恰好为 D）都存在身高
// 至少是它 2 倍的奶牛，它就会觉得拥挤。
// 求觉得拥挤的奶牛总数量。
// 输出一个整数表示答案。
// 数据范围：1 <= N <= 50000，
// 1 <= D, x_i, h_i <= 10^9，x_i 互不相同。
// 难度评分：1600（洛谷分级换算）
// 算法标签：单调队列、排序
#include<bits/stdc++.h>
using namespace std;

int n,d;
struct row{
    int x,h;
}nums[50000];
int q[50005],l[50005],r[50005],ans=0;
int head,tail;

int cmp(row a,row b){
    return a.x<b.x;
}

int main()
{
    cin>>n>>d;
    for(int i=0;i<n;i++){
        cin>>nums[i].x>>nums[i].h;
    }
    sort(nums,nums+n,cmp);
    /*
    printf("---------------------------------------\n");
    for(int i=0;i<n;i++){
        printf("%d %d\n",nums[i].x,nums[i].h);
    }
    */
    head=tail=0;
    for(int i=0;i<n;i++){
        while(head<tail&&nums[i].x-nums[q[head]].x>d){
            head++;
        }
        while(head<tail&&nums[q[tail-1]].h<nums[i].h){
            tail--;
        }
        q[tail++]=i;
        if(nums[q[head]].h/2>=nums[i].h)
            l[i]=1;
        //printf("%5d",l[i]);
    }
    //printf("\n");
    memset(q,0,sizeof(q));
    head=tail=0;
    for(int i=n-1;i>=0;i--){
        while(head<tail&&nums[q[head]].x-nums[i].x>d){
            head++;
        }
        while(head<tail&&nums[q[tail-1]].h<nums[i].h){
            tail--;
        }
        q[tail++]=i;
        if(nums[q[head]].h/2>=nums[i].h)
            r[i]=1;
        //printf("%5d",r[i]);
    }
    //printf("\n");
    for(int i=0;i<n;i++){
        if(l[i]&&r[i])
            ans++;
    }
    cout<<ans;
    return 0;
}
