// https://www.luogu.com.cn/problem/P5200
// 题意：给 1..N 的排列，每次只能命令排头奶牛向后移动 c 步（1 <= c <= N-1）
// 求排成升序 1..N 的最少操作次数 K 及每步移动步数序列 c_1..c_K。
// 数据范围：1 <= N <= 10^5。
#include<bits/stdc++.h>
// 算法标签：树状数组、贪心
using namespace std;
const int MAXN = 100005;

int tree[MAXN],arr[MAXN];
int n;

int lowbit(int x){
    return x & -x;
}

void add(int i,int v){
    while(i<=n){
        tree[i]+=v;
        i+=lowbit(i);
        //每一次都加上自己最右侧的1
    }
}

int sum(int i){
    int ans=0;
    while(i>0){
        ans+=tree[i];
        i-=lowbit(i);
        //每一次都减去自己最右侧的1
    }
    return ans;
}
//这个函数求的是从1到i所有数字的和


int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    int ans=0;
    for(int i=n;i>0;i--){
        if(arr[i]<arr[i-1]){
            ans=i-1;
            break;
        }
        add(arr[i],1);
    }
    add(arr[ans+1],1);
    cout<<ans<<endl;
    for(int i=1;i<=ans;i++){
        add(arr[i],1);
        cout<<ans-i+sum(arr[i]-1)<<' ';
    }
    return 0;
}
