// 大鱼吃小鱼问题
// 给定一个数组arr，每个值代表鱼的体重
// 每一轮每条鱼都会吃掉右边离自己最近比自己体重小的鱼，每条鱼向右找只吃一条
// 但是吃鱼这件事是同时发生的，也就是同一轮在A吃掉B的同时，A也可能被别的鱼吃掉
// 如果有多条鱼在当前轮找到的是同一条小鱼，那么在这一轮，这条小鱼同时被这些大鱼吃
// 请问多少轮后，鱼的数量就固定了
// 比如 : 8 3 1 5 6 7 2 4
// 第一轮 : 8吃3；3吃1；5、6、7吃2；4没有被吃。数组剩下 8 5 6 7 4
// 第二轮 : 8吃5；5、6、7吃4。数组剩下 8 6 7
// 第三轮 : 8吃6。数组剩下 8 7
// 第四轮 : 8吃7。数组剩下 8。
// 过程结束，返回4
// 测试链接 : https://www.nowcoder.com/practice/77199defc4b74b24b8ebf6244e1793de
// 测试链接 : https://leetcode.cn/problems/steps-to-make-array-non-decreasing/
#include<bits/stdc++.h>
using namespace std;

struct fish{
    int weight,turn;
}nums[1000];
int n;
int st[1000],r=0,ans=0;

int main()
{
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>nums[i].weight;
        nums[i].turn=0;//这个最终是用于记录当前的鱼吃掉右边小于自己的鱼需要的步数
    }
    for(int i=n-1;i>=0;i--){
        while(r>0&&nums[st[r-1]].weight<nums[i].weight){
            //这道题的栈是小压大
            nums[i].turn=max(nums[i].turn+1,nums[st[--r]].turn);
            //吃掉一个鱼耗费1  然后和他吃掉的鱼的步骤  比大小
        }
        st[r++]=i;
        ans=max(ans,nums[i].turn);
    }
    cout<<ans;
    return 0;
}
