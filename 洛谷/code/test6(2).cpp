#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <locale>
#include <codecvt>

using namespace std;

// 设置全局区域设置，支持中文
void setupLocale() {
    try {
        locale::global(locale("zh_CN.UTF-8"));
        wcout.imbue(locale("zh_CN.UTF-8"));
        cout.imbue(locale("zh_CN.UTF-8"));
    }
    catch (...) {
        // 如果设置失败，使用默认设置
    }
}

/*===========================
        Army 类
===========================*/
class Army {
public:
    int archers;
    int catapults;
    int swordsmen;

    Army(int a = 0, int c = 0, int s = 0)
        : archers(a), catapults(c), swordsmen(s) {}

    bool isDead() const {
        return archers + catapults + swordsmen == 0;
    }

    // 限制死亡数量不能超过现有数量
    void applyLoss(int dead_archers, int dead_catapults, int dead_swordsmen) {
        dead_archers = min(dead_archers, archers);
        dead_catapults = min(dead_catapults, catapults);
        dead_swordsmen = min(dead_swordsmen, swordsmen);

        archers -= dead_archers;
        catapults -= dead_catapults;
        swordsmen -= dead_swordsmen;

        cout << "本方损失：" << endl;
        cout << "  弓箭手死亡 " << dead_archers << " 人" << endl;
        cout << "  投石车损失 " << dead_catapults << " 台" << endl;
        cout << "  剑士死亡   " << dead_swordsmen << " 人" << endl;
    }
};

/*===========================
        Battle 类
===========================*/
class Battle {
public:
    static void fight(Army& player, Army& german, 
                      int send_archers, int send_catapults, int send_swordsmen) 
    {
        cout << "\n===== 战斗开始 =====" << endl;

        // 敌军对玩家造成的伤害
        int p_archer_dead = 2 * german.catapults;
        int p_catapult_dead = german.swordsmen;
        int p_swords_dead = 3 * german.archers;

        // 玩家对敌军造成的伤害（取决于派出的士兵）
        int g_archer_dead = 2 * send_catapults;
        int g_catapult_dead = send_swordsmen;
        int g_swords_dead = 3 * send_archers;

        // 应用损失
        player.applyLoss(p_archer_dead, p_catapult_dead, p_swords_dead);
        german.applyLoss(g_archer_dead, g_catapult_dead, g_swords_dead);

        cout << "===== 战斗结束 =====" << endl;
    }
};

/*===========================
        Game 类
===========================*/
class Game {
private:
    Army player;
    Army german;
    string name;

public:
    Game() {
        srand(time(0));

        // Player 初始兵力
        player = Army(50, 25, 100);

        // German 随机兵力
        german = Army(
            rand() % 51 + 20,   // 20 - 70
            rand() % 41 + 10,   // 10 - 50
            rand() % 101 + 50   // 50 - 150
        );
    }

    void intro() {
        cout << "欢迎，冒险者！请输入你的名字：" << endl;
        cin >> name;

        cout << "欢迎你，" << name << "！" << endl
             << "你是罗马军团的指挥官，正在攻击日耳曼部落。" << endl;
    }

    void showStatus() {
        cout << "\n当前兵力：" << endl;
        cout << "  你：弓箭手 " << player.archers 
             << "  投石车 " << player.catapults
             << "  剑士 " << player.swordsmen << endl;

        cout << "  日耳曼：弓箭手 " << german.archers
             << "  投石车 " << german.catapults
             << "  剑士 " << german.swordsmen << endl;
    }

    void start() {
        intro();

        while (true) {
            showStatus();

            int sendA = 0, sendC = 0, sendS = 0;

            cout << "\n请输入派出的弓箭手数量：";
            cin >> sendA;
            sendA = min(sendA, player.archers);

            cout << "请输入派出的投石车数量：";
            cin >> sendC;
            sendC = min(sendC, player.catapults);

            cout << "请输入派出的剑士数量：";
            cin >> sendS;
            sendS = min(sendS, player.swordsmen);

            Battle::fight(player, german, sendA, sendC, sendS);

            // 胜负判断
            if (player.isDead()) {
                cout << "\n你的军队全军覆没……你输了。" << endl;
                return;
            }
            if (german.isDead()) {
                cout << "\n恭喜！你击败了日耳曼部落！" << endl;
                return;
            }
        }
    }
};

/*===========================
        主函数
===========================*/
int main() {
    // 设置区域设置，解决中文显示问题
    setupLocale();
    
    Game game;
    game.start();
    return 0;
}