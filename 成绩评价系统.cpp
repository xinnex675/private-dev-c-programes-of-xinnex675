#include <iostream>
#include <string>
using namespace std;

// 基础功能：简单的个人信息录入与成绩判断
int main() {
    // 1. 定义基础变量
    string name;
    int age;
    float mathScore, englishScore;
    float averageScore;

    // 2. 友好提示与信息输入
    cout << "===== 基础信息录入工具 =====" << endl;
    cout << "请输入你的姓名：";
    getline(cin, name);  // 读取包含空格的姓名

    cout << "请输入你的年龄：";
    cin >> age;

    cout << "请输入数学成绩：";
    cin >> mathScore;
    cout << "请输入英语成绩：";
    cin >> englishScore;

    // 3. 简单计算（平均成绩）
    averageScore = (mathScore + englishScore) / 2;

    // 4. 条件判断（成绩等级判断）
    string grade;
    if (averageScore >= 90) {
        grade = "优秀";
    } else if (averageScore >= 80) {
        grade = "良好";
    } else if (averageScore >= 60) {
        grade = "及格";
    } else {
        grade = "不及格";
    }

    // 5. 循环演示（打印3次结果提示）
    cout << "\n===== 你的信息汇总 =====" << endl;
    for (int i = 0; i < 1; i++) {  // 简化为1次打印，如需多轮可修改循环次数
        cout << "姓名：" << name << endl;
        cout << "年龄：" << age << "岁" << endl;
        cout << "数学成绩：" << mathScore << "，英语成绩：" << englishScore << endl;
        cout << "平均成绩：" << averageScore << "，等级：" << grade << endl;
    }

    // 6. 程序结束提示
    cout << "\n按回车键退出程序...";
    cin.ignore();  // 清除输入缓冲区残留
    cin.get();     // 等待用户按回车

    return 0;
}

   
