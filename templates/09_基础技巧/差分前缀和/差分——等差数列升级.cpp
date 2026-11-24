// 一群人落水后求每个位置的水位高度
// 问题描述比较复杂，见测试链接
// 测试链接 : https://www.luogu.com.cn/problem/P5026
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下的code，提交时请把类名改成"Main"，可以直接通过
#include<bits/stdc++.h>
using namespace std;
const int offset=30005;

int n,m;
int v,x;
int arr[2030005];

void Set(int l,int r,int s,int e,int d){
    arr[l+offset]+=s;
    arr[l+1+offset]+=(d-s);
    arr[r+1+offset]-=(d+e);
    arr[r+2+offset]+=e;
}

void build(){
    //两遍前缀和
    for(int i=1;i<=n+offset;i++){
        arr[i]+=arr[i-1];
    }
    for(int i=1;i<=n+offset;i++){
        arr[i]+=arr[i-1];
    }
}

void fall(int v,int x){
    //表示v在x处落水  导致的结果如下四个函数
    Set(x-3*v+1,x-2*v,1,v,1);
    Set(x-2*v+1,x,v-1,-v,-1);
    Set(x+1,x+2*v,-v+1,v,1);
    Set(x+2*v+1,x+3*v-1,v-1,1,-1);
}

int main()
{
    cin>>m>>n;
    while(m--){
        cin>>v>>x;
        fall(v,x);
    }
    build();
    for(int i=1;i<=n;i++){
        printf("%d ",arr[i+offset]);
    }
    return 0;
}