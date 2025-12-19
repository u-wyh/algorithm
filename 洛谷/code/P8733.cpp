#include<bits/stdc++.h>
using namespace std;

int n,D;
struct node{
    int x,y;
    int i;
}nums[20];
double graph[20][20];
double dp[1<<20][20]={0};

void build(){
    for(int i=0;i<(n-1);i++){
        for(int j=i+1;j<n;j++){
            double k=sqrt(pow(nums[i].x-nums[j].x,2)+pow(nums[i].y-nums[j].y,2));
            if(k>=D)
                k=DBL_MAX;
            graph[i][j]=k;
            graph[j][i]=k;
        }
    }
}

double dfs(int status,int now){
    //cout<<666<<endl;
    if(status==((1<<n)-1)){
        //cout<<777<<endl;
        return graph[now][0];
    }
    if(dp[status][now]!=0){
        //cout<<888<<endl;
        return dp[status][now];
    }
    double ans=1e9;
    for(int i=0;i<n;i++){
        //cout<<999<<endl;
        if(((status&(1<<i))==0)&&graph[now][i]<=D){
            //cout<<111<<endl;
            ans=min(ans,graph[now][i]+dfs(status|(1<<i),i));
        }
    }
    dp[status][now]=ans;
    return ans;
}

int main()
{
    cin>>n>>D;
    for(int i=0;i<n;i++){
        cin>>nums[i].x>>nums[i].y;
        nums[i].i=i;
    }
    build();
    for(int i = 0 ; i < n ; i++)
		for(int j = 0 ; j < n ; j++)
			for(int k = 0 ; k < n ; k++)
				graph[i][j] = min(graph[i][j] , graph[i][k] + graph[k][j]) ;
//    for(int i=0;i<n;i++){
//        for(int j=0;j<n;j++){
//            printf("%5.2lf",graph[i][j]);
//        }
//        cout<<endl;
//    }
    for(int i=0;i<(1<<n);i++){
        for(int j=0;j<n;j++){
            dp[i][j]=0;
        }
    }
    printf("%.2lf\n",dfs(1,0));
//    for(int i=0;i<(1<<n);i++){
//        for(int j=0;j<n;j++){
//            printf("%5.2lf",dp[i][j]);
//        }
//        cout<<endl;
//    }
    return  0;
}
