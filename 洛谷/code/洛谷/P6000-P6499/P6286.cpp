// https://www.luogu.com.cn/problem/P6286
// 题意：给定 n 个互不相同的小写单词和目标排位排列 a_i，
// 求一个英文字母表排列作为替换密钥
// 使所有单词替换后按字典序升序排列时第 i 位恰好为原第 a_i 个单词；
// 不可行输出 NE，否则输出 DA 及任意可行密钥。
// 数据范围：2 <= n <= 100，1 <= a_i <= n，
// 单词长度 <= 100。
// 算法标签：拓扑排序
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;

int n;
string str[MAXN];
int arr[MAXN];
vector<int>vec[30];//空格看做27

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
