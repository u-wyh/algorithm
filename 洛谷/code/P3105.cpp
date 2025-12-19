#include<bits/stdc++.h>
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
