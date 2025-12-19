#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;

struct compare{
    bool operator()(int a,int b){
        return a<b;
    }
};
//这两个堆都存储的是  pos*z+更新这个pos位置之前的操作的代价   并且这个代价已经被加入到ans中  
//这个代价是遇到此次操作之前的局部最优解  加上pos*z是为了处理移动时的代价
priority_queue<int,vector<int>,compare>buy;//用于需求的单位代价  需要得到别人的帮助或直接购买
priority_queue<int,vector<int>,compare>sell;//用于供给的单位代价  需要提供给别人或扔掉

int n,x,y,z;//x是购买一份的代价  y是扔掉一份的代价  z是移动一个位置的代价

signed main()
{
    cin>>n>>x>>y>>z;
    int ans=0;//每次ans在更新时  都是目前已经更新结束的最优答案   即局部最优
    for(int i=1;i<=n;i++){
        int a,b;
        cin>>a>>b;
        while(a>b){
            //表示有多余的  
            //那么对于多余的部分只有两种结果 要么是直接扔掉 要么是用于补充那些不够的（可能在前面，也有可能在后面）
            //我们先只考虑前面的   对于后面的则可以使用后悔操作修正
            if(!buy.empty()){
                int cost=i*z-buy.top();//用于更新之前的代价
                if(cost<y){
                    //表示的是解决这个位置所要付出的最小代价
                    ans+=cost;
                    buy.pop();
                    sell.push(i*z+cost);//这里还是要放在sell堆里面
                    //因为这个位置上本身就是有多余的   只不过是暂时将多余的给了前面需要的位置
                    //如果给后面需要的位置会给总体带来更好的效果  那么还是会后悔操作给到后面
                }
                else{
                    ans+=y;
                    sell.push(i*z+y);
                }
            }
            else{
                //表示没有办法 此时只能暂时用扔出的操作
                ans+=y;
                sell.push(i*z+y);
            }
            a--;
        }
        while(a<b){
            if(!sell.empty()){
                int cost=i*z-sell.top();
                if(cost<x){
                    ans+=cost;
                    sell.pop();
                    buy.push(i*z+cost);
                }
                else{
                    ans+=x;
                    buy.push(i*z+x);
                }
            }
            else{
                ans+=x;
                buy.push(i*z+x);
            }
            b--;
        }
    }

    cout<<ans<<endl;
    return 0;
}