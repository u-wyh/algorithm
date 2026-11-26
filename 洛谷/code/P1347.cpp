// https://www.luogu.com.cn/problem/P1347
// 题意：依次给 n 个字母之间的小于关系。
// 处理每条新关系后，判断是否已经能确定唯一顺序，或前缀关系已经矛盾。
// 第一次能判定时按题目格式输出关系条数和结果，始终不能判定则输出 Sorted sequence cannot be determined.。
// 数据范围：2 ≤ n ≤ 26，1 ≤ m ≤ 600，元素用大写字母 A 起顺序表示。

#include<bits/stdc++.h>
using namespace std;

int n,m;
int k;
int graph[30][30];
struct node{
    int sum,index;
}nums[30];
char str[600][3];

bool cmp(node a,node b){
    return a.sum<b.sum;
}

void compute(int x){
    for(int i=0;i<=n;i++){
        nums[i].index=i;
        nums[i].sum=0;
        for(int j=0;j<=n;j++){
            if(graph[i][j]==1){
                nums[i].sum++;
            }
        }
    }
    sort(nums,nums+n,cmp);
    cout<<"Sorted sequence determined after "<<x<<" relations: ";
    for(int i=0;i<n;i++){
        char c=nums[i].index+'A';
        cout<<c;
    }
    cout<<'.';
}

int main()
{
    cin>>n>>m;
    int ans=(n*n-n)/2;
    for(int i=1;i<=m;i++){
        cin>>str[i][0]>>str[i][1]>>str[i][2];
    }
    for(int i=1;i<=m;i++){
        char a=str[i][0],b=str[i][2];
        int u,v;
        u=a-'A';
        v=b-'A';
        int temp=u;
        u=v;
        v=temp;
        if(u==v){
            cout<<"Inconsistency found after " <<i<< " relations.";
            return 0;
        }
        if(graph[u][v]==0){
            graph[u][v]=1;
            graph[v][u]=-1;
            k++;
            if(k==ans){
                compute(i);
                return 0;
            }
            for(int j=0;j<n;j++){
                if(graph[v][j]==1){
                    if(graph[u][j]==0){
                        graph[u][j]=1;
                        graph[j][u]=-1;
                        k++;
                        if(k==ans){
                            compute(i);
                            return 0;
                        }
                    }
                    if(graph[u][j]==1){
                        continue;
                    }
                    else{
                        cout<<"Inconsistency found after " <<i<< " relations.";
                        return 0;
                    }
                }
            }
//            for(int h=0;h<n;h++){
//                if(graph[u][h]==-1){
//                    for(int j=0;j<n;j++){
//                        if(graph[v][j]==1){
//                            if(graph[h][j]==0){
//                                graph[h][j]=1;
//                                graph[j][h]=-1;
//                                k++;
//                                if(k==ans){
//                                    compute(i);
//                                    return 0;
//                                }
//                            }
//                            if(graph[h][j]==1){
//                                continue;
//                            }
//                            else{
//                                cout<<"Inconsistency found after " <<i<< " relations.";
//                                return 0;
//                            }
//                        }
//                    }
//                }
//            }
        }
        else if(graph[u][v]==1)
            continue;
        else{
            cout<<"Inconsistency found after " <<i<< " relations.";
            return 0;
        }
    }
    cout<<"Sorted sequence cannot be determined.";
    return 0;
}
