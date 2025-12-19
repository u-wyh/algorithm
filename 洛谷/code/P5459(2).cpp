#include<bits/stdc++.h>
using namespace std;
const int MAXN = 500001;

int tree[MAXN];
int n,L,R;

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

int query(int l,int r){
    return sum(r)-sum(l-1);
}

int main()
{
    cin>>n>>L>>R;
    for(int i=1;i<=n;i++){
        int v;
        cin>>v;
        add(i,v);
        //我们初始时认为树状数组里面的数字全都是0   直接调用add操作建立树状数组
    }
    int ans=0;
    for(int i=1,j=1;i<=n,j<=n;i++){
        while(query(i,j)<L){
            j++;
        }
        if(query(i,j)>=L&&query(i,j)<=R){
            ans++;
        }
    }
    cout<<ans;
    return 0;
}
