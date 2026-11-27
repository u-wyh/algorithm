#include<bits/stdc++.h>
using namespace std;
const int MAXN = 305;

int goal;
int c1,c2,c3;
int w1,w2,w3;
bool vis[MAXN][MAXN][MAXN];
int t[MAXN][MAXN][MAXN];
struct node{
    int a,b,c;
};
node pre[MAXN][MAXN][MAXN];
queue<node>q;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

stack<node>st;
void compute(int a,int b,int c){
    if(a==w1&&b==w2&&c==w3){
        while(!st.empty()){
            node u=st.top();
            st.pop();
            cout<<u.a<<' '<<u.b<<' '<<u.c<<endl;
        }
    }
    else{
        st.push({a,b,c});
        node u=pre[a][b][c];
        compute(u.a,u.b,u.c);
    }
}

int main()
{
    cin>>c1>>c2>>c3;
    cin>>w1>>w2>>w3>>goal;
    vis[w1][w2][w3]=true;
    t[w1][w2][w3]=0;
    q.push({w1,w2,w3});
    while(!q.empty()){
        node u=q.front();
        q.pop();
        if(u.a==goal||u.b==goal||u.c==goal){
            cout<<t[u.a][u.b][u.c]<<endl;
            compute(u.a,u.b,u.c);
            return 0;
        }
        int now=t[u.a][u.b][u.c];
        int minn=INT_MAX;
        if(u.a){
            minn=min(minn,u.a);
        }
        if(u.b){
            minn=min(minn,u.b);
        }
        if(u.c){
            minn=min(minn,u.c);
        }
        if(u.a==minn){
            if(!vis[0][u.b][u.c]){
                vis[0][u.b][u.c]=true;
                t[0][u.b][u.c]=now+1;
                pre[0][u.b][u.c]={u.a,u.b,u.c};
                q.push({0,u.b,u.c});
            }
        }
        if(u.b==minn){
            if(!vis[u.a][0][u.c]){
                vis[u.a][0][u.c]=true;
                t[u.a][0][u.c]=now+1;
                pre[u.a][0][u.c]={u.a,u.b,u.c};
                q.push({u.a,0,u.c});
            }
        }
        if(u.c==minn){
            if(!vis[u.a][u.b][0]){
                vis[u.a][u.b][0]=true;
                t[u.a][u.b][0]=now+1;
                pre[u.a][u.b][0]={u.a,u.b,u.c};
                q.push({u.a,u.b,0});
            }
        }
        if(u.a){
            int d=min(u.a,c2-u.b);
            if(!vis[u.a-d][u.b+d][u.c]){
                vis[u.a-d][u.b+d][u.c]=true;
                t[u.a-d][u.b+d][u.c]=now+1;
                pre[u.a-d][u.b+d][u.c]={u.a,u.b,u.c};
                q.push({u.a-d,u.b+d,u.c});
            }
            d=min(u.a,c3-u.c);
            if(!vis[u.a-d][u.b][u.c+d]){
                vis[u.a-d][u.b][u.c+d]=true;
                t[u.a-d][u.b][u.c+d]=now+1;
                pre[u.a-d][u.b][u.c+d]={u.a,u.b,u.c};
                q.push({u.a-d,u.b,u.c+d});
            }
        }
        if(u.b){
            int d=min(u.b,c1-u.a);
            if(!vis[u.a+d][u.b-d][u.c]){
                vis[u.a+d][u.b-d][u.c]=true;
                t[u.a+d][u.b-d][u.c]=now+1;
                pre[u.a+d][u.b-d][u.c]={u.a,u.b,u.c};
                q.push({u.a+d,u.b-d,u.c});
            }
            d=min(u.b,c3-u.c);
            if(!vis[u.a][u.b-d][u.c+d]){
                vis[u.a][u.b-d][u.c+d]=true;
                t[u.a][u.b-d][u.c+d]=now+1;
                pre[u.a][u.b-d][u.c+d]={u.a,u.b,u.c};
                q.push({u.a,u.b-d,u.c+d});
            }
        }
        if(u.c){
            int d=min(u.c,c2-u.b);
            if(!vis[u.a][u.b+d][u.c-d]){
                vis[u.a][u.b+d][u.c-d]=true;
                t[u.a][u.b+d][u.c-d]=now+1;
                pre[u.a][u.b+d][u.c-d]={u.a,u.b,u.c};
                q.push({u.a,u.b+d,u.c-d});
            }
            d=min(u.c,c1-u.a);
            if(!vis[u.a+d][u.b][u.c-d]){
                vis[u.a+d][u.b][u.c-d]=true;
                t[u.a+d][u.b][u.c-d]=now+1;
                pre[u.a+d][u.b][u.c-d]={u.a,u.b,u.c};
                q.push({u.a+d,u.b,u.c-d});
            }
        }
    }
    cout<<-1<<endl;
    return 0;
}