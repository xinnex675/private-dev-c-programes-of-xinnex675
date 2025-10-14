#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

// ��ɫ����
const int COLOR_BLACK = 0;
const int COLOR_DARKGREEN = 2;
const int COLOR_GREEN = 10;
const int COLOR_LIGHTGREEN = 14;

// �нṹ��
struct Column {
    int x;              // X����
    int y;              // ͷ��Y����
    int length;         // ����
    int speed;          // �ٶ�
    int updateRate;     // ����Ƶ��
    int updateCounter;  // ���¼�����
};

// �����ı���ɫ
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// ���ù��λ��
void setCursorPos(int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {static_cast<SHORT>(x), static_cast<SHORT>(y)};
    SetConsoleCursorPosition(hConsole, coord);
}

// ���ع��
void hideCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo = {sizeof(cursorInfo), FALSE};
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

// ��ȡ����̨�ߴ�
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

// ��������ַ����Ż����֣�
char getRandomChar() {
    // �����ַ�����Ԥ���㳤�ȣ����Ч��
    static const char chars[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static const int charCount = sizeof(chars) - 1; // Ԥ��������ظ�����
    return chars[rand() % charCount]; // ʹ��Ԥ����ĳ���
}

// ��ʼ����
void initColumn(Column &col, int width, int height) {
    col.x = rand() % width;
    col.y = - (rand() % height);
    col.length = 3 + rand() % 12;
    col.speed = 1 + rand() % 2;
    col.updateRate = 1 + rand() % 3;
    col.updateCounter = 0;
}

// ������
void updateColumn(Column &col, int height) {
    col.y += col.speed;
    col.updateCounter++;
    
    if (col.y > height + col.length) {
        col.y = - (rand() % height);
        col.length = 3 + rand() % 12;
        col.speed = 1 + rand() % 2;
    }
}

// ������
void drawColumn(const Column &col, int height, vector<vector<char>> &charBuffer) {
    // ����ͷ��
    if (col.y >= 0 && col.y < height) {
        setCursorPos(col.x, col.y);
        setColor(COLOR_LIGHTGREEN);
        char c = getRandomChar();
        charBuffer[col.y][col.x] = c;
        cout << c;
    }
    
    // ��������
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
    
    // ���β��
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
    SetConsoleTitleA("������Ч��");
    
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
    cout << "��ESC���˳�";
    
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
    
