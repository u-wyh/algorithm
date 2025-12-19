// https://www.luogu.com.cn/problem/P1441
// 这道题要注意 砝码只能放一边
#include<bits/stdc++.h>
using namespace std;

int one[1<<21];
int value[21];
int n,m;

int main()
{
    cin>>n>>m;
    for(int i=0;i<n;i++){
        cin>>value[i];
    }
    //快速得到每个数字二进制上1的个数  就是去除最低位的1的数字加上1
    one[0]=0;
    for(int i=1;i<(1<<n);i++){
        int j=i&-i;
        one[i]=one[i-j]+1;
    }
    int ans=0;
    //这里是一个状态压缩
    for(int i=1;i<(1<<n);i++){
        if(one[i]==n-m){
            bitset<2010> b;
            b[0]=1;//必须有一个1初始化  否则后面根本加不上或操作
            for(int j=0;j<n;j++){
                if(i&(1<<j)){
                    b=b|(b<<value[j]);
                }
            }
            ans=max(ans,(int)b.count());
        }
    }
    cout<<ans-1;
    return 0;
}