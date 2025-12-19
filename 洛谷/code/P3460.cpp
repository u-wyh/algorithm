#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e4+5;
const int MAXM = 1e6+5;

int step[MAXM],cnt;
int n,m;
int tree[MAXN<<1];
int nums[MAXN<<1];
int pos[MAXN];

inline int lowbit(int x){
    return x&-x;
}

void add(int x,int v){
    while(x<=2*n){
        tree[x]+=v;
        x+=lowbit(x);
    }
}

int query(int x){
    int ans=0;
    while(x){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}

int main()
{
    cin>>n;
    for(int i=1;i<=2*n;i++){
        cin>>nums[i];
        add(i,1);
    }
    for(int i=1;i<=2*n;i++){
        if(pos[nums[i]]){
            int dis=query(i-1)-query(pos[nums[i]]);
            int now=i;
            while(dis){
                step[++cnt]=now-1-m;
                now--;
                dis--;
            }
            add(pos[nums[i]],-1);
            add(i,-1);
            m+=2;
        }   
        else{
            pos[nums[i]]=i;
        }
    }
    cout<<cnt<<endl;
    for(int i=1;i<=cnt;i++){
        cout<<step[i]<<endl;
    }
    return 0;
}