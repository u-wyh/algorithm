#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;
const int LIMIT = 21;

int power;
int ans;
int stjump[MAXN << 1][LIMIT];
int n, m;
struct flag{
    int num,s,e;//表示编号  开始 结束位置
}line[MAXN<<1];

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

bool cmp(flag a,flag b){
    return a.s < b.s;
}//比较函数

int log2(int n) {
    int ans = 0;
    while ((1 << ans) <= (n >> 1)) {
        ans++;
    }
    return ans;
}
//求出不超过n的最大2的幂次方是多少  即‘跳跃’次数不会超过

void build() {
    for (int i = 1; i <= n; i++) {
        if (line[i].s > line[i].e) {
            //所有左边界大于右边界的边 更改一下
            line[i].e += m;
        }
    }//首先将线段变成一个链的形式
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

    for (int i = 1, arrive = 1; i <= e; i++) {
        //arrive  表示寻找到的目前的线段条数
        while (arrive + 1 <= e && line[arrive + 1].s <= line[i].e) {
            //判断条件是  这条线段没有越界 即不是最后一条线段
            //并且这条线段的左边界小于等于目前线段的右边界
            arrive++;
        }
        stjump[i][0] = arrive;//表示跳跃2的0次方步可以到达的线段编号
    }//记录每条线段走一步可以到什么地方

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
    ans=INT_MAX;
    for (int i = 1; i <= n; i++) {
        ans=min(ans,jump(i));
    }
}

int main()
{
    cin>>m>>n;
    for(int i=1;i<=n;i++){
        line[i].num=i;
        line[i].s=read();
        line[i].e=read()+1;
        if(line[i].s==line[i].e%m){
            cout<<1<<endl;
            return 0;
        }
    }
    compute();
    if(ans==INT_MAX||ans>n){
        cout<<"impossible";
        return 0;
    }
    cout<<ans<<endl;
    return 0;
}
