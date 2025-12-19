#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100000;

int n;
int nums[10][6];
int tmp[6];
int vis[MAXN];

int fun(int *nums){
    int ans=0;
    for(int i=1;i<=5;i++){
        ans=ans*10+nums[i];
    }
    return ans;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=5;j++){
            cin>>nums[i][j];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=9;j++){
            //转动幅度
            for(int p=1;p<=5;p++){
                //转动位置
                for(int k=1;k<=5;k++){
                    tmp[k]=nums[i][k];
                }
                tmp[p]=(tmp[p]+j)%10;
                vis[fun(tmp)]++;
            }
            for(int p=1;p<=4;p++){
                for(int k=1;k<=5;k++){
                    tmp[k]=nums[i][k];
                }
                tmp[p]=(tmp[p]+j)%10;
                tmp[p+1]=(tmp[p+1]+j)%10;
                vis[fun(tmp)]++;
            }
        }
    }
    int cnt=0;
    for(int i=0;i<=99999;i++){
        if(vis[i]==n){
            cnt++;
        }
    }
    cout<<cnt<<endl;
    return 0;
}