#include<bits/stdc++.h>
using namespace std;

vector<int>vec[21];
int sta[21];//表示动了这个开关后会有什么样的数据变化1表示变化
//这里要注意  一开始全都是0  最好变为1
int n;
int dp[1<<21];
queue<int>q;

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        int t;
        cin>>t;
        for(int j=1;j<=t;j++){
            int u;
            cin>>u;
            vec[i].push_back(u);
        }
    }
    for(int i=1;i<=n;i++){
        //sta[i]=1;//初始化
        sta[i]^=(1<<i);//先改变当前的状态
        //cout<<vec[i].size()<<endl;
        for(int j=0;j<vec[i].size();j++){
            sta[i]^=(1<<vec[i][j]);//改变直接相连的状态
        }
        for(int j=0;j<vec[i].size();j++){
            for(int k=0;k<vec[vec[i][j]].size();k++){
                //cout<<vec[vec[i][j]][k]<<' ';
                sta[i]^=(1<<vec[vec[i][j]][k]);
            }
        }
        //cout<<endl;
//        bitset<8> binary(sta[i]);
//        cout<<' '<<binary<<endl;
        //cout<<' '<<sta[i]<<endl;
    }
    dp[(1<<(n+1))-2]=1;//最终答案要减去1
    //cout<<' '<<(1<<(n+1))-1<<endl;
    q.push((1<<(n+1))-2);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        if(u==0){
            cout<<dp[u]-1;
            return 0;
        }
        for(int i=1;i<=n;i++){
            int status=sta[i]^u;
            if(!dp[status]){
                dp[status]=dp[u]+1;
                q.push(status);
            }
        }
    }
    cout<<"Change an alarm clock，please!";
    return 0;
}
