// https://www.luogu.com.cn/problem/P3663
// 题意：输入网格边长 N、奶牛数 K、分隔相邻格子的道路数 R，R 条道路两侧的相邻坐标，以及 K 头奶牛所在格子坐标。
// 奶牛可四联通移动到相邻格，但不想穿过道路；若两头奶牛互相拜访时必须至少穿过一条道路，则称为「远距离」对。
// 输出远距离奶牛对的数量。
// 数据范围：2 <= N <= 100，1 <= K <= 100，K <= N^2。
#include<bits/stdc++.h>
// 算法标签：深度优先搜索
using namespace std;

int n,k,r;
int nums[105][105];
int edge[105][105][4];
int color[105][105];
int cnt,all;
int walk[4][2]={{1,0},{-1,0},{0,1},{0,-1}};//表示南北东西
int b[105][105];
vector<int>vec;

void dfs(int x,int y){
	if(x<1||y<1||x>n||y>n){
		return;
	}
	if(color[x][y]!=-1){
		return;
	}
    color[x][y]=cnt;
	if(b[x][y]==1){
		all++;
	}
	for(int i=0;i<4;i++){
		if(edge[x][y][i]==1){
			continue;
		}
		int xx=x+walk[i][0];
		int yy=y+walk[i][1];
		dfs(xx,yy);
	}
}

int main()
{
    cin>>n>>k>>r;
    for(int i=1;i<=r;i++){
        int x,y,x1,y1;
        cin>>x>>y>>x1>>y1;
        if(y==y1){
            edge[min(x,x1)][y][0]=1;
            edge[max(x,x1)][y][1]=1;
        }
        else if(x==x1){
            edge[x][min(y,y1)][2]=1;
            edge[x][max(y,y1)][3]=1;
        }
    }
    for(int i=1;i<=k;i++){
        int x,y;
        cin>>x>>y;
        b[x][y]=1;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            color[i][j]=-1;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(color[i][j]==-1){
                all=0;
                cnt++;
                dfs(i,j);
                vec.push_back(all);
            }
        }
    }
    int ans=0;
    for(int i=0;i<vec.size();i++){
        for(int j=i+1;j<vec.size();j++){
            ans+=vec[i]*vec[j];
        }
    }
    cout<<ans;
    return 0;
}
