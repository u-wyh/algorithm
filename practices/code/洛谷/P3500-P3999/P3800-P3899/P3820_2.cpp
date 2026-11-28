// https://www.luogu.com.cn/problem/P3820
// 题意：第一行输入行列数 N, M，
// 接下来 N 行每行 M 个字符描述地形（. 为温泉，* 为土），
// 随后输入操作数 Q 及 Q 行操作。
// 操作 1 w x1 y1 ... xw yw：在指定的 w 个位置中，
// 求各自所在四连通温泉块大小最大的位置编号
// （若为土则大小为 0，并列取输入靠前的编号
// 1..w）。
// 操作 2 w x1 y1 ... xw yw：
// 按顺序翻转这 w 个位置的地形（. 变 * 或 * 变 .），
// 且题目保证将温泉变土时不会把一个连通区域分割。
// 对每个操作 1 输出一行答案。
// 数据范围：对于 100% 的数据，
// 1 <= N*M, Q <= 10^6，sum
// w <= 10^6，w >= 1。
// 难度评分：1800（洛谷分级换算）
// 算法标签：并查集
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
		 a[i].resize(m+3,0);//千万别开m+1
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
