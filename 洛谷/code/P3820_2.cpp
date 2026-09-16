#include<bits/stdc++.h>
using namespace std;
const int N = 1e6+500;

vector<int> a[N],f[N];
char s[N];
int n,m,Q,tot,fa[N<<1],siz[N<<1];
int mvx[4]={0,0,1,-1},mvy[4]={1,-1,0,0};

int newnode(){
	fa[++tot]=tot;
	siz[tot]=1;
	return tot;
}
bool valid(int x,int y){
	return 1<=x&&x<=n&&1<=y&&y<=m;
}
int get(int x){
	if(fa[x]==x)return x;
	return fa[x]=get(fa[x]);
}
void merge(int x,int y){
	x=get(x);y=get(y);
	if(x==y)return;
	fa[x]=y;
	siz[y]+=siz[x];siz[x]=0;
}
void inital(){
	for(int i=0;i<=n;i++){
		 a[i].resize(m+3,0);//Ç§Íò±ð¿ªm+1
		f[i].resize(m+3,0);
	}
}
void change(int x,int y){
	a[x][y]^=1;
	if(!a[x][y])//delete
		siz[get(f[x][y])]--;
	else{       //new lake
		f[x][y]=newnode();
		for(int k=0;k<4;k++){
			int xx=x+mvx[k],yy=y+mvy[k];
			if( !valid(xx,yy) || a[x][y]!=a[xx][yy])continue;
			merge(f[xx][yy],f[x][y]);
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);tot=0;
	inital();
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		for(int j=1;j<=m;j++){
			a[i][j] = (s[j]=='.');
			if(a[i][j]){
				f[i][j]=newnode();
				if(a[i][j]==a[i-1][j])merge(f[i][j],f[i-1][j]);
				if(a[i][j]==a[i][j-1])merge(f[i][j],f[i][j-1]);
			}
		}
	}
	scanf("%d",&Q);
	while(Q--){
		int op,w;
		scanf("%d%d",&op,&w);
		int ans=0,ret=1;
		for(int i=1,x,y;i<=w;i++){
			scanf("%d%d",&x,&y);
			if(op==1){
				if(a[x][y]&&siz[get(f[x][y])]>ans)
					ans=siz[get(f[x][y])],ret=i;
			}
			else change(x,y);
		}
		if(op==1)
			printf("%d\n",ret);
	}
	return 0;
}
