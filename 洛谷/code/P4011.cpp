#include<bits/stdc++.h>
using namespace std;

int n,m,p,k,s;
int dp[11][11][1<<11];//用于确定拥有钥匙状态
//int nums[11][11];//用于储存钥匙
struct node{
    int x,y,status;
};
queue<node>q;
int edge[22][11];
int walk[4][2]={{1,0},{-1,0},{0,1},{0,-1}};//下上右左
vector<int>nums[11][11];

int main()
{
    cin>>n>>m>>p>>k;
    for(int i=1;i<=k;i++){
        int x,y,xx,yy,opt;
        cin>>x>>y>>xx>>yy>>opt;
        if(opt==0)
            opt=-1;
        if(x!=xx){
            edge[2*min(x,xx)][y]=opt;
        }
        else{
            edge[2*x-1][min(y,yy)]=opt;
        }
    }
    cin>>s;
    for(int i=1;i<=s;i++){
        int x,y,opt;
        cin>>x>>y>>opt;
        nums[x][y].push_back(opt);
    }
//    cout<<"----------------------------------------------------------------"<<endl;
//    for(int i=1;i<=2*n-1;i++){
//        for(int j=1;j<=m;j++){
//            cout<<edge[i][j]<<' ';
//        }
//        cout<<endl;
//    }
//    cout<<"----------------------------------------------------------------"<<endl;
//    for(int i=1;i<=n;i++){
//        for(int j=1;j<=m;j++){
//            cout<<nums[i][j].size()<<' ';
//        }
//        cout<<endl;
//    }
//    cout<<"----------------------------------------------------------------"<<endl;
    //路径以及钥匙位置判断检测
    q.push({1,1,1});
    dp[1][1][0]=1;//最后的结果要减1
    dp[1][1][1]=1;
    while(!q.empty()){
        //cout<<666<<endl;
        node u=q.front();
        q.pop();
        if(u.x==n&&u.y==m){
            cout<<dp[u.x][u.y][u.status]-1;
            return 0;
            //输出结果
        }
        for(int i=0;i<4;i++){
            //cout<<555<<endl;
            int x=u.x+walk[i][0];
            int y=u.y+walk[i][1];
            int now=u.status;
            if(x<=0||x>n||y<=0||y>m)
                continue;//越界
            if(i==0){
                if(edge[2*u.x][u.y]==-1)
                    continue;//墙
                //cout<<111<<' '<<i<<endl;
                if((u.status&(1<<edge[2*u.x][u.y]))==0)
                    continue;//没有钥匙的门
                //cout<<222<<' '<<i<<endl;
            }
            else if(i==1){
                if(edge[2*x][u.y]==-1)
                    continue;//墙
                //cout<<111<<' '<<i<<endl;
                if((u.status&(1<<edge[2*x][u.y]))==0)
                    continue;//没有钥匙的门
                //cout<<222<<' '<<i<<endl;
            }
            else if(i==2){
                if(edge[2*u.x-1][u.y]==-1)
                    continue;//墙
                //cout<<111<<' '<<i<<endl;
                if((u.status&(1<<edge[2*u.x-1][u.y]))==0)
                    continue;//没有钥匙的门
                //cout<<222<<' '<<i<<endl;
            }
            else if(i==3){
                if(edge[2*u.x-1][y]==-1)
                    continue;//墙
                //cout<<111<<' '<<i<<endl;
                if((u.status&(1<<edge[2*u.x-1][y]))==0)
                    continue;//没有钥匙的门
                //cout<<222<<' '<<i<<endl;
            }//表示走不通
            //cout<<888<<endl;
            for(int z=0;z<nums[x][y].size();z++){
                //cout<<u.x<<' '<<u.y<<' '<<x<<' '<<y<<' '<<z<<endl;
                now|=(1<<nums[x][y][z]);
            }
            if(dp[x][y][now]==0){
                //cout<<777<<endl;
                dp[x][y][now]=dp[u.x][u.y][u.status]+1;
                q.push({x,y,now});
            }
        }
    }
    cout<<-1<<endl;
    return 0;
}
