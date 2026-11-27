// https://www.luogu.com.cn/problem/B3874
// 题意：给出 N 名学生进入教室的顺序，学号是 0 到 N-1。
// 每人进门时，和已经在教室里且学号比自己小的人各握一次手，求总次数。
// 数据范围：2 ≤ N ≤ 3 × 10^5，入场顺序恰好包含每个学号一次。
// 算法标签：归并排序、逆序对

#include<bits/stdc++.h>
using namespace std;
#define int long long

int n;
int arr[300005];
int help[300005];

int mergesort(int l,int r){
    int mid=(l+r)/2;
    if(l==r)
        return 0;
    for(int i=l;i<=r;i++){
        help[i]=arr[i];
    }
    int i=l;
    int j=mid+1;
    int cnt=0;
    for(int k=l;k<=r;k++){
        if(i==mid+1){
            arr[k]=help[j];
            j++;
        }else if(j==r+1){
            arr[k]=help[i];
            i++;
        }else if(help[i]<=help[j]){
            arr[k]=help[i];
            i++;
        }else if(help[j]<help[i]){
            arr[k]=help[j];
            j++;
            cnt+=(mid-i+1);
        }else
            break;
    }
    return cnt;
}

int merge(int l,int r){
    if(l==r)
        return 0;
    int mid=(l+r)/2;
    int ans=0;
    ans+=merge(l,mid);
    ans+=merge(mid+1,r);
    ans+=mergesort(l,r);
    return ans;
}

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[n-i+1];
    }
    cout<<merge(1,n);
    return 0;
}

