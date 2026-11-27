// 测试链接 : https://www.luogu.com.cn/problem/P1527
// 矩阵内第k小，第一种写法，C++版
// 题意：输入 n*n 整数矩阵和 q 次询问。
// 每次询问以 (x1, y1) 为左上角、(x2, y2) 为右下角的子矩阵中第
// k 小的数。
// 对每次询问输出一行一个整数表示答案。
// 数据范围：
// 1 <= n <= 500（矩阵边长）
// 1 <= q <= 6*10^4（询问次数）
// 0 <= a_{i,j} <= 10^9（矩阵元素值）
// 给定一个n * n的矩阵，接下来有q条查询，格式如下
// 查询 a b c d k : 左上角(a, b)，右下角(c, d)，
// 打印该区域中第k小的数
// 1 <= n <= 500
// 1 <= q <= 6 * 10^4
// 0 <= 矩阵中的数字 <= 10^9
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
//这个就是一个二维的  没有什么特殊的
// 算法标签：整体二分、二维树状数组
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 605;
const int MAXQ = 6e4+5;

int n,q;
struct node{
    int x,y,val;
}nums[MAXN*MAXN];
int sz;

int tree[MAXN][MAXN];

int qid[MAXQ];
int a[MAXQ];
int b[MAXQ];
int c[MAXQ];
int d[MAXQ];
int k[MAXQ];

int lset[MAXQ];
int rset[MAXQ];

int ans[MAXQ];

inline int lowbit(int x){
    return x&-x;
}

void add(int x,int y,int v){
    for(int i=x;i<=n;i+=lowbit(i)){
        for(int j=y;j<=n;j+=lowbit(j)){
            tree[i][j]+=v;
        }
    }
}

int query(int x,int y){
    int ans=0;
    for(int i=x;i;i-=lowbit(i)){
        for(int j=y;j;j-=lowbit(j)){
            ans+=tree[i][j];
        }
    }
    return ans;
}

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

bool cmp(node a,node b){
    return a.val<b.val;
}

void compute(int ql,int qr,int vl,int vr){
    if(ql>qr){
        return ;
    }
    if(vl==vr){
        for(int i=ql;i<=qr;i++){
            ans[qid[i]]=nums[vl].val;
        }
    }
    else{
        int mid=(vl+vr)/2;
        for(int i=vl;i<=mid;i++){
            add(nums[i].x,nums[i].y,1);
        }
        int lsz=0,rsz=0;
        for(int i=ql;i<=qr;i++){
            int id=qid[i];
            int num=query(c[id],d[id])-query(a[id]-1,d[id])-query(c[id],b[id]-1)+query(a[id]-1,b[id]-1);
            if(num>=k[id]){
                lset[++lsz]=id;
            }
            else{
                rset[++rsz]=id;
                k[id]-=num;
            }
        }
        for (int i = 1; i <= lsz; i++) {
			qid[ql + i - 1] = lset[i];
		}
		for (int i = 1; i <= rsz; i++) {
			qid[ql + lsz + i - 1] = rset[i];
		}
		for(int i=vl;i<=mid;i++){
            add(nums[i].x,nums[i].y,-1);
        }
		compute(ql, ql + lsz - 1, vl, mid);
		compute(ql + lsz, qr, mid + 1, vr);
    }
}

int main()
{
    n=read(),q=read();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            nums[++sz].x=i;
            nums[sz].y=j;
            nums[sz].val=read();
        }
    }
    sort(nums+1,nums+sz+1,cmp);
    for(int i=1;i<=q;i++){
        qid[i]=i;
        a[i]=read();
        b[i]=read();
        c[i]=read();
        d[i]=read();
        k[i]=read();
    }
    compute(1,q,1,sz);
    for(int i=1;i<=q;i++){
        printf("%d\n",ans[i]);
    }
	return 0;
}