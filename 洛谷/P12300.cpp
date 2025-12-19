#include<bits/stdc++.h>
using namespace std;
const int MAXN = 305;
const int INF = 1e9;

int n;
int ans;
int nums[MAXN];
int pre[MAXN];
int col[MAXN];
int dp[MAXN][MAXN][3];
int sta[MAXN][2];
int top;

void compute(int l,int r,int c){
    if(l==r){
        return ;
    }
    int len=r-l+1;
    for(int i=l;i<=r;i++){
        dp[i][i][col[i]]=0;
    }
    for(int k=2;k<=len;k++){
        for(int i=l;i<=r-k+1;i++){
            int j=i+k-1;
            for(int t=i;t<j;t++){
                dp[i][j][0]=min(dp[i][j][0],dp[i][t][2]+dp[t+1][j][2]+pre[j]-pre[i-1]);
                dp[i][j][1]=min(dp[i][j][1],dp[i][t][0]+dp[t+1][j][0]+pre[j]-pre[i-1]);
                dp[i][j][2]=min(dp[i][j][2],dp[i][t][1]+dp[t+1][j][1]+pre[j]-pre[i-1]);
            }
        }
    }
    ans+=dp[l][r][c];
}

void push(int col,int pos){
    if(top==0||sta[top][0]!=col){
        sta[++top][0]=col;
        sta[top][1]=pos;
        return ;
    }
    top--;
    push((col+1)%3,pos);
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
    }
    for(int i=1;i<=n;i++){
        pre[i]=pre[i-1]+nums[i];
    }
    for(int i=1;i<=n;i++){
        cin>>col[i];
    }
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            dp[i][j][0]=dp[i][j][1]=dp[i][j][2]=INF;
        }
    }
    for(int i=1;i<=n;i++){
        push(col[i],i);
    }
    cout<<top<<' ';
    int l=1;
    for(int i=1;i<=top;i++){
        compute(l,sta[i][1],sta[i][0]);
        l=sta[i][1]+1;
    }

    int ans1=ans;
    ans=0;
    top=0;
    for(int i=1;i<=n/2;i++){
        swap(col[i],col[n-i+1]);
        swap(nums[i],nums[n-i+1]);
    }
    for(int i=1;i<=n;i++){
        pre[i]=pre[i-1]+nums[i];
    }
    
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            dp[i][j][0]=dp[i][j][1]=dp[i][j][2]=INF;
        }
    }
    for(int i=1;i<=n;i++){
        push(col[i],i);
    }
    l=1;
    for(int i=1;i<=top;i++){
        compute(l,sta[i][1],sta[i][0]);
        l=sta[i][1]+1;
    }
    ans=min(ans,ans1);
    cout<<ans<<endl;
    return 0;
}