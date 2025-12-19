#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005;

int n,m;
int nums[MAXN][MAXN];

int sta[MAXN];
int top=0;

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            char c;
            cin>>c;
            nums[i][j]=(c=='.');
            if(nums[i][j]){
                nums[i][j]+=nums[i-1][j];
            }
        }
    }
    long long ans=0;
    for(int i=1;i<=n;i++){
        top=0;
        for(int j=1;j<=m;j++){
            while(top>0&&nums[i][sta[top-1]]>=nums[i][j]){
                int cur=sta[--top];
                if(nums[i][cur]>nums[i][j]){
                    int lt=(top==0)?0:sta[top-1];
                    int len=j-lt-1;
                    int h=max((lt==0)?0:nums[i][lt],nums[i][j]);
                    ans+=(nums[i][cur]-h)*len*(len+1)/2;
                }
            }
            sta[top++]=j;
        }

        while(top>0){
            int cur=sta[--top];
            int lt=(top==0)?0:sta[top-1];
            int len=m-lt;
            int down=(lt==0)?0:nums[i][lt];
            ans+=(nums[i][cur]-down)*len*(len+1)/2;
        }
    }
    cout<<ans<<endl;
    return 0;
}