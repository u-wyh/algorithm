// https://www.luogu.com.cn/problem/P3864
// 题意：第一行输入一个长度为 1..12 的数字串编号，
// 接下来若干行每行输入一个字典中的大写英文名字。
// 数字 2~9 分别映射字母：
// 2->ABC, 3->DEF, 4->GHI, 5->JKL, 6->MNO,
// 7->PRS, 8->TUV
// 9->WXY（无 Q 和 Z）。
// 按字典序每行输出所有能由该编号翻译得到且在字典中的名字；若无则输出 NONE。
// 数据范围：编号长度 1 到 12，
// 字典名字不超过 5000
// 个（题述准确为 4617 个，均为大写且已按字典序排列）。
// 难度评分：1200（洛谷分级换算）
// 算法标签：枚举、字符串
#include<bits/stdc++.h>
using namespace std;
vector<string> Dict; //用Dict存放所有字典中的名字
string str; //给定的编号
const char * str_trans = "2223334445556667 77888999"; //使用该C-风格字符串来存放A-Z(除去Q和Z这24个字母所对应的数字)
int main(){
    ios::sync_with_stdio(false); //只用cin/cout加快IO速度
    cin >> str;
    string tmp;
    while (cin >> tmp){ //将后面所有的字符串循环读入到tmp中，再放到Vector尾，(cin>>tmp)即可以起到读入字符串的作用，也可以起到判断文件是否到达末尾。详情请阅读C++ Primer Plus。
        Dict.push_back(tmp);
    }
    int len = str.length();
    bool global_flag = false;
    for (int i = 0; i < Dict.size(); i++){ //遍历所有字典元素，因为字典元素少
        if (len != Dict[i].length())continue; //剪枝，如果字符串位数不一样就没有必要比较。
        bool flag = true;
        for (int j = 0; j < len; j++){
            if (str_trans[Dict[i][j] - 'A'] != str[j]){ //比对字典中每个字符对应的数字是否与输入的每个数字相同
                flag = false; //不相同直接跳出循环
                break;
            }
        }
        if (flag){ //相同则输出该单词
            cout << Dict[i] << endl;
            global_flag = true;
        }
    }
    if (!global_flag){ //如果没有一个单词符合要求，就输出NONE。
        cout << "NONE" << endl;
    }
}
