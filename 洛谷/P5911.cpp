//P5911
//这道题的关键是枚举所有的子集
#include<bits/stdc++.h>
using namespace std;
#define int long long

int weight,n;
struct node{
    int t,w;
}nums[16];
int f[1<<16];
int t[1<<16];//表示如果是这个状态 时间是多少
int w[1<<16];//表示如果是这个状态 重量是多少

signed main()
{
    cin>>weight>>n;
    for(int i=0;i<n;i++){
        cin>>nums[i].t>>nums[i].w;
    }
    for(int s=0;s<(1<<n);s++){
        //枚举子集
        for(int i=0;i<n;i++){
            if(s&(1<<i)){
                //表示这个状态存在这个人
                t[s]=max(t[s],nums[i].t);
                w[s]+=nums[i].w;
            }
        }
    }
    for(int i=0;i<(1<<n);i++){
        f[i]=INT_MAX;
    }
    f[0]=0;
    for(int s=1;s<(1<<n);s++){
        for(int s1=s;;s1=s&(s1-1)){
            //这样可以保证s1一定是s的子集
            int s2=s^s1;//表示这是s的最后一批
            if(w[s2]<=weight){
                f[s]=min(f[s],f[s1]+t[s2]);
            }
            if(s1==0){
                //这里不能放在循环中作为判断条件
                //因为或许最后一次就是全部过去了
                break;
            }
        }
        //cout<<f[s]<<endl;
    }
    cout<<f[(1<<n)-1];
    return 0;
}
