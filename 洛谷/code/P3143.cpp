// https://www.luogu.com.cn/problem/P3143
// 题意：输入钻石数 N、允许的最大差值 K，以及每颗钻石的大小。
// 有两个展示柜，要求同一个柜子里任意两颗钻石的大小差都不超过 K（可以恰好为 K）。
// 求两个展示柜一共最多能展示多少颗钻石。
// 输出一个整数表示最大展示总数。
// 数据范围：1 <= N <= 5*10^4，0 <= K <= 10^9，钻石大小为不超过 10^9 的正整数。
#include<cstdio>
#include<algorithm>
using namespace std;
int n,k,a[50005],c[50005],r=2,ma,ans;//c[i]用来存从i-1向左最多可以取多少颗钻石。
int main(){
    scanf("%d %d",&n,&k);
	a[n+1]=2100000000;
    for(int i=1;i<=n;++i)
        scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    for(int i=1;i<=n;++i){
        while(a[r]<=a[i]+k)r++;
        c[r]=max(r-i,c[r]);
        ma=max(ma,c[i]);
        ans=max(ans,ma+r-i);
    }
    printf("%d",ans);
    return 0;
}
