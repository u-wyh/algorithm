#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e7+5;

int tree[MAXN];
//这个数组实际上是一个差分数组
int n,m;

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
//这个函数的作用是数组的i位置加上v

int sum(int i){
    int ans=0;
    while(i>0){
        ans+=tree[i];
        i-=lowbit(i);
        //每一次都减去自己最右侧的1
    }
    return ans;
}
//这个函数求的是这个差分数组从1到i数字的累加和  那么就相当于这个数字实际值

int main()
{
    cin>>n>>m;
    for(int i=1,op,x,y;i<=m;i++){
        cin>>op;
        if(op==0){
            cin>>x>>y;
            add(x,1);
            add(y+1,-1);
        }else if(op==1){
            cin>>x;
            cout<<sum(x)<<endl;
        }
    }
    return 0;
}
