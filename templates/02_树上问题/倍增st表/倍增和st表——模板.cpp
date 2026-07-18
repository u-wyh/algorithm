// 国旗计划
// 给定点的数量m，点的编号1~m，所有点围成一个环
// i号点一定顺时针到达i+1号点，最终m号点顺指针回到1号点
// 给定n条线段，每条线段(a, b)，表示线段从点a顺时针到点b
// 输入数据保证所有线段可以把整个环覆盖
// 输入数据保证每条线段不会完全在另一条线段的内部
// 也就是线段之间可能有重合但一定互不包含
// 返回一个长度为n的结果数组ans，ans[x]表示一定选x号线段的情况下
// 至少选几条线段能覆盖整个环
// 测试链接 : https://www.luogu.com.cn/problem/P4155
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下的code，提交时请把类名改成"Main"，可以直接通过
//这道题的思路是既然两条边一定不可能相互包含  那么从这个线段出发可以到达的最远的距离就是从这个最右边的交集线走
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 200001;
const int LIMIT = 18;

int power;
// stjump[i][p] : 从i号线段出发，跳的次数是2的p次方，能到达的最右线段的编号
int stjump[MAXN << 1][LIMIT];
int ans[MAXN];//记录答案数组
int n, m;
struct flag{
    int num,s,e;//表示编号  开始 结束位置
}line[MAXN];

int read(){
	int a=0,k=1;
	char c=getchar();
	while (!isdigit(c)){
        if (c=='-')k=-1;c=getchar();
    }
	while (isdigit(c)){
        a=a*10+c-'0';c=getchar();
    }
	return a*k;
}

//比较函数
bool cmp(flag a,flag b){
    return a.s < b.s;
}

//求出不超过n的最大2的幂次方是多少  即‘跳跃’次数不会超过
int log2(int n) {
    int ans = 0;
    while ((1 << ans) <= (n >> 1)) {
        ans++;
    }
    return ans;
}

void build() {
    //首先将线段变成一个链的形式
    for (int i = 1; i <= n; i++) {
        if (line[i].s > line[i].e) {
            //所有左边界大于右边界的边 更改一下
            line[i].e += m;
        }
    }
    sort(line+1 ,line+n+1,cmp);
    // for(int i=1;i<=n;i++)
    //    printf("%d %d %d\n",line[i][0],line[i][1],line[i][2]);
    for (int i = 1; i <= n; i++) {
        line[i + n].num = line[i].num;
        line[i + n].s = line[i].s + m;
        line[i + n].e = line[i].e + m;
    }
    //实现线段的克隆
    int e = n << 1;//线段的数目变为原来两倍

    //记录每条线段走一步可以到什么地方
    for (int i = 1, arrive = 1; i <= e; i++) {
        //arrive  表示寻找到的目前的线段条数
        while (arrive + 1 <= e && line[arrive + 1].s <= line[i].e) {
            //判断条件是  这条线段没有越界 即不是最后一条线段
            //并且这条线段的左边界小于等于目前线段的右边界
            arrive++;
        }
        stjump[i][0] = arrive;//表示跳跃2的0次方步可以到达的线段编号
    }
    for (int p = 1; p <= power; p++) {
        for (int i = 1; i <= e; i++) {
            stjump[i][p] = stjump[stjump[i][p - 1]][p - 1];
        }
    }//完成st表
}

int jump(int i) {
    //表示现在来到了第i条线段  要统计这个战士的答案
    int aim = line[i].s + m, cur = i, next, ans = 0;
    //aim是这条线段期望的目标
    for (int p = power; p >= 0; p--) {
        next = stjump[cur][p];//表示跳2的p次方可以到哪
        if (next != 0 && line[next].e < aim) {
            ans += 1 << p;
            cur = next;
        }
    }
    return ans + 1 + 1;
}

void compute() {
    power = log2(n);
    build();
    for (int i = 1; i <= n; i++) {
        //填答案
        //如果一开始的顺序是  1 2 3 4 5
        //但是经过排序可能变为5 3 1 4 2
        //那么我们一开始就记录了编号   将相应的答案填到对应编号中
        ans[line[i].num] = jump(i);
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        line[i].num=i;
        line[i].s=read();
        line[i].e=read();
    }
    compute();
    for(int i=1;i<=n;i++)
        cout<<ans[i]<<' ';
    return 0;
}