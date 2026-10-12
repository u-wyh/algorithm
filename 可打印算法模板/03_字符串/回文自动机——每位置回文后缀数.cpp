// 用途：逐位置求以该位置结尾的回文子串个数。
// 时间：O(n×字符集大小)。
// 空间：O(n×字符集大小)。
// 注意：本例先用上一个答案解码当前字符，再插入自动机。
// 例题：https://www.luogu.com.cn/problem/P5496
// 题意：字符按上个答案偏移编码；解码后逐位求当前回文后缀数。
// 思路：沿失配链找到可扩展回文，新增节点并继承 fail 链统计。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;

int n;

int tree[MAXN][26];
int fail[MAXN];
int len[MAXN];// 节点代表的回文串长度
// 注意这里的回文子串数量更像是种类的个数
int num[MAXN];// 以节点结尾的回文子串个数
int cnt;
int last;

char s[MAXN];
char t[MAXN];
int ans[MAXN];

// 初始化回文自动机
void init(){
    cnt=1;
    last=0;
    // 为了保证len[x]=len[fa[x]]+2 所以将奇根设置为-1
    len[0]=0,len[1]=-1;
    fail[0]=1;//偶根节点的fail指针指向奇根
    fail[1]=1;
    num[0]=0,num[1]=0;
    t[0]='#';// 特殊字符，防止越界
}

// 在fail链上查找满足条件的节点  即回文串前面一个字母是t[i]的位置  最大的位置
int getfail(int p,int i){
    while(t[i-len[p]-1]!=t[i]){
        p=fail[p];
    }
    return p;
}

// 添加字符t[i]到回文自动机
// 我们先要找到以t[i-1]为尾的、并且前一位字符等于t[i]的最长回文串
void insert(int i){
    // 当前字符的数值
    int c=t[i]-'a';
    // 查找合适的节点  其实这里找的是一个类似于父亲节点
    // 此时找到的cur即为我们找到的最长回文串
    int cur=getfail(last,i);

    // 如果该这个状态没有后面接t[i]的，那么说明此时是一个全新的状态，创建新节点
    if(!tree[cur][c]){
        int x=++cnt;
        len[x]=len[cur]+2;

        // 这里要找的是新状态的fail指针指向的节点  意思是最长的回文后缀  但不能是整体  即子回文后缀
        // 所以这里必须是cur的fail指针所指向的节点  然后选择这个节点走向c的儿子
        int p=getfail(fail[cur],i);
        fail[x]=tree[p][c];

        tree[cur][c]=x;
        num[x]=num[fail[x]]+1;
    }
    last=tree[cur][c];
}

int main()
{
    scanf("%s",s);
    n=strlen(s);
    init();

    t[1]=s[0];
    insert(1);
    ans[1]=num[last];

    for(int i=2;i<=n;i++){
        t[i]=(s[i-1]+ans[i-1]-'a')%26+'a';
        insert(i);
        ans[i]=num[last];
    }

    for(int i=1;i<=n;i++){
        cout<<ans[i]<<' ';
    }
    cout<<endl;
    return 0;
}
