// https://www.luogu.com.cn/problem/P1286
// 题意：多组数据，
// 每组已知 n 个非负整数两两相加得到的 n*(n-1)/2 个和值，
// 还原这 n 个数。
// 输入：若干行至 EOF，每行先输入 n，
// 后输入 n*(n-1)/2 个非负整数和值。
// 输出：每组输出一行：有解则按升序输出 n 个非负整数；
// 无解输出 Impossible。
// 数据范围：2 < n < 10，每个和值不超过 100000。
// 数据范围：数据组数不超过 12。
// 算法标签：枚举、贪心、排序
#include<bits/stdc++.h>
using namespace std;

int n;
int arr[20];
int sum[100];
multiset<int>val;
multiset<int>::iterator it;

bool check(int a){
    arr[1]=a;
    for(int i=2;i<=n;i++){
        int v=*val.begin();
        arr[i]=v-arr[1];
        it=val.begin();
        val.erase(it);
        if(arr[i]<arr[i-1]){
            return false;
        }
        for(int j=1;j<=i-2;j++){
            it=val.find(arr[i]+arr[j+1]);
            if(it==val.end()){
                return false;
            }
            else{
                val.erase(it);
            }
        }
    }
    return true;
}

int main()
{
    while(cin>>n){
        bool flag=false;
        for(int i=1;i<=n*(n-1)/2;i++){
            cin>>sum[i];
        }
        sort(sum+1,sum+n*(n-1)/2+1);
        for(int i=0;i<=sum[1]/2;i++){
            val.clear();
            for(int j=1;j<=n*(n-1)/2;j++){
                val.insert(sum[j]);
            }
            if(check(i)){
                for(int j=1;j<=n;j++){
                    cout<<arr[j]<<' ';
                }
                cout<<endl;
                flag=true;
                break;
            }
        }
        if(!flag){
            cout<<"Impossible"<<endl;
        }
    }
    return 0;
}