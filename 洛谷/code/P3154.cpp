#include<bits/stdc++.h>
using namespace std;

int n;
int score[9];
int a,b;
int cnt1,cnt2;
int nums[9][9];

bool cmp(int a,int b){
    return a>b;
}

int dfs(int u,int v,int sum){
    if(cnt1>a||cnt2>b){
        return 0;
    }
    if(u==n+1){
        return 1;
    }
    int ans=0;
    if(v==n+1){
        if(sum!=score[u]){
            return 0;
        }
        int tmp=0;
        for(int i=1;i<=u;i++){
            tmp+=nums[u+1][i];
        }
        ans+=dfs(u+1,u+2,tmp);
    }
    else{
        if(sum>score[u]){
            return 0;
        }
        nums[u][v]=3,nums[v][u]=0,cnt1++;
        ans+=dfs(u,v+1,sum+3);
        nums[u][v]=0,nums[v][u]=3;
        ans+=dfs(u,v+1,sum);
        cnt1--,cnt2++,nums[u][v]=1,nums[v][u]=1;
        ans+=dfs(u,v+1,sum+1);
    }
    return ans;
}

int main()
{
    cin>>n;
    int sum=0;
    for(int i=1;i<=n;i++){
        cin>>score[i];
        sum+=score[i];
    }
    sort(score+1,score+n+1,cmp);
    b=(n*(n-1))/2*3-sum;
    a=(n*(n-1))/2-b;
    cout<<a<<' '<<b<<endl;
    cout<<dfs(1,2,0);
    return 0;
}