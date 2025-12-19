#include<bits/stdc++.h>
#define N 200005
using namespace std;
int n,m,cnt,rt,fa[N];
int h[N],ans[N];
vector<set<int> >st;
struct node {
	int to,next;
} e[N<<1];
struct Line {
	int l,opt,id;
	Line(int L=0,int O=0,int Id=0) {
		l=L,opt=O,id=Id;
	}
	bool operator <(Line a) const {
		return l==a.l?opt>a.opt:l<a.l;
	}
};
set<Line>line;
struct Pair {
	int l,r,x,opt,id;
	bool operator <(Pair a) const {
		return x==a.x?opt<a.opt:x<a.x;
	}
} p[N],q[N];
const int Mxdt=100000;
inline char gc() {
	static char buf[Mxdt],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,Mxdt,stdin),p1==p2)?EOF:*p1++;
}
inline char pc(char ch,bool bj) {
	static char buf[Mxdt],*p1=buf,*p2=buf+Mxdt;
	return (bj||(*p1++=ch)&&p1==p2)&&fwrite(p1=buf,1,p1-buf,stdout),0;
}
inline int read() {
	int res=0;
	char ch=gc();
	while(ch<'0')ch=gc();
	while(ch>='0')res=(res<<3)+(res<<1)+(ch^48),ch=gc();
	return res;
}
void print(int x) {
	if(x>9)print(x/10);
	pc(x%10^48,false);
}
inline void printnum(int x,char ch) {
	if(x<0)pc('-',false),x=-x;
	print(x),pc(ch,false);
}
void Addedge(int x,int y) {
	e[++cnt]=(node) {y,h[x]},h[x]=cnt;
}
set<Line>::iterator it;
void Merge(int x,int y) {
	if(st[x].size()<st[y].size())swap(st[x],st[y]);
	for(int a:st[y])st[x].insert(a);
	st[y].clear();
}
void Dfs(int x) {
	for(int i=h[x]; i; i=e[i].next)Dfs(e[i].to),Merge(x,e[i].to);
	ans[x]=st[x].size();
}
int main() {
	n=read(),m=read();st.resize(n+1);
	for(int i=1,a,b,c,d; i<=n; ++i) {
		a=read(),b=read(),c=read(),d=read();
		p[++cnt].id=i,p[cnt].opt=1,p[cnt].l=b,p[cnt].r=d,p[cnt].x=a;
		p[++cnt].id=i,p[cnt].opt=2,p[cnt].l=b,p[cnt].r=d,p[cnt].x=c;
	}
	for(int i=1; i<=m; ++i)q[i].x=read(),q[i].l=read(),q[i].r=read();
	sort(p+1,p+cnt+1),sort(q+1,q+m+1);
	for(int i=1,j=1; i<=m; ++i) {
		while(j<=cnt&&(q[i].x>p[j].x||(q[i].x==p[j].x&&p[j].opt==1))) {
			if(p[j].opt==1) {
				if((it=line.lower_bound(Line(p[j].l)))!=line.end())
					fa[p[j].id]=((*it).opt==2)?(*it).id:fa[(*it).id];
				line.insert(Line(p[j].l-1,1,p[j].id)),line.insert(Line(p[j].r,2,p[j].id));
			} else line.erase(Line(p[j].l-1,1,p[j].id)),line.erase(Line(p[j].r,2,p[j].id));
			++j;
		}
		if((it=line.lower_bound(Line(q[i].l,3)))!=line.end()) {
			if((*it).opt==2)st[(*it).id].insert(q[i].r);
			else st[fa[(*it).id]].insert(q[i].r);
		}
	}
	cnt=0;
	for(int i=1; i<=n; ++i)if(fa[i])Addedge(fa[i],i);
	for(int i=1; i<=n; ++i)if(!fa[i])Dfs(i);
	for(int i=1; i<=n; ++i)printnum(ans[i],'\n');
	return pc('0',1);
}
