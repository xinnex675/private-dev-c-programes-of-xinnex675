#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    // 初始化随机数生成器
    srand(time(0));
    int secretNumber = rand() % 100 + 1; // 生成1-100的随机数
    int guess;
    int attempts = 0;

    cout << "猜数字游戏！我已经想好了一个1-100之间的数字。" << endl;

    // 猜数字循环
    do {
        cout << "请输入你的猜测: ";
        cin >> guess;
        attempts++;

        if (guess > secretNumber) {
            cout << "太大了！再试试。" << endl;
        } else if (guess < secretNumber) {
            cout << "太小了！再试试。" << endl;
        } else {
            cout << "恭喜你猜对了！答案是 " << secretNumber 
                 << "，你用了 " << attempts << " 次猜对。" << endl;
        }
    } while (guess != secretNumber);

    return 0;
}
    
