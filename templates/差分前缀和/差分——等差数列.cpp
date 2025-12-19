// 一开始1~n范围上的数字都是0，一共有m个操作，每次操作为(l,r,s,e,d)
// 表示在l~r范围上依次加上首项为s、末项为e、公差为d的数列
// m个操作做完之后，统计1~n范围上所有数字的最大值和异或和
// 测试链接 : https://www.luogu.com.cn/problem/P4231
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下的code，提交时请把类名改成"Main"，可以直接通过
//等差数列差分需要两遍前缀和
#include<bits/stdc++.h>
using namespace std;

int n,m;
long long arr[10000005];
long long l,s,r,e,maxans,eor;

long long read(){
	short f=1;long long x;char ch;
	while(ch=getchar(),ch<'0'||ch>'9')
		if(ch=='-') f=-1;
	x=ch-'0';
	while(ch=getchar(),ch>='0'&&ch<='9')
		x=x*10+ch-'0';
	return x*f;
}

void Set(long long l,long long r,long long s,long long e,long long d){
    //以上参数分别表示  左起点  右终点  初始增加值  末尾增加值  公差
    arr[l]+=s;
    arr[l+1]+=(d-s);
    arr[r+1]-=(d+e);
    arr[r+2]+=e;
}

void build(){
    //两遍前缀和完成
    for(int i=1;i<=n;i++){
        arr[i]+=arr[i-1];
    }
    for(int i=1;i<=n;i++){
        arr[i]+=arr[i-1];
    }
}

int main()
{
    cin>>n>>m;
    while(m--){
        l=read(),r=read(),s=read(),e=read();
        Set(l,r,s,e,(e-s)/(r-l));
    }
    build();
    eor=0;
    for(int i=1;i<=n;i++){
        maxans=max(maxans,arr[i]);
        eor^=arr[i];
    }
    cout<<eor<<' '<<maxans<<endl;
    return 0;
}