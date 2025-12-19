#include<bits/stdc++.h>
using namespace std;

int stxm,stym,stxg,styg,enx,eny;
int vis[32][32][32][32];
int n,m;
int arr[32][32];
int walk[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
struct node{
    int gx,gy,mx,my;
};
queue<node>q;

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            char c;
            cin>>c;
            if(c!='#'){
                if(c=='X'){
                    arr[i][j]=-1;
                }
                else {
                    arr[i][j]=1;
                    if(c=='G'){
                        stxg=i,styg=j;
                    }
                    else if(c=='M'){
                        stxm=i,stym=j;
                    }
                    else if(c=='T'){
                        enx=i,eny=j;
                    }
                }
            }
        }
    }
    //cout<<stxg<<' '<<styg<<' '<<stxm<<' '<<stym<<' '<<enx<<' '<<eny<<endl;
    //system("pause");
    q.push({stxg,styg,stxm,stym});
    vis[stxg][styg][stxm][stym]=1;
    while(!q.empty()){
        node u=q.front();
        q.pop();
        int x1=u.gx,y1=u.gy,x2=u.mx,y2=u.my;
        if(x1==x2&&y1==y2&&x1==enx&&y1==eny){
            break;
        }
        //cout<<x1<<' '<<y1<<' '<<x2<<' '<<y2<<endl;
        //system("pause");
        for(int i=0;i<4;i++){
            int x3=x1+walk[i][0],y3=y1+walk[i][1];
            int x4=x2+walk[i][0],y4=y2-walk[i][1];
            if(vis[x3][y3][x4][y4]||arr[x3][y3]==-1||arr[x4][y4]==-1||x3>n||x3<=0||x4>n||x4<=0||y3>m||y3<=0||y4>m||y4<=0||(arr[x3][y3]==0&&arr[x4][y4]==0)){
                continue;
            }
            if(arr[x3][y3]==0){
                x3=x1,y3=y1;
            }
            if(arr[x4][y4]==0){
                x4=x2,y4=y2;
            }
            if(vis[x3][y3][x4][y4]){
                continue;
            }
            vis[x3][y3][x4][y4]=vis[x1][y1][x2][y2]+1;
            q.push({x3,y3,x4,y4});
        }
    }
    if(vis[enx][eny][enx][eny]){
        cout<<(vis[enx][eny][enx][eny]-1)<<endl;
    }
    else{
        cout<<"no"<<endl;
    }
    return 0;
}
