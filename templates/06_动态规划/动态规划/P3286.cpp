// https://www.luogu.com.cn/problem/P3286
// 这道题查询l~r之间的数字的k进制表示方式  将非0的数字合并成一堆的最少步数的累加和
// 我们知道合并成一堆  需要的是权值中位数  但是我们有没有办法全部展开所有的数字的k进制  所以我们使用数位dp来累加贡献
// 我们初始时认为所有的数字全部合并到最低位的位置  得到一个初始时的答案
// 然后将合并的位置逐渐右移  如果某个数字在这个位置由于在之前的位置 那么就会有贡献  如果不优于  那么一定会有损失
// 我们只计算贡献  有损失的我们认为  答案已经固定了
// 这有一个很关键的点  就是合并位置产生的结果是一个单峰函数  如果当前位置有损失 那么继续右移还是会有损失 
// 我们累加贡献  得到答案
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXH = 70;

int x,y,k;
int nums[MAXH];
int len;
int f[MAXH][7000][2];

int dfs(int x,int sum,int p,int free){
    if(sum<0){
        // 因为如果继续向下遍历的话  那么sum只会变得更小
        return 0;
    }
    if(x==0){
        return sum;
    }
    if(f[x][sum][free]!=-1){
        return f[x][sum][free];
    }
    int ans=0;
    int up=free?k-1:nums[x];
    for(int i=0;i<=up;i++){
        if(p==1){
            // 最初的时候 我们将所有的数字全部合并到最右边 也就是最低位
            ans+=dfs(x-1,sum+x*i-i,p,free||i<nums[x]);
        }
        else{
            if(x<p){
                // 目前合并位置左移  也就是往高位移动  那么右边的距离增加
                ans+=dfs(x-1,sum-i,p,free||i<nums[x]);
            }
            else{
                // 目前合并位置左移  也就是往高位移动  那么左边的距离减少
                ans+=dfs(x-1,sum+i,p,free||i<nums[x]);
            }
        }
    }
    f[x][sum][free]=ans;
    return ans;
}

int compute(int x){
    if(x==0){
        return 0;
    }
    len=0;
    while(x){
        nums[++len]=x%k;
        x/=k;
    }
    int ans=0;
    for(int i=1;i<=len;i++){
        memset(f,-1,sizeof(f));
        if(i==1){
            ans+=dfs(len,0,i,0);
        }
        else{
            ans-=dfs(len,0,i,0);
        }
    }
    return ans;
}

signed main()
{
    cin>>x>>y>>k;
    cout<<(compute(y)-compute(x-1))<<endl;
    return 0;
}