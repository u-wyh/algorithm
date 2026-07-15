#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;

int n;
string str[MAXN];
int arr[MAXN];
vector<int>vec[30];//¿Õ¸ñ¿´×ö27

int in[30];
int head[30];
int Next[10005];
int to[10005];
int cnt=1;

queue<int>q;
int ans[30];
char s[30];

void addedge(int u,int v){
    Next[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
    in[v]++;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>str[i];
    }
    for(int i=1;i<=n;i++){
        int u;
        cin>>u;
        arr[u]=i;
    }
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            if(arr[i]<arr[j]){
                int len1=str[i].length();
                int len2=str[j].length();
                int k=0;
                while(k<len1&&k<len2&&str[i][k]==str[j][k]){
                    k++;
                }
                if(k==len1&&k==len2){
                    cout<<"NE";
                    return 0;
                }
                if(k==len1){
                    cout<<"NE";
                    return 0;
                    addedge(27,str[j][k]-'a'+1);
                }
                else if(k==len2){
                    addedge(str[i][k]-'a'+1,27);
                }
                else{
                    addedge(str[i][k]-'a'+1,str[j][k]-'a'+1);
                }
            }
            else{
                int len1=str[i].length();
                int len2=str[j].length();
                int k=0;
                while(k<len1&&k<len2&&str[i][k]==str[j][k]){
                    k++;
                }
                if(k==len1&&k==len2){
                    cout<<"NE";
                    return 0;
                }
                if(k==len1){
                    addedge(str[j][k]-'a'+1,27);
                }
                else if(k==len2){
                    cout<<"NE";
                    return 0;
                    addedge(27,str[i][k]-'a'+1);
                }
                else{
                    addedge(str[j][k]-'a'+1,str[i][k]-'a'+1);
                }
            }
        }
    }
    int cnt=0;
    for(int i=1;i<=27;i++){
        if(in[i]==0){
            q.push(i);
        }
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        ans[++cnt]=u;
        for(int i=head[u];i;i=Next[i]){
            in[to[i]]--;
            if(in[to[i]]==0){
                q.push(to[i]);
            }
        }
    }
    for(int i=1;i<=27;i++){
        if(in[i]!=0){
            cout<<"NE"<<endl;
            return 0;
        }
    }
    cout<<"DA"<<endl;
    int flag=0;
    for(int i=1;i<=27;i++){
        if(ans[i]!=27){
            s[ans[i]]='a'-1-flag+i;
        }
        else{
            flag++;
        }
    }
    for(int i=1;i<=26;i++){
        cout<<s[i];
    }
    return 0;
}
