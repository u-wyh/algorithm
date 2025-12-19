#include<bits/stdc++.h>
using namespace std;

int n;
int death[1005][1005];
int t[1005][1005];
int T;
struct coord{
    int x,y;
};
queue<coord>Q;
int walk[4][2]={{1,0},{-1,0},{0,1},{0,-1}};

int main()
{
    cin>>T;
    while(T--){
        memset(death,0,sizeof(death)); // 初始化为0，表示尚未放置路障
        memset(t,-1,sizeof(t)); // 初始化为-1，表示尚未访问
        cin>>n;
        int x,y;
        for(int i=1;i<=2*n-2;i++){
            cin>>x>>y;
            death[x][y]=i; // 记录路障的放置时间
        }
        t[1][1]=0;
        Q.push({1,1});
        while(!Q.empty()){
            coord u=Q.front();
            Q.pop();
            int ux=u.x,uy=u.y,utime=t[ux][uy];
            if(ux == n && uy == n) { // 到达终点
                printf("Yes\n");
                goto next_test; // 跳到下一组测试数据
            }
            for(int k=0;k<4;k++){
                int x=ux+walk[k][0],y=uy+walk[k][1];
                if(x>0 && x<=n && y>0 && y<=n && t[x][y] == -1 && (utime+1 < death[x][y] || death[x][y] == 0)) {
                    // 检查是否越界，是否未访问过，以及在该位置放置路障之前能否到达
                    t[x][y]=utime+1;
                    Q.push({x,y});
                }
            }
        }
        printf("No\n");
    next_test:
        continue; // 实际上这里的continue是多余的，因为while循环会自动继续
    }
    return 0;
}
