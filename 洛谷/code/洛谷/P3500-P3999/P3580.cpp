// https://www.luogu.com.cn/problem/P3580
// 题意：输入列车数 n、单程行驶时间 s，
// 以及按非降序排列的各列车到达上城镇的最早可出发时间 t_1..t_n。
// 单线铁轨任意时刻所有列车必须同向行驶，同站先后发车至少间隔 1 分钟，
// 每列火车从上城镇开到下城镇立即零耗时装货再返回上城镇。
// 输出最后一列火车返回上城镇的最早时间。
// 数据范围：1 <= n <= 10^6，1 <= s <= 10^9，
// 0 <= t_1 <= t_2 <= ... <= t_n <= 10^9。
// 算法标签：线性动态规划、双指针
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e6+5;

int n,s;
int nums[MAXN];
int f[MAXN];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}


signed main()
{
    n=read(),s=read();
    nums[0]=-1;
    for(int i=1;i<=n;i++){
        nums[i]=read();
        nums[i]=max(nums[i],nums[i-1]+1);
    }
    f[1]=2*s+nums[1];
    int p=0;
    for(int i=2;i<=n;i++){
        while(p<i&&(f[p]-p)<(nums[i]-i+1)){
            p++;
        }
        f[i]=1-p+2*s+i-1+nums[i];
        if(p!=i){
            f[i]=min(f[i],f[p]-2*p+2*i+2*s-2);
        }
    }
    cout<<f[n]<<endl;
    return 0;
}