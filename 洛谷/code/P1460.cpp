// https://www.luogu.com.cn/problem/P1460
// 题意：有 v 种维生素和 g 种饲料，给每种维生素的最低需要量，以及每种饲料含有的各类维生素量。
// 每种饲料至多选一次，求覆盖所有需求的最少种数。
// 输出种数和升序编号，多解取字典序最小。
// 数据范围：1 ≤ v ≤ 25，1 ≤ g ≤ 15，含量和需求在 [1,1000]，保证有解。
// 算法标签：深度优先搜索、回溯、剪枝

#include<bits/stdc++.h>
using namespace std;

int m,n;
int need[30];
int nums[20][30];
int anscnt=100,ans[30];
int precnt=0,prepare[30];
int t=0;
int sum[30];

void dfs(int x){
    if(precnt>=anscnt||x>n+1){
        return;
    }
    if(t==m){
        //cout<<666<<endl;
        for(int i=1;i<=precnt;i++){
            ans[i]=prepare[i];
        }
        anscnt=precnt;
    }
    for(int i=1;i<=m;i++){
        sum[i]+=nums[x][i];
        if(sum[i]>=need[i]&&(sum[i]-nums[x][i]<need[i])){
            t++;
        }
    }
//    for(int i=1;i<=m;i++){
//        cout<<sum[i]<<' ';
//    }
//    cout<<t<<' ';
//    cout<<endl;
    prepare[++precnt]=x;
    dfs(x+1);
    //cout<<"no"<<endl;
    for(int i=1;i<=m;i++){
        sum[i]-=nums[x][i];
        if((sum[i]+nums[x][i]>=need[i])&&sum[i]<need[i]){
            t--;
        }
    }
    precnt--;
    dfs(x+1);
}

int main()
{
    cin>>m;
    for(int i=1;i<=m;i++){
        cin>>need[i];
    }
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>nums[i][j];
        }
    }
    dfs(1);
    cout<<anscnt<<' ';
    for(int i=1;i<=anscnt;i++){
        cout<<ans[i]<<' ';
    }
    return 0;
}
