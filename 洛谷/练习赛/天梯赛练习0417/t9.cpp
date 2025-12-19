#include<bits/stdc++.h>
using namespace std;

int n,m,k;
queue<int>q;
int sta[25];
int top;

int main()
{
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++){
        int u;
        cin>>u;
        q.push(u);
    }
    int u=n;
    while(u){
        int lst=0;
        if(top==0){
            lst=q.front();
            cout<<q.front();
            q.pop();
            u--;
        }
        else{
            lst=sta[top];
            cout<<sta[top--];
            u--;
        }

        int tmp=0;
        if(u==0){
            break;
        }

        while(tmp<k-1){
            if(sta[top]<=lst&&top){
                u--;
                tmp++;
                lst=sta[top];
                cout<<' '<<sta[top--];
            }
            else if(!q.empty()&&q.front()<=lst){
                u--;
                tmp++;
                lst=q.front();
                q.pop();
                cout<<' '<<lst;
            }
            else if(top<m&&!q.empty()){
                sta[++top]=q.front();
                q.pop();
            }
            else{
                break;
            }

            if(u==0){
                break;
            }
        }
        cout<<endl;
    }
    return 0;
}