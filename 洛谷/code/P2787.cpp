// https://www.luogu.com.cn/problem/P2787
// 题意：输入字符串长度 n、操作数 m，一个长度为 n 的仅含 26 个英文字母的字符串，以及 m 条操作。
// 大小写不敏感，操作共三种：1 x y k 统计 [x,y] 内字母 k 出现次数；
// 2 x y k 将 [x,y] 全改为 k；
// 3 x y 将 [x,y] 按 a~z 升序排序。
// 按操作顺序依次执行所有修改与查询。
// 对每条操作 1 输出一行一个整数，表示查询区间内字母 k 的出现次数。
// 数据范围：对于 100% 的数据，1 <= n, m <= 50000，字符集最多 26 个字母。
#include<iostream>
#include<cstring>
#include<cctype>
#include<cstdio>
#define lson nod<<1
#define rson nod<<1|1
using namespace std;

struct Node{
    int cnt[26];
    Node(){memset(cnt,0,sizeof(cnt));}
};
Node operator + (Node a,Node b){
    Node c;
    for(int i=0;i!=26;++i)
        c.cnt[i]=a.cnt[i]+b.cnt[i];
    return c;
}
const int MAXN=65536,toc='a'-'A';
char s[MAXN];
int n,m,lazy[MAXN<<2];
Node tree[MAXN<<2],emp;

char c;
inline char toupper(char tmp){return ('a'<=tmp && tmp<='z')?(tmp-toc):tmp;}
inline void read(int &x)
{
    x=0,c=getchar();
    while(c<'0' || c>'9')    c=getchar();
    while('0'<=c && c<='9')    x=(x<<3)+(x<<1)+c-'0',c=getchar();
}

inline void pushdown(int nod,int ln,int rn)
{
    if(lazy[nod]!=-1)
    {
         lazy[lson]=lazy[nod],lazy[rson]=lazy[nod];
        tree[lson]=Node(),tree[rson]=Node();
        tree[lson].cnt[lazy[lson]]=ln;
        tree[rson].cnt[lazy[rson]]=rn;
        lazy[nod]=-1;
    }
}

void build(int nod,int lef,int rig)
{
    if(lef==rig)    tree[nod].cnt[s[lef]-'A']=1;
    else
    {
        int mid=(lef+rig)>>1;
        build(lson,lef,mid);
        build(rson,mid+1,rig);
        tree[nod]=tree[lson]+tree[rson];
    }
}

void update(int nod,int lef,int rig,int goal,int goar,int val)
{
    if(rig<goal || goar<lef)    return;
    if(goal<=lef && rig<=goar)
    {
        tree[nod]=Node(),lazy[nod]=val;
        tree[nod].cnt[val]=rig-lef+1;
    }
    else
    {
        int mid=(lef+rig)>>1;
        pushdown(nod,mid-lef+1,rig-mid);
        if(goal<=mid)    update(lson,lef,mid,goal,goar,val);
        if(goar>mid)    update(rson,mid+1,rig,goal,goar,val);
        tree[nod]=tree[lson]+tree[rson];
    }
}

Node query(int nod,int lef,int rig,int goal,int goar)
{
    if(rig<goal || goar<lef)    return emp;
    if(goal<=lef && rig<=goar)    return tree[nod];

    Node ret;
    int mid=(lef+rig)>>1;
    pushdown(nod,mid-lef+1,rig-mid);
    if(goal<=mid)    ret=ret+query(lson,lef,mid,goal,goar);
    if(goar>mid)    ret=ret+query(rson,mid+1,rig,goal,goar);

    return ret;
}

int main()
{
    read(n),read(m),scanf("%s",s+1);
    memset(lazy,-1,sizeof(lazy));
    for(int i=n;i!=0;s[i]=toupper(s[i]),--i);

    build(1,1,n);
    int a,b,c; char d;
    for(int i=0;i!=m;++i)
    {
        read(a),read(b),read(c);
        if(a!=3)        scanf("%c",&d),d=toupper(d);
        if(a==1)        printf("%d\n",query(1,1,n,b,c).cnt[d-'A']);
        else if(a==2)    update(1,1,n,b,c,d-'A');
        else
        {
            Node tmp=query(1,1,n,b,c);
            for(int i=0,l,r=b-1;i!=26;++i)
            {
                if(tmp.cnt[i]==0)    continue;
                l=r+1,r=l+tmp.cnt[i]-1;
                update(1,1,n,l,r,i);
            }
        }
    }
    return 0;
}
