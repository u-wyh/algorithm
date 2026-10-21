// https://www.luogu.com.cn/problem/P6000
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n;
char s[MAXN];
int dp[MAXN][26];

bool check(){
    stack<int>stk;
    for(int i=1;i<=n;i++){
        int v=s[i]-'a';
        if(stk.empty()){
            stk.push(v);
        }
        else if(stk.top()==v){
            stk.pop();
        }
        else{
            stk.push(v);
        }
    }
    return stk.empty();
}

void solve(int l,int r){
    if(l>r){
        return ;
    }
    if(l+1==r){
        cout<<"()";
        return ;
    }
    int p=dp[r][s[l]-'a'];
    cout<<"(";
    solve(l+1,p-1);
    cout<<")";
    solve(p+1,r);
}

void compute(){
    for(int i=1;i<=n;i++){
        int v=s[i]-'a';
        int p=dp[i-1][v];
        if(p){
            for(int j=0;j<26;j++){
                dp[i][j]=dp[p-1][j];
            }
        }
        dp[i][v]=i;
    }
}

int main()
{
    scanf("%s",s+1);
    n=strlen(s+1);
     
    if(!check()){
        cout<<-1<<endl;
        return 0;
    }

    compute();

    solve(1,n);
    return 0;
}