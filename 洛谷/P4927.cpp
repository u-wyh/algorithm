#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#define lc now<<1
#define rc now<<1|1
#define int __int128
using namespace std;
int read()
{
    char ch=getchar();int h=0,t=1;
    while((ch>'9'||ch<'0')&&ch!='-') ch=getchar();
    if(ch=='-') t=-1,ch=getchar();
    while(ch>='0'&&ch<='9') h=h*10+ch-'0',ch=getchar();
    return h*t;
}
const int N=1e5+100,mod=998244353;
struct Que{int op,l,r,k;}A[N];
int n,m,P[N];
int ksm(int x,int k)
{
    int s=1;for(;k;k>>=1,x=x*x%mod)
                if(k&1) s=s*x%mod;return s;
}
void print(int x) {if(x>9) print(x/10);putchar(x%10+'0');}
struct Seg {int l,val,tag,v;}t[N<<2];
int tot,ans;
int f(int x) {return x*x;}
void pushup(int now,int l,int r)
{
	ans-=f(t[now].v);
	t[now].v=t[lc].v+t[rc].v;
	ans+=f(t[now].v);
	t[now].l=t[lc].l+t[rc].l+f(r-l+1);
	t[now].val=t[lc].val+t[rc].val+(r-l+1)*t[now].v;
}
void build(int now,int l,int r)
{
	if(l==r)
	{
		t[now]=(Seg){1,P[l],0,P[l]};
		tot+=P[l];ans+=f(P[l]);return;
	}
	int mid=(l+r)>>1;
	build(lc,l,mid);
	build(rc,mid+1,r);
	pushup(now,l,r);
}
void put(int now,int l,int r,int k,int op)
{
	if(op)
	{
		ans+=2*k*t[now].val;
		ans+=k*k*t[now].l;
	}
	t[now].tag+=k;
	t[now].v+=k*(r-l+1);
	t[now].val+=t[now].l*k;
}
void pushdown(int now,int l,int mid,int r)
{
	int &s=t[now].tag;if(!s) return;
	put(lc,l,mid,s,0);put(rc,mid+1,r,s,0);s=0;
}
void Add(int now,int l,int r,int gl,int gr,int k)
{
	if(l>=gl&&r<=gr) {put(now,l,r,k,1);return;}
	int mid=(l+r)>>1;
	pushdown(now,l,mid,r);
	if(gl<=mid) Add(now<<1,l,mid,gl,gr,k);
	if(gr>mid) Add(now<<1|1,mid+1,r,gl,gr,k);
	pushup(now,l,r);
}
signed main()
{
    n=read();m=read();
    for(int i=1;i<=n;i++) P[i]=read();
    for(int i=1;i<=m;i++)
    {
        int op=read(),l=0,r=0,k=0;
        if(op==1) l=read(),r=read(),k=read();
        A[i]=(Que){op,l,r,k};
    }
	build(1,1,n);
	for(int i=1;i<=m;i++)
		if(A[i].op==2)
		{
			int fz=ans/__gcd(ans,tot);
			int fm=tot/__gcd(ans,tot);
			print(fz%mod*ksm(fm,mod-2)%mod),puts("");
		}
		else tot+=(A[i].r-A[i].l+1)*A[i].k,Add(1,1,n,A[i].l,A[i].r,A[i].k);
}
