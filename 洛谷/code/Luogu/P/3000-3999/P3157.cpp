// 动态逆序对，C++版
// 给定一个长度为n的排列，1~n所有数字都出现一次
// 如果，前面的数 > 后面的数，那么这两个数就组成一个逆序对
// 给定一个长度为m的数组，表示依次删除的数字
// 打印每次删除数字前，排列中一共有多少逆序对，一共m条打印
// 1 <= n <= 10^5
// 1 <= m <= 5 * 10^4
// 测试链接 : https://www.luogu.com.cn/problem/P3157
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
//这道题还是比较巧妙的
//我们将时间作为第一维   坐标作为第二维  效果作为第三维  统计答案作为第四维（附属）
//首先按照时间排序  那么可以有一点先确定 就是左边的组不能够统计右边的信息 
//即他们的地位是不平等的   时效性的设置
//右边的组需要统计左边组可以和自己构成逆序对的包括：前面大于自己的  后面小于自己的
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 5e4+5;

int n,m;

int pos[MAXN];

struct node{
    int val;
    int pos;
    int v;
    int sub;
}nums[MAXN+MAXM];
int cnt=0;

int tree[MAXN];

long long ans[MAXM];

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

inline int lowbit(int x){
    return x&-x;
}

void add(int x,int v){
    while(x<=n){
        tree[x]+=v;
        x+=lowbit(x);
    }
}

int query(int x){
    int ans=0;
    while(x){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}

bool cmp(node a,node b){
    return a.pos<b.pos;
}

void merge(int l,int mid,int r){
    int p1,p2;
    for(p1=l-1,p2=mid+1;p2<=r;p2++){
        while(p1+1<=mid&&nums[p1+1].pos<=nums[p2].pos){
            p1++;
            add(nums[p1].val,nums[p1].v);
        }
        ans[nums[p2].sub]+=nums[p2].v*(query(n)-query(nums[p2].val));
    }
    for(int i=l;i<=p1;i++){
        add(nums[i].val,-nums[i].v);
    }

    for(p1=mid+1,p2=r;p2>mid;p2--){
        while(p1-1>=l&&nums[p1-1].pos>nums[p2].pos){
            p1--;
            add(nums[p1].val,nums[p1].v);
        }
        ans[nums[p2].sub]+=nums[p2].v*query(nums[p2].val-1);
    }
    for(int i=mid;i>=p1;i--){
        add(nums[i].val,-nums[i].v);
    }
    sort(nums+l,nums+r+1,cmp);
}

void cdq(int l,int r){
    if(l==r){
        return ;
    }
    int mid=(l+r)>>1;
    cdq(l,mid);
    cdq(mid+1,r);
    merge(l,mid,r);
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        int v=read();
        pos[v]=i;
        nums[++cnt].val=v;
        nums[cnt].pos=i;
        nums[cnt].v=1;
        nums[cnt].sub=0;
    }
    for(int i=1;i<=m;i++){
        int v=read();
        nums[++cnt].val=v;
        nums[cnt].pos=pos[v];
        nums[cnt].v=-1;
        nums[cnt].sub=i;
    }
    cdq(1,cnt);
    for (int i = 1; i < m; i++) {
		ans[i] += ans[i - 1];
	}
	for (int i = 0; i < m; i++) {
		cout << ans[i] << '\n';
	}
    return 0;
}