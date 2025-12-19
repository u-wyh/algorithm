// 去除重复字母保证剩余字符串的字典序最小
// 给你一个字符串 s ，请你去除字符串中重复的字母，使得每个字母只出现一次
// 需保证 返回结果的字典序最小
// 要求不能打乱其他字符的相对位置
// 测试链接 : https://leetcode.cn/problems/remove-duplicate-letters/
//这道题单调栈是一个工具
#include<bits/stdc++.h>
using namespace std;

int n;
char str[1000];
int nums[30],enter[30];
int r=0,st[1000];

int main()
{
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>str[i];
        nums[str[i]-'a']++;//首先统计词频
        //词频表是为了判断单调栈中的元素是否可以删除
    }
    
    for(int i=0;i<n;i++){
        if(!enter[str[i]-'a']){
            //如果现在有一个相同的元素在表中  说明目前来看在这个位置是现在最好的选择
            //那么就不会进入
            while(r>0&&nums[str[st[r-1]]-'a']>0&&str[st[r-1]]>str[i]){
                //如果栈顶的元素比自己大  无法大压小  
                //并且后面还有这个栈顶元素  那么就可以删除栈顶  让更小的到前面去
                enter[str[st[r-1]]-'a']=0;
                r--;
            }
            st[r++]=i;
            enter[str[i]-'a']=1;//表示这个元素是在栈中
        }
        nums[str[i]-'a']--;//表示在这之后还有多少个这个元素
    }
    for(int i=0;i<r;i++)
        cout<<str[st[i]];
    return 0;
}