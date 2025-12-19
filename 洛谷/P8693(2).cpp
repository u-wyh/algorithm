#include<bits/stdc++.h>
using namespace std;

int walk[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
int n,k;
struct node {
	int x, y;//坐标
	int Time;//时间
	int size;//小明大小
};
bool vis[305][305];
int a[305][305];

bool check(int x, int y, int size){
	if(vis[x][y])
        return false;
	for(int i=x-size;i<=x+size;i++)
		for(int j=y-size;j<=y+size;j++)
			if(i < 1 || i > n || j < 1 || j > n || a[i][j])
				return false;
	return true;
}

int work(int Time){
	if(Time < k)
        return 2;
	else if(Time < 2 * k)
        return 1;
	else
        return 0;
}

void bfs(){
    queue<node>q;
    vis[3][3]=1;
    q.push({3,3,0,2});
    while(!q.empty()){
        node t=q.front();
        q.pop();
        if(t.x == n - 2 && t.y == n - 2){
            //到达终点，停止搜索
			cout << t.Time;
			return ;
		}
		if(t.size != 0)
            q.push({t.x, t.y, t.Time+1, work(t.Time+1)});//站着不动
		for(int i=0;i<4;i++)
		{
			int X = t.x + walk[i][0];
			int Y = t.y + walk[i][1];
			if(check(X, Y, t.size))//判断
			{
				vis[X][Y] = 1;
				q.push((node){X, Y, t.Time+1, work(t.Time+1)});
			}
		}
    }
}

int main()
{
    cin >> n >> k;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			char c;
			cin >> c;
			if(c == '*')
                a[i][j] = 1;
			else
                a[i][j] = 0;
		}
	}
	bfs();
    return 0;
}
