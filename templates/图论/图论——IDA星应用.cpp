//P2534
//预测函数的要求是尽量和实际相似 但是一定要比实际情况不能多
//比如说目前一个状态需要10步才可以完成 那么预测函数至少就得10步 
//因为dfs本身会访问很多不应该到达的点 IDA*只是减少无效访问
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 20;

int n;
int arr[MAXN];
int help[MAXN];
int ans;

//这道题用这种方法预测很好 因为每次翻转只能改变一组相邻值的差  最终的结果相邻值的差都是1
//所以预测函数就是
int predict(){
    int cnt=0;
    for(int i=1;i<=n;i++){
        //这里还要特别注意 i要枚举到n 
        if(abs(arr[i]-arr[i+1])!=1){
            cnt++;
        }
    }
    return cnt;
}

int find(int num){
    int l=1,r=n,ans=1;
    while(l<=r){
        int mid=(l+r)/2;
        if(help[mid]>=num){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

bool IDAdfs(int t){
    int pre=predict();
    if(pre+t>ans){
        return false;
    }
    if(pre==0){
        return true;
    }
    int flag=false;
    for(int i=2;i<=n;i++){
        reverse(arr+1,arr+i+1);
        if(IDAdfs(t+1)){
            flag=true;
        }
        reverse(arr+1,arr+i+1);
    }
    if(flag)
        return true;
    return false;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        help[i]=arr[i];
    }
    sort(help+1,help+n+1);
    for(int i=1;i<=n;i++){
        //离散化
        arr[i]=find(arr[i]);
    }
    arr[n+1]=n+1;//新加节点
    ans=predict();
    while(!IDAdfs(0)){
        ans++;
    }
    cout<<ans<<endl;
    return 0;
}
