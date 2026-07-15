
#include<iostream>
using namespace std;
#define MAX 105

int m,n,d=2;
char s[MAX];
int nums[MAX][MAX];
int walk[12][2]={{1,0},{-1,0},{2,0},{-2,0},{0,1},{0,-1},{0,2},{0,-2},{1,1},{1,-1},{-1,1},{-1,-1}};

void dfs(int i,int j){
    nums[i][j]=d;
    for(int k=0;k<12;k++){
        int x=i+walk[k][0],y=j+walk[k][1];
        if(x==0||y==0||x>n||y>m||nums[x][y]!=1){
            continue;
        }
        dfs(x,y);
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>s[j];
            if(s[j]=='-'){
                nums[i][j]=0;
            }
            if(s[j]=='#'){
                nums[i][j]=1;
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(nums[i][j]==1){
                dfs(i,j);
                d++;
            }
        }
    }
    cout<<d-2;
    return 0;
}
