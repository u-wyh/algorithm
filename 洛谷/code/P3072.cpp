// https://www.luogu.com.cn/problem/P3072
// 题意：输入干草堆数量 n，以及这 n 个干草堆在网格中的坐标 (x, y)。
// 所有干草堆四连通组成一个大连通块，内部可能包围若干封闭的空白「洞」。
// 求整个连通块外部的周长（不包含内部「洞」的边界）。
// 输出一个整数表示周长 p。
// 数据范围：1 <= n <= 5*10^4，1 <= x, y <= 10^6。
#include <iostream>
#include <cstdio>
#include <queue>
#include <algorithm>
#include <map>
// 算法标签：广度优先搜索
using namespace std;

int fx[4] = {0,1,0,-1};
int fy[4] = {1,0,-1,0};
int pdx[8] = {-1,0,1,1, 1, 0,-1,-1};
int pdy[8] = { 1,1,1,0,-1,-1,-1, 0};
int N;
int Startx, Starty;
map<pair<int,int>, int> vist;
map<pair<int,int>, int> grass;
int x,y;
int maxx,maxy;
int minx = 1e6, miny = 1e6;
long long Answer;

bool DisNice(int x, int y) {//判断该点是否“贴着”连通块
	for(int i = 0 ; i < 8 ; i++) {
		int gx = x+pdx[i];
		int gy = y+pdy[i];
		if(grass[{gx,gy}] != 0)
			return false;
	}
	return true;
}

void BFS()//广搜——核心代码
{
	queue<pair<int,int> > Q;
	while(!Q.empty()) Q.pop();
	Q.push({Startx+1, Starty});
	while(!Q.empty()) {
		int X = Q.front().first;
		int Y = Q.front().second;
		Q.pop();

		if( vist[{X,Y}] != 0 || grass[{X,Y}] != 0)
			continue;
		vist[{X,Y}] = 1;
		for(int i = 0 ; i< 4 ; i++) {
			x = X+fx[i];
			y = Y+fy[i];
			if(grass[{x,y}] != 0) {
				Answer++;
			}
			if( vist[{x,y}] != 0 || grass[{x,y}] != 0 || DisNice(x,y)) {
				continue;
			} else {
				Q.push({x,y});
			}
		}
	}
}

int main()
{
	scanf("%d", &N);
	for(int i = 1 ; i<= N ; i++) {
		scanf("%d%d", &x, &y);
		grass[{x,y}] = 1;
		if(Startx < x) {
			Startx = x;
			Starty = y;
		}
	}
	BFS();
	printf("%d\n", Answer);
	return 0;
}
