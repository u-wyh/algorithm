#include<bits/stdc++.h>
using namespace std;

int dire[8][2]={{1,1},{1,-1},{-1,1},{-1,-1},{1,0},{0,1},{-1,0},{0,-1}};
int walk[4][2]={{1,0},{0,1},{-1,0},{0,-1}};

int main()
{
    int n,m;
    cin>>n>>m;
    int nums[n+1][m+1];
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            char c;
            cin>>c;
            if(c=='O')
                nums[i][j]=1;
            else
                nums[i][j]=0;
        }
    }
    while(true){
        int a,b,c,d;
        cin>>a>>b>>c>>d;
        if((a+b+c+d)==0)
            break;
        int cnt=0;
        for(int i=0;i<8;i++){
            int x=a+dire[i][0];
            int y=b+dire[i][1];
            while(x>0&&x<=n&&y>0&&y<=m&&nums[x][y]!=0){
                cnt++;
                nums[x][y]=2;
                x+=dire[i][0];
                y+=dire[i][1];
            }
        }
        if(cnt==0){
            cout<<"Poor Harry"<<endl;
            for(int i=1;i<=n;i++){
                for(int j=1;j<=m;j++){
                    if(nums[i][j]==2)
                        nums[i][j]=1;
                }
            }
            continue;
        }
        if(nums[c][d]==2){
            for(int i=1;i<=n;i++){
                for(int j=1;j<=m;j++){
                    if(nums[i][j]==2)
                        nums[i][j]=1;
                }
            }
            cout<<0<<endl;
            continue;
        }
        int dis[n+1][m+1];
        for(int i=0;i<=n;i++){
            for(int j=0;j<=m;j++){
                dis[i][j]=-1;
            }
        }
        struct node{
            int x,y;
        };
        queue<node>q;
        q.push({c,d});
        dis[c][d]=0;
        int f=0;
        while(!q.empty()){
            node u=q.front();
            q.pop();
            for(int i=0;i<4;i++){
                int x=u.x+walk[i][0];
                int y=u.y+walk[i][1];
                if(nums[x][y]==2){
                    cout<<(dis[u.x][u.y]+1)<<endl;
                    f=1;
                    break;
                }
                if(dis[x][y]!=-1&&x>0&&x<=n&&y>0&&y<=m&&nums[x][y]!=0){
                    dis[x][y]=dis[u.x][u.y]+1;
                    q.push({x,y});
                }
            }
        }
        if(!f)
            cout<<"Poor Harry"<<endl;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(nums[i][j]==2)
                    nums[i][j]=1;
            }
        }
        while(!q.empty()){
            q.pop();
        }
    }

    return 0;
}
