// ST表查询最大值和最小值
// 给定一个长度为n的数组arr，一共有m次查询
// 每次查询arr[l~r]上的最大值和最小值
// 每次查询只需要打印最大值-最小值的结果
// 测试链接 : https://www.luogu.com.cn/problem/P2880
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下的code，提交时请把类名改成"Main"，可以直接通过
//这个当然可以使用线段树来维持  但是不如这种方法简单
//这个倍增和普通的倍增我感觉是略有不同的
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 70005;
//这里本来50005即可  但是下面访问到了2的16次方
const int LIMIT = 16;

int stmax[MAXN][LIMIT];
int stmin[MAXN][LIMIT];
int arr[MAXN];
int Log2[MAXN];
int n,m;

void build(int n){
    Log2[0]=-1;
    for(int i=1;i<=n;i++){
        Log2[i]=Log2[i>>1]+1;
        stmax[i][0]=arr[i];
        stmin[i][0]=arr[i];
    }
    // 这里需要注意 有的代码中会有j+(1<<(i-1))-1<=n  这样做是为了防止j+(1<<(i-1))越界
    // 因为st[u][i]代表的含义是  u~u+(1<<i)-1  所以u+(1<<i)-1<=n
    // 这样的统计答案也是对的  因为查询的时候  绝对不会有左边界访问到n+1之后的位置
    for(int i=1;i<=Log2[n];i++){
        for(int j=1;j<=n;j++){
            stmax[j][i]=max(stmax[j][i-1],stmax[j+(1<<(i-1))][i-1]);
            stmin[j][i]=min(stmin[j][i-1],stmin[j+(1<<(i-1))][i-1]);
        }
    }
}

int query(int l,int r){
    int p=Log2[r-l+1];
    int maxans=max(stmax[l][p],stmax[r-(1<<p)+1][p]);
    int minans=min(stmin[l][p],stmin[r-(1<<p)+1][p]);
    return maxans-minans;
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        cin>>arr[i];
    build(n);
    while(m--){
        int l,r;
        cin>>l>>r;
        cout<<query(l,r)<<endl;
    }
    return 0;
}