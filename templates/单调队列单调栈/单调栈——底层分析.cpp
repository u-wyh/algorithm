// 给你一个 m * n 的矩阵 mat，其中只有0和1两种值
// 请你返回 元素全部都是1的 子矩阵 的 最大面积的3倍
#include<bits/stdc++.h>
using namespace std;

int st[10000];
int n,m,r=0;
int nums[1000][1000],L;
char s[1000][1000];
int ans=0;

int main()
{
    cin>>n>>m;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>s[i][j];
            if(s[i][j]=='F')
                nums[i][j]=1;
            if(s[i][j]=='R')
                nums[i][j]=0;
            if(i!=0){
                if(nums[i][j]!=0)
                    nums[i][j]+=nums[i-1][j];
            }
        }
    }

    for(int j=0;j<n;j++){
        //将每一行作为最底层进行计算
        int cur;
        r=0;
        for(int i=0;i<m;i++){
            while(r>0&&nums[j][st[r-1]]>=nums[j][i]){
                cur=st[--r];
                L=r>0?st[r-1]:-1;
                ans=max(ans,nums[j][cur]*(i-1-L));
            }
            st[r++]=i;
        }

        while (r > 0) {
            cur = st[--r];
            L = r > 0 ? st[r - 1] : -1;
            ans=max(ans,nums[j][cur]*(m-1-L));
        }
    }

    cout<<ans*3<<endl;
    return 0;
}