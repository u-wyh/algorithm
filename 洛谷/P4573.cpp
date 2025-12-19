#include<cstdio>
#include<queue>
#include<iostream>
#include<cstring>
using namespace std;
inline int read(){
	int ans=0,f=1;char chr=getchar();
	while(!isdigit(chr)){if(chr=='-') f=-1;chr=getchar();}
	while(isdigit(chr)){ans=(ans<<3)+(ans<<1)+chr-48;chr=getchar();}
	return ans*f;
}char h[20][20],l[20][20];int num[15][15],bh[15][15],bl[15][15];
inline int get(int x,int y){return (x-1)/3*3+(y-1)/3+1;}int ANS[10][10];
inline int check(int x,int y,int z){if(bh[x][z]||bl[y][z]||num[get(x,y)][z]) return 0;return 1;}
inline void init(int x,int y,int z) {num[get(x,y)][z]=bh[x][z]=bl[y][z]=1;}
inline void outit(int x,int y,int z){num[get(x,y)][z]=bh[x][z]=bl[y][z]=0;}
inline int check_lr(int x,int y,int z){
	if(y%3==1)return 1;
	if(h[x][y-1]=='<') return ANS[x][y-1]<z;
	else return ANS[x][y-1]>z;
}
inline int check_ud(int x,int y,int z){
	if(x%3==1)return 1;
	if(l[x-1][y]=='v') return ANS[x-1][y]>z;
	else return ANS[x-1][y]<z;
}
inline void OUTPUT(){for(int i=1;i<=9;i++,puts(""))for(int j=1;j<=9;j++) printf("%d ",ANS[i][j]);}
void dfs(int x,int y){
	if(x==10){OUTPUT();exit(0);}
	if(y==10){dfs(x+1,1);return;}
	for(int i=1;i<=9;i++)
		if(check(x,y,i)&&check_lr(x,y,i)&&check_ud(x,y,i))
			ANS[x][y]=i,init(x,y,i),dfs(x,y+1),outit(x,y,i);
//init用来标记这个格子用过了，outit用来回溯，取消标记
}int main(){
	for(int i=1;i<=9;i++) {if(i%3==0) continue;cin>>h[1][i];}
	for(int i=1;i<=9;i++) cin>>l[1][i];
	for(int i=1;i<=9;i++) {if(i%3==0) continue;cin>>h[2][i];}
	for(int i=1;i<=9;i++) cin>>l[2][i];
	for(int i=1;i<=9;i++) {if(i%3==0) continue;cin>>h[3][i];}
	for(int i=1;i<=9;i++) {if(i%3==0) continue;cin>>h[4][i];}
	for(int i=1;i<=9;i++) cin>>l[4][i];
	for(int i=1;i<=9;i++) {if(i%3==0) continue;cin>>h[5][i];}
	for(int i=1;i<=9;i++) cin>>l[5][i];
	for(int i=1;i<=9;i++) {if(i%3==0) continue;cin>>h[6][i];}
	for(int i=1;i<=9;i++) {if(i%3==0) continue;cin>>h[7][i];}
	for(int i=1;i<=9;i++) cin>>l[7][i];
	for(int i=1;i<=9;i++) {if(i%3==0) continue;cin>>h[8][i];}
	for(int i=1;i<=9;i++) cin>>l[8][i];
	for(int i=1;i<=9;i++) {if(i%3==0) continue;cin>>h[9][i];}
	dfs(1,1);
	return 0;
}
