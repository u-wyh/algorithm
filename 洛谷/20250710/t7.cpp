#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e3+5;

int n,m,l,r;
char s[MAXN][MAXN];
int t[MAXN][MAXN];
queue<pair<int,int>>q;

int walk[8][2]={{1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}};

inline bool check(int x,int y){
    if(x>n||x<=0||y>m||y<=0||s[x][y]=='0'||t[x][y]!=-1){
        return false;
    }
    return true;
}

void prepare(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            t[i][j]=-1;
        }
    }
    while(!q.empty()){
        q.pop();
    }
}

void compute(){
    t[n][m]=0;
    q.push({n,m});
    while(!q.empty()){
        if(t[1][1]!=-1){
            break;
        }
        int x=q.front().first;
        int y=q.front().second;
        q.pop();
        for(int i=0;i<8;i++){
            int nx=x+walk[i][0];
            int ny=y+walk[i][1];
            if(check(nx,ny)){
                t[nx][ny]=t[x][y]+1;
                q.push({nx,ny});
            }
        }
    }
}

int main()
{
    int T;
    cin>>T;
    while(T--){
        int n,m;
        cin>>n>>m>>l>>r;
        // cout<<n<<' '<<m<<' '<<l<<' '<<r<<endl;
        for(int i=1;i<=n;i++){
            scanf("%s",s[i]+1);
        }
        prepare();
        compute();
        // cout<<t[1][1]<<endl;
        if(t[1][1]==-1){
            cout<<t[1][1]<<endl;
            continue;
        }
        if(l!=r){
            cout<<(t[1][1]+r-1)/r<<endl;
        }
        else{
            if(l%2==0){
                cout<<(t[1][1]+r-1)/r<<endl;
            }
            else{
                cout<<(t[1][1]/r+1-((t[1][1]%r)%2))<<endl;
            }
        }
    }
    return 0;
}
/*
3
5 5
2 3
10000
01000
00110
11001
11111
7 8
3 3
10101000
01010100
10000100
01000010
00100100
00011010
00000001
7 8
4 4
10101000
01010100
10000100
01000010
00100100
00011010
00000001
*/