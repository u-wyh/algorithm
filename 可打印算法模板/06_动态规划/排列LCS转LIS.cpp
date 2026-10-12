// 用途：两个排列的最长公共子序列，转为最长递增子序列。
// 时间：O(n log n)。
// 空间：O(n)。
// 注意：两个序列须是 1..n 的排列。
#include<iostream>
#include<cstdio>
using namespace std;

int a[100001],b[100001],map[100001],f[100001];

int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        map[a[i]]=i;
    }
	for(int i=1;i<=n;i++){
        scanf("%d",&b[i]);
        f[i]=0x7fffffff;
    }
	// 把第二个排列映射成第一个排列中的位置，再求严格 LIS。
	int len=0;
	f[0]=0;
	for(int i=1;i<=n;i++){
		int l=0,r=len,mid;
		if(map[b[i]]>f[len])
            f[++len]=map[b[i]];
		else{
            while(l<r){
                mid=(l+r)/2;
                if(f[mid]>map[b[i]])
                    r=mid;
                else
                    l=mid+1;
            }
            f[l]=min(map[b[i]],f[l]);
     	}
    }
    cout<<len;
    return 0;
}
