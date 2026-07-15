#include<bits/stdc++.h>
using namespace std;

int dire[1005];
int walk[4][2]={{0,1},{0,-1},{1,0},{-1,0}};
int n,m,Q;
int sti,stj;
int in[55][55];
int nums[55][55];
queue<pair<int,int>>q;
queue<pair<int,int>>t;

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            char c;
            cin>>c;
            if(c=='*'){
                sti=i;
                stj=j;
                nums[i][j]=1;
            }
            else if(c=='.'){
                nums[i][j]=1;
            }
            //cout<<nums[i][j]<<' ';
        }
        //cout<<endl;
    }
    cin>>Q;
    for(int i=1;i<=Q;i++){
        string str;
        cin>>str;
        if(str=="NORTH")
            dire[i]=3;
        else if(str=="SOUTH")
            dire[i]=2;
        else if(str=="WEST")
            dire[i]=1;
        else
            dire[i]=0;
        //cout<<dire[i]<<endl;
    }
    q.push({sti,stj});
    in[sti][stj]=true;
    for(int i=1;i<=Q;i++){
        //cout<<q.size()<<' '<<t.size()<<endl;
        while(!q.empty()){
            int x=q.front().first;
            int y=q.front().second;
            q.pop();
            while(true){
                int ux=x+walk[dire[i]][0];
                int uy=y+walk[dire[i]][1];
                if(nums[ux][uy]==0||in[ux][uy]==i||x>n||y>m||x<=0||y<=0){
                    break;
                }
                t.push({ux,uy});
                in[ux][uy]=i;
                x=ux;
                y=uy;
            }
        }
        //cout<<q.size()<<' '<<t.size()<<endl;
        swap(q,t);
        //cout<<q.size()<<' '<<t.size()<<endl<<endl;
    }
    while(!q.empty()){
        int x=q.front().first;
        int y=q.front().second;
        q.pop();
        nums[x][y]=2;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(nums[i][j]==0){
                cout<<"X";
            }
            else if(nums[i][j]==1){
                cout<<".";
            }
            else
                cout<<"*";
        }
        cout<<endl;
    }
    return 0;
}
