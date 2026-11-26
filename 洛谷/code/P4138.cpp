// https://www.luogu.com.cn/problem/P4138
// 题意：第一行输入挂饰个数 N；接下来 N 行每行两个整数 A_i 和 B_i，表示挂饰 i 有 A_i 个挂钩、安装可得 B_i 喜悦值（可为负）。
// 手机最多直接挂 1 个挂饰，其余只能挂在其他挂饰的挂钩上（可不挂满，也可一个不挂），最大化所选挂饰喜悦值之和。
// 输出一行一个整数表示最大喜悦值总和。
// 数据范围：1 <= N <= 2000，0 <= A_i <= N，-10^6 <= B_i <= 10^6。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e3+5;

int n;
struct node{
    int val,cost;
}nums[MAXN];
int f[MAXN];
int arr[MAXN];
int s[MAXN];
int cnta,cntb;
int sum=0;
int cnt=0;

bool cmp(int a,int b){
    return a>b;
}

int main()
{
    cnt=1;
    cin>>n;
    for(int i=1;i<=n;i++){
        int u,v;
        cin>>u>>v;
        if(u==0){
            if(v<=0){
                //i--,n--;
            }
            else{
                ++cntb;
                arr[cntb]=v;
            }
        }
        else{
            if(v>=0){
                cnt+=v-1,sum+=v;
            }
            else{
                ++cnta;
                nums[cnta].val=u-1,nums[cnta].cost=v;
            }
        }
    }
    cnt=min(cnt,n);

    for(int i=0;i<=2000;i++){
        f[i]=-1e9;
    }
    for(int i=0;i<=cnt;i++){
        f[i]=0;
    }
    for(int i=1;i<=cnta;i++){
        for(int j=2000;j>=nums[i].val;j--){
            f[j]=max(f[j],f[j-nums[i].val]+nums[i].cost);
        }
    }
    for(int i=n-1;i>=0;i--){
        f[i]=max(f[i+1],f[i]);
    }
    sort(arr+1,arr+cntb+1,cmp);
    for(int i=1;i<=2000;i++){
        s[i]=s[i-1]+arr[i];
    }
    int ans=0;
    for(int i=0;i<=2000;i++){
        ans=max(ans,f[i]+s[i]);
    }
    cout<<(ans+sum)<<endl;
    return 0;
}
