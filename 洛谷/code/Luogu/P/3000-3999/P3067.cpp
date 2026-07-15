//这种方法之所以错 是因为这道题目问的是可以划分的集合的个数  而不是可以划分的集合的划分方案数
//比如 1 1 1 2  可以划分成 1 1 1     2差值为1   和   1 1      1 2差值也为1
// #include<bits/stdc++.h>
// using namespace std;
// const int MAXN = 1e5+5;

// int n;
// int arr[22];
// int lsum[MAXN],lsize;
// int rsum[MAXN],rsize;
// int size;

// void dfs(int u,int st,int en,int sum,int *num){
//     if(u==en+1){
//         num[++size]=sum;
//         return ;
//     }
//     dfs(u+1,st,en,sum+arr[u],num);
//     dfs(u+1,st,en,sum-arr[u],num);
//     dfs(u+1,st,en,sum,num);
// }

// int main()
// {
//     cin>>n;
//     for(int i=1;i<=n;i++){
//         cin>>arr[i];
//     }
//     size=0;
//     dfs(1,1,n/2,0,lsum);
//     lsize=size;
//     size=0;
//     dfs(n/2+1,n/2+1,n,0,rsum);
//     rsize=size;
//     sort(lsum+1,lsum+lsize+1);
//     sort(rsum+1,rsum+rsize+1);
//     int ans=0;
//     int last=0;
//     int r=rsize;
//     lsum[0]=lsum[1]+1;//表示他们不一样  防止偶然相同
//     for(int i=1;i<=lsize;i++){
//         if(lsum[i]==lsum[i-1]){
//             ans+=last;
//             continue;
//         }
//         last=0;
//         while(r&&(lsum[i]+rsum[r]>=0)){
//             if(lsum[i]+rsum[r]==0){
//                 last++;
//             }
//             r--;
//         }
//         ans+=last;
//     }
//     ans/=2;
//     cout<<ans<<endl;
//     return 0;
// }

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1<<21;

int n;
int arr[21];
vector<int>vec[MAXN];
map<int,int>vis;
int tot=0;//离散化
int ans[MAXN];

void dfs1(int u,int sum,int now){
    //now表示到目前为止选过的状态
    if(u==n/2+1){
        if(vis[sum]==0){
            vis[sum]=++tot;//离散化
        }
        vec[vis[sum]].push_back(now);
        return ;
    }
    dfs1(u+1,sum+arr[u],now|(1<<(u-1)));
    dfs1(u+1,sum-arr[u],now|(1<<(u-1)));
    dfs1(u+1,sum,now);
}

void dfs2(int u,int sum,int now){
    if(u==n+1){
        int k=vis[sum];
        if(k!=0){
            for(int i=0;i<vec[k].size();i++){
                ans[now|vec[k][i]]=1;
            }
        }
        return ;
    }   
    dfs2(u+1,sum+arr[u],now|(1<<(u-1)));
    dfs2(u+1,sum-arr[u],now|(1<<(u-1)));
    dfs2(u+1,sum,now);
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    dfs1(1,0,0);
    dfs2(n/2+1,0,0);
    int res=0;
    for(int i=1;i<(1<<n);i++){
        res+=ans[i];
    }
    cout<<res<<endl;
    return 0;
}