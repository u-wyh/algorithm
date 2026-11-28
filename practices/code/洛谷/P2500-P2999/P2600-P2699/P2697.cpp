// https://www.luogu.com.cn/problem/P2697
// 题意：给定由 G 和 R 组成的字符串，
// 求 G 和 R 数目相等的最长连续子串长度。
// 输出最长子串长度。
// 数据范围：字符串长度 <= 10^6。
// 难度评分：1200（洛谷分级换算）
// 算法标签：前缀和、map
#include<bits/stdc++.h>
using namespace std;
const int MAXN =1e6+5;

char str[MAXN];
int nums[MAXN];
int sum[MAXN];
map<int,int >M;
int ans=0;

int main()
{
    int i=1;
    while(cin>>str[i]&&str[i]!='\n'){
        if(str[i]=='G'){
            nums[i]=-1;
        }else{
            nums[i]=1;
        }
        i++;
    }
    cout<<i;
    int n=i-1;
    for(int i=1;i<=n;i++){
        sum[i]=nums[i]+sum[i-1];
        if(M.find(sum[i])!=M.end()){
            ans=max(ans,i-M.find(sum[i])->second+1);
        }
        else{
            M[sum[i]]=i;
        }
    }
    cout<<ans;
    return 0;
}
