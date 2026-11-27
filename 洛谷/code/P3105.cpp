// https://www.luogu.com.cn/problem/P3105
// 题意：输入奶牛数 N，以及每头牛的坐标 x_i 和毛色（W 白色或 S 斑点）。
// 可以把任意多头白色牛涂成斑点牛（也可不涂），然后拍摄一段连续区间内的奶牛照片。
// 要求照片里白色牛和斑点牛数量恰好相等，且照片长度（最右牛与最左牛坐标差）最大。
// 输出一个整数表示最大照片长度。
// 数据范围：2 <= N <= 10^5，0 <= x_i <= 10^9，x_i 互不相同且至少有 1 头白牛。
#include<bits/stdc++.h>
// 算法标签：前缀和、贪心、排序
using namespace std;
const int MAXN = 1e5+5;

struct node{
    int pos,col;
}nums[MAXN];
int n;
int sum[MAXN];
map<int,int>m;

bool cmp(node a,node b){
    return a.pos<b.pos;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        char c;
        cin>>nums[i].pos>>c;
        if(c=='W')
            nums[i].col=1;
        else
            nums[i].col=-1;
    }
    sort(nums+1,nums+n+1,cmp);
    int ans=0;
    for(int i=1;i<=n;i++){
        sum[i]=sum[i-1]+nums[i].col;

        //小于0的部分  只记录第一次出现的时候的坐标
        //并且第一次出现的话一定不会贡献答案
        //因为这个sum变化是连续的且不会保持不变的
        //第一次出现说明以前所有的值都是大于它的  要不然不可能是第一次出现
        if(m[sum[i]]==0&&sum[i]<0)
        	m[sum[i]]=i;
		else if(sum[i]<0)
			ans=max(ans,nums[i].pos-nums[m[sum[i]]+1].pos);

		if(sum[i]%2==0&&sum[i]>=0)
			ans=max(ans,nums[i].pos-nums[1].pos);//表示从头开始到现在  白色牛多的数量是偶数  那么一定可以通过涂色改成一样的
		else if(sum[i]>=0)
			ans=max(ans,nums[i].pos-nums[2].pos);//表示从头开始到现在  白色的牛多的数量是奇数 那么无论第一头牛的是什么颜色
            //只要不要第一头牛  就一定可以通过涂色实现一样
    }
    cout<<ans<<endl;
    return 0;
}
