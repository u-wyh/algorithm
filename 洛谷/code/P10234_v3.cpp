#include <bits/stdc++.h>
#define big long long
using namespace std;
struct Node{
	big x,y;
};
big T,n,m,to[4][2]={1,0,0,1,-1,0,0,-1};
char path[5]={'D','R','U','L'};
big ways[3004][3004],dis[3004][3004];
bool vis[3004][3004],mapp[3004][3004];
void bfs(big sx,big sy)
{
	queue <Node> q;
	q.push(Node({sx,sy}));
	dis[sx][sy] = 0;
	vis[sx][sy] = 1;
	while(!q.empty())
	{
		Node pos=q.front();
		q.pop();
		if(pos.x == n && pos.y == m)
		{
			printf("%lld\n",dis[n][m]);
            stack <big> st;
            big ex = n,ey = m;
            while((ex != 1) || (ey != 1))
            {
                st.push(ways[ex][ey]);
                big back = (ways[ex][ey]+2)%4;
                ex += to[back][0], ey += to[back][1]; // 回溯
            }
            while(!st.empty())
            {
                putchar(path[st.top()]);
                st.pop();
            }
            putchar('\n');
			return;
		}
		big ax = pos.x, ay = pos.y;
		for(big i = 0;i < 4;i++)
		{
			big nowx = ax+to[i][0], nowy = ay+to[i][1];
			if((vis[nowx][nowy] == 0) && (mapp[nowx][nowy] != mapp[ax][ay]) && (1 <= ax && ax <= n && ay >= 1 && ay <= m))
            {
                ways[nowx][nowy] = i;
				dis[nowx][nowy] = dis[ax][ay]+1;
				vis[nowx][nowy] = 1;
                q.push(Node({nowx,nowy}));
            }
		}
	}
    printf("-1\n");
}
int main()
{
    scanf("%lld\n",&T);
    while(T--)
    {
        scanf("%lld %lld\n",&n,&m);
        for(big i = 0;i <= n;i++)
        {
            for(big j = 0;j <= m;j++)
            {
                vis[i][j] = 0;
                dis[i][j] = ways[i][j] = 0;
            }
        }
	    for(big i = 1;i <= n;i++)
	    {
	    	for(big j = 1;j <= m;j++)
            {
                char ch = getchar();
				while(ch != '0' && ch != '1')
                {
                    ch = getchar();
                }
				mapp[i][j] = ch-'0';
            }
	    }
        if((mapp[n-1][m] == mapp[n][m]) && (mapp[n][m-1] == mapp[n][m])) // 小小优化
        {
            printf("-1\n");
            continue;
        }
        bfs(1,1);
    }
	return 0;
}

