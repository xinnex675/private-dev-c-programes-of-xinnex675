#include <iostream>
#include <string>
#include <iomanip>
#include <windows.h> // 用于控制台颜色控制（Dev-C++支持）

using namespace std;

// 颜色定义
enum Color {
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    BROWN = 6,
    LIGHTGRAY = 7,
    DARKGRAY = 8,
    LIGHTBLUE = 9,
    LIGHTGREEN = 10,
    LIGHTCYAN = 11,
    LIGHTRED = 12,
    LIGHTMAGENTA = 13,
    YELLOW = 14,
    WHITE = 15
};

// 设置控制台文本颜色
void setColor(int textColor, int bgColor = BLACK) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgColor << 4) | textColor);
}

// 光标定位
void setCursorPosition(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// 绘制水平线
void drawHorizontalLine(int length, char symbol = '-') {
    for(int i = 0; i < length; i++) {
        cout << symbol;
    }
    cout << endl;
}

// 学生结构体
struct Student {
    string name;
    int id;
    float score;
};

// 函数声明
void addStudent(Student students[], int &count, int maxSize);
void displayStudents(Student students[], int count);
void calculateStatistics(Student students[], int count);
void showMenu();
void printTitle(const string &title);
void pauseScreen();

int main() {
    // 设置控制台标题
    SetConsoleTitleA("学生成绩管理系统");
    
    const int MAX_STUDENTS = 50;
    Student students[MAX_STUDENTS];
    int studentCount = 0;
    int choice;
    
    do {
        system("cls");
        showMenu();
        
        setColor(CYAN);
        cout << "\n请输入您的选择 (1-4): ";
        setColor(WHITE);
        cin >> choice;
        cin.ignore(); // 清除输入缓冲区
        
        switch(choice) {
            case 1:
                system("cls");
                printTitle("添加学生信息");
                addStudent(students, studentCount, MAX_STUDENTS);
                pauseScreen();
                break;
            case 2:
                system("cls");
                printTitle("学生信息列表");
                displayStudents(students, studentCount);
                pauseScreen();
                break;
            case 3:
                system("cls");
                printTitle("成绩统计信息");
                calculateStatistics(students, studentCount);
                pauseScreen();
                break;
            case 4:
                system("cls");
                setColor(YELLOW);
                drawHorizontalLine(50, '=');
                cout << setw(30) << "感谢使用本系统！" << endl;
                drawHorizontalLine(50, '=');
                setColor(WHITE);
                break;
            default:
                setColor(LIGHTRED);
                cout << "\n无效的选择！请输入1到4之间的数字。" << endl;
                setColor(WHITE);
                pauseScreen();
        }
    } while(choice != 4);
    
    return 0;
}

// 显示带装饰的标题
void printTitle(const string &title) {
    setColor(YELLOW);
    drawHorizontalLine(50, '=');
    cout << setw((50 + title.length()) / 2) << title << endl;
    drawHorizontalLine(50, '=');
    setColor(WHITE);
    cout << endl;
}

// 显示菜单
void showMenu() {
    printTitle("学生成绩管理系统");
    
    setColor(LIGHTGREEN);
    cout << "【1】添加学生信息" << endl << endl;
    cout << "【2】查看学生列表" << endl << endl;
    cout << "【3】成绩统计分析" << endl << endl;
    cout << "【4】退出系统" << endl;
    setColor(WHITE);
}

// 添加学生信息
void addStudent(Student students[], int &count, int maxSize) {
    if(count >= maxSize) {
        setColor(LIGHTRED);
        cout << "错误：已达到最大学生数量限制 (" << maxSize << "人)！" << endl;
        setColor(WHITE);
        return;
    }
    
    Student s;
    
    setColor(LIGHTCYAN);
    cout << "请输入学生信息：" << endl;
    drawHorizontalLine(40);
    setColor(WHITE);
    
    cout << "姓名: ";
    getline(cin, s.name);
    
    cout << "ID号: ";
    cin >> s.id;
    
    cout << "成绩: ";
    cin >> s.score;
    
    // 验证成绩是否有效
    while(s.score < 0 || s.score > 100) {
        setColor(LIGHTRED);
        cout << "成绩无效！请输入0-100之间的数值: ";
        setColor(WHITE);
        cin >> s.score;
    }
    
    students[count] = s;
    count++;
    
    setColor(LIGHTGREEN);
    cout << "\n√ 学生信息添加成功！当前共 " << count << " 名学生" << endl;
    setColor(WHITE);
}

// 显示所有学生信息
void displayStudents(Student students[], int count) {
    if(count == 0) {
        setColor(LIGHTRED);
        cout << "暂无学生信息可显示！" << endl;
        setColor(WHITE);
        return;
    }
    
    // 表头
    setColor(CYAN);
    cout << left << setw(5) << "序号" 
         << setw(20) << "姓名" 
         << setw(15) << "ID号" 
         << setw(10) << "成绩" 
         << setw(10) << "等级" << endl;
    drawHorizontalLine(60);
    setColor(WHITE);
    
    // 内容
    for(int i = 0; i < count; i++) {
        cout << left << setw(5) << (i + 1);
        cout << setw(20) << students[i].name;
        cout << setw(15) << students[i].id;
        
        // 根据成绩显示不同颜色
        if(students[i].score >= 90) {
            setColor(GREEN);
        } else if(students[i].score >= 60) {
            setColor(WHITE);
        } else {
            setColor(RED);
        }
        
        cout << setw(10) << fixed << setprecision(1) << students[i].score;
        
        // 显示等级
        if(students[i].score >= 90) {
            cout << setw(10) << "优秀" << endl;
        } else if(students[i].score >= 80) {
            cout << setw(10) << "良好" << endl;
        } else if(students[i].score >= 60) {
            cout << setw(10) << "及格" << endl;
        } else {
            cout << setw(10) << "不及格" << endl;
        }
        setColor(WHITE);
    }
}

// 计算成绩统计信息
void calculateStatistics(Student students[], int count) {
    if(count == 0) {
        setColor(LIGHTRED);
        cout << "暂无学生信息可统计！" << endl;
        setColor(WHITE);
        return;
    }
    
    float sum = 0, average, highest = students[0].score, lowest = students[0].score;
    int passCount = 0, excellentCount = 0;
    
    for(int i = 0; i < count; i++) {
        sum += students[i].score;
        
        if(students[i].score > highest) highest = students[i].score;
        if(students[i].score < lowest) lowest = students[i].score;
        if(students[i].score >= 60) passCount++;
        if(students[i].score >= 90) excellentCount++;
    }
    
    average = sum / count;
    
    setColor(LIGHTBLUE);
    cout << "统计结果：" << endl;
    drawHorizontalLine(40);
    setColor(WHITE);
    
    cout << left << setw(25) << "总人数：" << count << " 人" << endl;
    cout << left << setw(25) << "平均分：" << fixed << setprecision(1) << average << endl;
    
    setColor(GREEN);
    cout << left << setw(25) << "最高分：" << fixed << setprecision(1) << highest << endl;
    setColor(RED);
    cout << left << setw(25) << "最低分：" << fixed << setprecision(1) << lowest << endl;
    setColor(WHITE);
    
    cout << left << setw(25) << "及格率：" << fixed << setprecision(1) 
         << (passCount * 100.0 / count) << "%" << endl;
    cout << left << setw(25) << "优秀率（90分以上）：" << fixed << setprecision(1) 
         << (excellentCount * 100.0 / count) << "%" << endl;
}

// 暂停屏幕等待用户操作
void pauseScreen() {
    setColor(CYAN);
    cout << "\n\n按回车键继续...";
    setColor(WHITE);
    cin.get();
}
    

