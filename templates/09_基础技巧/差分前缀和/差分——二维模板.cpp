// 二维差分模版(洛谷)
// 测试链接 : https://www.luogu.com.cn/problem/P3397
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下的code，提交时请把类名改成"Main"，可以直接通过
#include<bits/stdc++.h>
using namespace std;

int n,m;
int nums[1005][1005];

void Set(int a,int b,int c,int d,int v){
    nums[a][b]+=v;
    nums[a][d+1]-=v;
    nums[c+1][b]-=v;
    nums[c+1][d+1]+=v;
}

void build(){
    //来一遍二维前缀和即可
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            nums[i][j]+=nums[i-1][j]+nums[i][j-1]-nums[i-1][j-1];
        }
    }
}

int main()
{
    cin>>n>>m;
    int a,b,c,d;
    while(m--){
        cin>>a>>b>>c>>d;
        Set(a,b,c,d,1);
    }
    build();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            printf("%d ",nums[i][j]);
        }
        printf("\n");
    }
    return 0;
}