#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

// 颜色定义
const int COLOR_BLACK = 0;
const int COLOR_DARKGREEN = 2;
const int COLOR_GREEN = 10;
const int COLOR_LIGHTGREEN = 14;

// 列结构体
struct Column {
    int x;              // X坐标
    int y;              // 头部Y坐标
    int length;         // 长度
    int speed;          // 速度
    int updateRate;     // 更新频率
    int updateCounter;  // 更新计数器
};

// 设置文本颜色
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// 设置光标位置
void setCursorPos(int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {static_cast<SHORT>(x), static_cast<SHORT>(y)};
    SetConsoleCursorPosition(hConsole, coord);
}

// 隐藏光标
void hideCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo = {sizeof(cursorInfo), FALSE};
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

// 获取控制台尺寸
void getConsoleSize(int &width, int &height) {
    width = 80;
    height = 25;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if(GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }
}

// 生成随机字符（优化部分）
char getRandomChar() {
    // 精简字符集并预计算长度，提高效率
    static const char chars[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static const int charCount = sizeof(chars) - 1; // 预计算避免重复计算
    return chars[rand() % charCount]; // 使用预计算的长度
}

// 初始化列
void initColumn(Column &col, int width, int height) {
    col.x = rand() % width;
    col.y = - (rand() % height);
    col.length = 3 + rand() % 12;
    col.speed = 1 + rand() % 2;
    col.updateRate = 1 + rand() % 3;
    col.updateCounter = 0;
}

// 更新列
void updateColumn(Column &col, int height) {
    col.y += col.speed;
    col.updateCounter++;
    
    if (col.y > height + col.length) {
        col.y = - (rand() % height);
        col.length = 3 + rand() % 12;
        col.speed = 1 + rand() % 2;
    }
}

// 绘制列
void drawColumn(const Column &col, int height, vector<vector<char>> &charBuffer) {
    // 绘制头部
    if (col.y >= 0 && col.y < height) {
        setCursorPos(col.x, col.y);
        setColor(COLOR_LIGHTGREEN);
        char c = getRandomChar();
        charBuffer[col.y][col.x] = c;
        cout << c;
    }
    
    // 绘制主体
    for (int i = 1; i < col.length; i++) {
        int pos = col.y - i;
        if (pos >= 0 && pos < height) {
            setCursorPos(col.x, pos);
            
            if (i < col.length / 3) {
                setColor(COLOR_GREEN);
            } else {
                setColor(COLOR_DARKGREEN);
            }
            
            if (col.updateCounter % col.updateRate == 0) {
                char c = getRandomChar();
                charBuffer[pos][col.x] = c;
                cout << c;
            } else {
                cout << charBuffer[pos][col.x];
            }
        }
    }
    
    // 清除尾部
    int clearPos = col.y - col.length;
    if (clearPos >= 0 && clearPos < height) {
        setCursorPos(col.x, clearPos);
        setColor(COLOR_BLACK);
        cout << ' ';
        charBuffer[clearPos][col.x] = ' ';
    }
}

int main() {
    srand(static_cast<unsigned int>(time(NULL)));
    hideCursor();
    SetConsoleTitleA("数字雨效果");
    
    int width, height;
    getConsoleSize(width, height);
    
    vector<vector<char>> charBuffer(height, vector<char>(width, ' '));
    const int COLUMN_COUNT = max(10, width / 3);
    vector<Column> columns(COLUMN_COUNT);
    for (auto &col : columns) {
        initColumn(col, width, height);
    }
    
    setCursorPos(1, 0);
    setColor(COLOR_GREEN);
    cout << "按ESC键退出";
    
    while (!(GetAsyncKeyState(VK_ESCAPE) & 0x8000)) {
        for (auto &col : columns) {
            updateColumn(col, height);
            drawColumn(col, height, charBuffer);
        }
        Sleep(60);
    }
    
    system("cls");
    setColor(15);
    return 0;
}
    
