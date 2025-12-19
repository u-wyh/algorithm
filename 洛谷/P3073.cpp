#include<bits/stdc++.h>
using namespace std;
const int maxn=501;
int n;
int mp[maxn][maxn];
inline int read(){//¿ì¶Á
	int x=0,y=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')y=-y; ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*y;
}
int fa[maxn*maxn];
int siz[maxn*maxn];
struct node{
	int u,v,w;
	node(){}
	node(int uu,int vv,int ww){
		u=uu;
		v=vv;
		w=ww;
	}
}edge[maxn*maxn*4];
bool cmp(const node &a,const node &b){
	return a.w<b.w;
}
int ans=0;
void init(){
	for(int i=1;i<=n*n;i++){
		fa[i]=i;
		siz[i]=1;
	}
}
int find(int x){
	if(x==fa[x]) return x;
	else return fa[x]=find(fa[x]);
}
int ex(int i,int j){
	return (i-1)*n+j;
}
int main(){
	n=read();
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			mp[i][j]=read();
		}
	}
	init();
	int tp=1;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			if(i>1){
				edge[tp]=node(ex(i,j),ex(i-1,j),abs(mp[i-1][j]-mp[i][j]));
				tp++;
			}
			if(j>1){
				edge[tp]=node(ex(i,j),ex(i,j-1),abs(mp[i][j-1]-mp[i][j]));
				tp++;
			}
			if(i<n){
				edge[tp]=node(ex(i,j),ex(i+1,j),abs(mp[i+1][j]-mp[i][j]));
				tp++;
			}
			if(j<n){
				edge[tp]=node(ex(i,j),ex(i,j+1),abs(mp[i][j+1]-mp[i][j]));
				tp++;
			}
		}
	}
	sort(edge+1,edge+tp,cmp);
	for(int i=1;i<tp;i++){
		int x=edge[i].u;
		int y=edge[i].v;
		int w=edge[i].w;
		x=find(x);
	    y=find(y);
	    if(x!=y){
		    fa[x]=y;
		    siz[y]+=siz[x];
		    if(siz[y]>=(n*n+1)/2){
			    cout<<w<<endl;
			    return 0;
		    }
	    }
	}
}
