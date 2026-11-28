// https://www.luogu.com.cn/problem/P10719
// 题意：给 n 行 m 列的 01 网格，1 表示黑格。
// 找一个包含至少 k 个黑格的矩形，使矩形面积尽可能小。
// 输出最小面积，找不到输出 0。
// 数据范围：1 ≤ n,m ≤ 100，1 ≤ k ≤ n×m。
// 难度评分：1300（洛谷分级换算）
// 算法标签：二分答案、二维前缀和

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;

int nums[MAXN][MAXN];
char c;
int n,m,k;

bool check(int x){
    for(int l=n;l>0;l--){
        for(int w=x/l;w>0;w--){
            for(int i=l;i<=n;i++){
                for(int j=w;j<=m;j++){
                    if(nums[i][j]+nums[i-l][j-w]-nums[i][j-w]-nums[i-l][j]>=k)
                        return true;
                }
            }
        }
    }
    return false;
}

int main()
{
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>c;
            nums[i][j]=c-'0';
            //printf("%3d",nums[i][j]);
        }
        //cout<<endl;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            nums[i][j]+=nums[i][j-1]+nums[i-1][j]-nums[i-1][j-1];
            //printf("%3d",nums[i][j]);
        }
        //cout<<endl;
    }
    if(k>nums[n][m]){
        cout<<0;
        return 0;
    }
    int l=k,r=n*m,mid,ans=r;
    while(l<=r){
        mid=(l+r)/2;
        if(check(mid)){
            ans=mid;
            r=mid-1;
        }else{
            l=mid+1;
        }
    }
    cout<<ans;
    return 0;
}
