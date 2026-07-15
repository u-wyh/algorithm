#include <bits/stdc++.h>
using namespace std;
const int MAX = 1007;
bitset<1007> vis[500007];
//记忆化需要的bitset，为了省空间

struct Trie//Trie树结构体封装式写法
//我喜欢这个，因为用起来就和STL一样
{
     int ch[500007][5], sz = 0, val[500007];
     //val指以这个位置为结尾的单词数量

     void clear()//初始化
     {
          memset(ch, 0, sizeof(ch));
          sz = 0;
     }

     int idx(char c)//获取每个字符对应的数码
     //总不能把char当成数组下标吧，map神仙当我没说
     {
          if (c == 'A')
          {
               return 1;
          }
          if (c == 'G')
          {
               return 2;
          }
          if (c == 'T')
          {
               return 3;
          }
          if (c == 'C')
          {
               return 4;
          }
          if (c == '?')
          {
               return 5;
          }
          if (c == '*')
          {
               return 6;
          }
     }

     void insert(char s[])//插入基操
     {
          int u = 0, len = strlen(s + 1);
          for (int i = 1; i <= len; i++)
          {
               int x = idx(s[i]);
               if (ch[u][x] == 0)
               {
                    ch[u][x] = ++sz;
               }
               u = ch[u][x];
          }
          val[u]++;
     }
} Tree;

char vir[1007];//病毒串
int N, L;//分别为RNA串的数量，病毒串的长度
int ans = 0;//可以和病毒串匹配的RNA串数量

void dfs(int stp, int now) //模式串的第stp位，在trie树上的位置为now
{
     if (stp == L + 1)//病毒串搜到底了
     {
          ans += Tree.val[now];//更新答案
          Tree.val[now] = 0;//修改val值，避免多加
          return;
     }
     if (vis[now][stp])//记忆化
     {
          return;
     }

     int x = Tree.idx(vir[stp]);
     vis[now][stp] = 1;

     if (x >= 1 && x <= 4)//若stp位置上是字母
     {
          if (Tree.ch[now][x])
               dfs(stp + 1, Tree.ch[now][x]);
     }

     if (x == 5)//若是'?'
     {
          for (int i = 1; i <= 4; i++)
          //向四个方向都可以走
          {
               if (Tree.ch[now][i])
                    dfs(stp + 1, Tree.ch[now][i]);
          }
     }

     if (x == 6)//若是*
     {
          dfs(stp + 1, now);//第一种情况：空串
          for (int i = 1; i <= 4; i++)
          //第二种情况：'*'='?'+'*'
          {
               if (Tree.ch[now][i])
               {
                    dfs(stp + 1, Tree.ch[now][i]);
                    //处理'?'
                    dfs(stp, Tree.ch[now][i]);
                    //处理'*'
               }
          }
     }
}
int main()
{
     cin >> vir + 1;
     L = strlen(vir + 1);

     cin >> N;
     Tree.clear();

     for (int i = 1; i <= N; i++)
     {
          char RNA[1007];
          cin >> RNA + 1;
          Tree.insert(RNA);
     }
     dfs(1, 0);
     cout << N - ans << endl;//ans是匹配上的RNA串数
     //题目要求的是匹配不上的串数，故为 N-ans
}
