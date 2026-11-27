// https://www.luogu.com.cn/problem/P1639
// 题意：要在数轴上从 a 运到 b，有一个连接 x、y 的双向传送门，
// 使用它没有距离成本，也可以不使用。求需要用车运输的最短总距离。
// 数据范围：a,b,x,y 均为 [0,100] 内的整数，不要求互不相同。
// 算法标签：数学、分类讨论

#include<stdio.h>
#include<math.h>

int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    int a,b,x,y;
    scanf("%d %d %d %d",&a,&b,&x,&y);
    int ans=abs(a-b);
    ans=min(ans,abs(a-x)+abs(b-y));
    ans=min(ans,abs(a-y)+abs(b-x));
    printf("%d\n",ans);
    return 0;
}
