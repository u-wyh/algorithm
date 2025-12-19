#include<bits/stdc++.h>
using namespace std;

int n;
int nums[10][10];
int row[100],col[100];//分别表示每种二进制状态有没有被选
int cnt=0;
int ok[1<<10];
vector<int>R[10];
vector<int>C[10];
int r[10],c[10];//表示行和列的选择
int tot;//不确定状态的数目

// 辅助函数：获取状态s中第j位的状态
inline int get(int s, int j) {
    return (s >> j) & 1;
}

// 辅助函数：设置状态s中第j位的状态为v，并返回新的状态
inline int set(int s, int j, int v) {
    return v == 0 ? (s & (~(1 << j))) : (s | (1 << j));
}

void dfs(int i,int s,int ss,int rest,int now){
    //表示目前到达第i位  上一个是s  上上一个是ss  还有rest个1没有填  以二进制存储有效状态now
    if(i==n&&rest==0){
        ok[++cnt]=now;
    }
    if(rest<=-1){
        return ;
    }
    if(s==ss){
        if(s!=1){
            dfs(i+1,1,s,rest-1,now|(1<<(n-1-i)));
        }
        if(s!=0){
            dfs(i+1,0,s,rest,now);
        }
    }
    else{
        dfs(i+1,1,s,rest-1,now|(1<<(n-1-i)));
        dfs(i+1,0,s,rest,now);
    }
}

int main()
{
    cin>>n;
    dfs(0,-1,-1,n/2,0);//一开始的0表示所有位都是0
    cout<<cnt<<endl;
    for(int i=0;i<=cnt;i++){
        row[i]=-1;
        col[i]=-1;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            char c;
            cin>>c;
            if(c=='0')
                nums[i][j]=0;
            else if(c=='1')
                nums[i][j]=1;
            else{
                nums[i][j]=-1;
                tot++;
            }
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<nums[i][j]<<' ';
        }
        cout<<endl;
    }
    cout<<endl;

    for(int i=0;i<n;i++){
        if(r[i]==0){
        //表示这一行还没有结束
            for(int k=1;k<=cnt;k++){
                cout<<444<<endl;
                if(row[k]==-1){//表示这个方案没有被选过
                    for(int j=0;j<n;j++){
                        if(nums[i][j]!=-1){
                            cout<<555<<' '<<k<<' '<<j<<endl;
                            if(nums[i][j]!=get(ok[k],j)){
                                //j=n;//表示终结这个方案
                                continue;
                            }
                            cout<<888<<endl;
                            if(j==n-1){
                                //表示这个方案可行
                                R[i].push_back(k);
                            }
                        }
                    }
                }
            }
            for(int j=0;j<n;j++){
                if(nums[i][j]==-1){
                    int sum=0;
                    for(int k=0;k<R[i].size();k++){
                        sum+=get(ok[R[i][k]],j);
                    }
                    if(sum==0){//全是0
                        tot--;
                        nums[i][j]=0;
                    }
                    else if(sum==R[i].size()){//全是1
                        tot--;
                        nums[i][j]=1;
                    }
                }
            }
        }
    }//完成每一行的初筛
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<nums[i][j]<<' ';
        }
        cout<<endl;
    }
    cout<<777<<endl;

//    for(int j=0;j<n;j++){
//        if(c[j]==0){
//        //表示这一列还没有结束
//            for(int k=1;k<=cnt;k++){
//                if(col[k]==-1){//表示这个方案没有被选过
//                    for(int i=0;i<n;i++){
//                        if(nums[j][i]!=-1){
//                            if(nums[j][i]!=get(ok[k],i)){
//                                i=n;//表示终结这个方案
//                                continue;
//                            }
//                            if(i==n-1){
//                                //表示这个方案可行
//                                C[j].push_back(k);
//                            }
//                        }
//                    }
//                }
//            }
//            for(int i=0;i<n;j++){
//                if(nums[j][i]==-1){
//                    int sum=0;
//                    for(int k=0;k<C[j].size();k++){
//                        sum+=get(ok[R[i][k]],n-i-1);
//                    }
//                    if(sum==0){//全是0
//                        tot--;
//                        nums[j][i]=0;
//                    }
//                    else if(sum==C[j].size()){//全是1
//                        tot--;
//                        nums[j][i]=1;
//                    }
//                }
//            }
//        }
//    }//完成每一列的初筛
//    for(int i=0;i<n;i++){
//        for(int j=0;j<n;j++){
//            cout<<nums[i][j]<<' ';
//        }
//        cout<<endl;
//    }

//    while(tot!=0){
//        for(int i=0;i<n;i++){
//        if(r[i]==0){
//        //表示这一行还没有结束
//            for(int k=1;k<=cnt;k++){
//                cout<<444<<endl;
//                if(row[k]==-1){//表示这个方案没有被选过
//                    for(int j=0;j<n;j++){
//                        if(nums[i][j]!=-1){
//                            cout<<555<<endl;
//                            if(nums[i][j]!=get(ok[k],n-1-j)){
//                                //j=n;//表示终结这个方案
//                                continue;
//                            }
//                            //cout<<888<<endl;
//                            if(j==n-1){
//                                //表示这个方案可行
//                                R[i].push_back(k);
//                            }
//                        }
//                    }
//                }
//            }
//            for(int j=0;j<n;j++){
//                if(nums[i][j]==-1){
//                    int sum=0;
//                    for(int k=0;k<R[i].size();k++){
//                        sum+=get(ok[R[i][k]],n-j-1);
//                    }
//                    if(sum==0){//全是0
//                        tot--;
//                        nums[i][j]=0;
//                    }
//                    else if(sum==R[i].size()){//全是1
//                        tot--;
//                        nums[i][j]=1;
//                    }
//                }
//            }
//        }
//    }//完成每一行的初筛
//    cout<<777<<endl;
//    for(int j=0;j<n;j++){
//        if(c[j]==0){
//        //表示这一列还没有结束
//            for(int k=1;k<=cnt;k++){
//                if(col[k]==-1){//表示这个方案没有被选过
//                    for(int i=0;i<n;i++){
//                        if(nums[j][i]!=-1){
//                            if(nums[j][i]!=get(ok[k],n-1-i)){
//                                i=n;//表示终结这个方案
//                                continue;
//                            }
//                            if(i==n-1){
//                                //表示这个方案可行
//                                C[j].push_back(k);
//                            }
//                        }
//                    }
//                }
//            }
//            for(int i=0;i<n;j++){
//                if(nums[j][i]==-1){
//                    int sum=0;
//                    for(int k=0;k<C[j].size();k++){
//                        sum+=get(ok[R[i][k]],n-i-1);
//                    }
//                    if(sum==0){//全是0
//                        tot--;
//                        nums[j][i]=0;
//                    }
//                    else if(sum==C[j].size()){//全是1
//                        tot--;
//                        nums[j][i]=1;
//                    }
//                }
//            }
//        }
//    }//完成每一列的初筛
//    for(int i=0;i<n;i++){
//        for(int j=0;j<n;j++){
//            cout<<nums[i][j]<<' ';
//        }
//        cout<<endl;
//    }
//    }
    return 0;
}
