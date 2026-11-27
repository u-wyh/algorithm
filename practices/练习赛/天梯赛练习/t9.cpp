#include<bits/stdc++.h>
using namespace std;

int n,m,s;
stack<char>sta;
vector<char>vec[105];

int main()
{
    cin>>n>>m>>s;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            char c;
            cin>>c;
            vec[i].push_back(c);
        }
    }
    int op;
    while(cin>>op&&op!=-1){
        if(op!=0){
            if(sta.size()==s&&vec[op].size()!=0){
                cout<<sta.top();
                sta.pop();
            }
            if(vec[op].size()){
                char c=vec[op].front();
                vec[op].erase(vec[op].begin());
                sta.push(c);
            }
        }
        else {
            if(sta.size()){
                cout<<sta.top();
                sta.pop();
            }
        }
    }
    return 0;
}