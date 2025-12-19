#include<bits/stdc++.h>
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
