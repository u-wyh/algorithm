#include<iostream>
using namespace std;

int n,m;
int dp[1<<10][1<<10][3];
int nums[100];//以二进制的形式表示每一行的情况
int cnt[1<<10];//统计每个二进制分别有多少个1
int ans;
int ok[1<<10];
int cunt=1;//以上的两行表示可能的有效状态，即同一行不会有问题的状态  cunt是个数

int main()
{
    cin>>n>>m;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            char c;
            cin>>c;
            nums[i]<<=1;
            nums[i]+=(c=='H'?1:0);//表示h的时候是1否则是0
        }
        //cout<<nums[i]<<endl;
    }
    cnt[0]=0;
    for(int i=1;i<(1<<m);i++){
        int j=i&(-i);//表示最低位的1
        int k=i^j;//表示补集
        cnt[i]=cnt[k]+1;
        //cout<<cnt[i]<<' ';
    }
    //cout<<endl;
    for(int i=0;i<(1<<n);i++){
        if(((i<<1)|(i<<2)|(i>>1)|(i>>2))&i){
            continue;
        }
        ok[cunt++]=i;
    }
    //cout<<cunt<<endl;
    for(int i=1;i<cunt;i++){
        if(!(nums[0]&ok[i])){
            dp[0][ok[i]][0]=cnt[ok[i]];
        }
    }
    for(int i=1;i<cunt;i++){
        for(int j=1;j<cunt;j++){
            if((ok[i]&ok[j])||(ok[i]&nums[0])||(ok[j]&nums[1])){
                continue;
            }
            dp[ok[i]][ok[j]][1]=cnt[ok[i]]+cnt[ok[j]];
        }
    }
    for(int i=2;i<n;i++){
        for(int j=1;j<cunt;j++){
            if(nums[i-1]&ok[j]){
                continue;
            }
            for(int k=1;k<cunt;k++){
                if((nums[i]&ok[k])||(ok[j]&ok[k]))
                    continue;
                for(int u=1;u<cunt;u++){
                    if((nums[i-2]&ok[u])||(ok[u]&ok[j])||(ok[u]&ok[k]))
                        continue;
                    dp[ok[j]][ok[k]][i%3]=max(dp[ok[j]][ok[k]][i%3],dp[ok[u]][ok[j]][(i-1)%3]+cnt[ok[k]]);
                }
            }
        }
    }
    for(int i=1;i<cunt;i++){
        for(int j=1;j<cunt;j++){
            ans=max(ans,dp[ok[i]][ok[j]][(n-1)%3]);
        }
    }
    cout<<ans<<endl;
    return 0;
}