#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1505;
const int MAXM = MAXN*MAXN;

int n,m;
int fa[MAXM];

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

int main()
{
    scanf("%d %d",&n,&m);
    int all=(n-1)*(n-1)+1;
    for(int i=1;i<=all;i++){
        fa[i]=i;
    }
    bool ans=true;;
    for(int i=1;i<=m;i++){
        int x,y,x1,y1,x2,y2;
        char op,op1,op2;
        scanf("%d %d %c",&x1,&y1,&op1);
        scanf("%d %d %c",&x2,&y2,&op2);
        if(ans){
            x=x1;
            y=y1;
            op=op1;
        }
        else{
            x=x2;
            y=y2;
            op=op2;
        }

        int face1,face2;
        if(op=='E'){
            if(y!=1){
                face1=(x-1)*(n-1)+y-1;
            }
            else{
                face1=all;
            }

            if(y!=n){
                face2=(x-1)*(n-1)+y;
            }
            else{
                face2=all;
            }
        }
        else{
            if(x!=1){
                face1=(x-2)*(n-1)+y;
            }
            else{
                face1=all;
            }

            if(x!=n){
                face2=(x-1)*(n-1)+y;
            }
            else{
                face2=all;
            }
        }

        int fx=find(face1);
        int fy=find(face2);
        if(fx!=fy){
            ans=true;
            fa[fx]=fy;
        }
        else{
            ans=false;
        }

        if(ans){
            cout<<"TAK"<<endl;
        }
        else{
            cout<<"NIE"<<endl;
        }
    }
    return 0;
}