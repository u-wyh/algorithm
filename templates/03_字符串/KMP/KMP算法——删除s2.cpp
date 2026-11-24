// 不停删除之后剩下的字符串
// 给定一个字符串s1，如果其中含有s2字符串，就删除最左出现的那个
// 删除之后s1剩下的字符重新拼接在一起，再删除最左出现的那个
// 如此周而复始，返回最终剩下的字符串
// 测试链接 : https://www.luogu.com.cn/problem/P4824
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下的code，提交时请把类名改成"Main"，可以直接通过
//这道题的关键是借助栈结构减少重复劳动
//栈中记录的是s1每个位置对应匹配的s2中的位置
//如果是-1  说明没有匹配上
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

char s1[MAXN];
char s2[MAXN];
int nxt[MAXN];
int n,m;

//使用栈结构维护
int st1[MAXN];
int st2[MAXN];//表示对于栈1中的同一个位置的元素对应上的s2中的位置  -1表示没对上
int sz;

void calcnext() {
    if (m == 1) {
        nxt[0] = -1;
        return ;
    }

    nxt[0] = -1;
    nxt[1] = 0;

    int i = 2, cn = 0;
    while (i < m) {
        if (s2[i - 1] == s2[cn]) {
            nxt[i++] = ++cn;
        } else if (cn > 0) {
            cn = nxt[cn];
        } else {
            nxt[i++] = 0;
        }
    }
}

void compute(){
    n=strlen(s1),m=strlen(s2);
    // cout<<n<<' '<<m<<endl;
    calcnext();
    int x=0,y=0;
    while(x<n){
        if(s1[x]==s2[y]){
            st1[sz]=x;
            st2[sz]=y;
            sz++;
            x++,y++;
        }
        else if(y==0){
            st1[sz]=x;
            st2[sz]=-1;//表示没有匹配上
            sz++;
            x++;
        }
        else{
            y=nxt[y];
        }

        if(y==m){
            //全部匹配上了  那么减去s2的长度
            sz-=m;
            y=sz>0?(st2[sz-1]+1):0;//如果栈中空了 那么从0开始   否则从栈顶的下一个位置开始
        }

    }
    for(int i=0;i<sz;i++){
        cout<<s1[st1[i]];
    }
}

int main()
{
    scanf("%s %s",s1,s2);
    compute();
    return 0;
}