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
