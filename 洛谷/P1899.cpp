#include<bits/stdc++.h>
using namespace std;
const int INF = 2e9;
const int MAXP = 5005;
const int MAXN = 1005;

int n,p,m=1;//m表示的是有效魔法物品的个数
int a[MAXN],b[MAXN];
int f[MAXP];//表示为了凑够i的钱  最少要浪费多少本来该有的利润
int v;//表示目前的利润
int sv;//sv纯粹是为了特判  表示根本买不起一个图鉴的情况

signed main()
{
    cin>>n>>p;
    for(int i=1;i<=n;i++){
        int x,y;
        cin>>x;
        if(getchar()==' '){
            cin>>y;
            if(x>=y-p){
                //表示的是无效的魔法物品
                v+=x;
            }
            else{
                a[m]=x,b[m++]=y;
            }
        }
        else
            v+=x;
    }
    for(int i=v+1;i<=p;i++){
        f[i]=INF;
    }
    sv=v;
    for(int i=1;i<=m;i++){
        v+=b[i]-p,sv+=a[i];
    }
    //此时的v是最大的利润
    for(int i=1;i<=m;i++){
        for(int j=p;j>=a[i];j--){
            f[j]=min(f[j],f[j-a[i]]+b[i]-p-a[i]);
            //表示一个魔法物品直接卖了 造成的利润损失
        }
    }
    cout<<(sv<=p?sv:v-f[p])<<endl;
    return 0;
}
