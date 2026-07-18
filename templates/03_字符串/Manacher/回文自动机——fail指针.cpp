// https://www.luogu.com.cn/problem/P3649
// 这道题需要统计出现次数  因为回文自动机上都是本质不同的回文串
// 那么次数就是本质相同的回文串的出现次数  加上是别的回文串的后缀次数
// 本质相同的回文串次数好算  就是在每次添加一个字符后 出现的次数加一
// 如果一个回文串是另外一个的最长子回文后缀  那么他出现的次数应该要加上这个的出现次数
// 因为这个回文串一定是包含了这个最长的子回文后缀的
// 这里其实是一个类似于fail树的操作
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;

int n;

int tree[MAXN][26];
int fail[MAXN];
int len[MAXN];// 节点代表的回文串长度
// 这里的num统计的是PAM上i节点代表的回文串在整个文本中出现的次数
int num[MAXN];
int cnt;
int last;

char s[MAXN];
long long ans;

// 初始化回文自动机
void init(){
    cnt=1;
    last=0;
    len[0]=0,len[1]=-1;
    fail[0]=1;//偶根节点的fail指针指向奇根
    fail[1]=1;
    num[0]=0,num[1]=0;
    s[0]='#';// 特殊字符，防止越界
}

// 在fail链上查找满足条件的节点  即回文串前面一个字母是t[i]的位置  最大的位置
int getfail(int p,int i){
    while(s[i-len[p]-1]!=s[i]){
        p=fail[p];
    }
    return p;
}

// 添加字符t[i]到回文自动机
void insert(int i){
    // 当前字符的数值
    int c=s[i]-'a';
    // 查找合适的节点  其实这里找的是一个类似于父亲节点
    int cur=getfail(last,i);

    // 如果该节点不存在，创建新节点
    if(!tree[cur][c]){
        int x=++cnt;
        len[x]=len[cur]+2;

        // 这里要找的是fail指针指向的节点  意思是最长的回文后缀  但不能是整体  即子回文后缀
        // 所以这里必须是cur的fail指针所指向的节点
        int p=getfail(fail[cur],i);
        fail[x]=tree[p][c];

        tree[cur][c]=x;
    }
    last=tree[cur][c];
}

int main()
{
    scanf("%s",s+1);
    n=strlen(s+1);
    init();
    for(int i=1;i<=n;i++){
        insert(i);
        num[last]++;
    }
    for(int i=cnt;i>=1;i--){
        num[fail[i]]+=num[i];
    }
    for(int i=1;i<=cnt;i++){
        ans=max(ans,1ll*num[i]*len[i]);
    }
    cout<<ans<<endl;
    return 0;
}