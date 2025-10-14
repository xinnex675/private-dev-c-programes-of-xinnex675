#include <iostream>
#include <string>
#include <iomanip>
#include <windows.h> // ���ڿ���̨��ɫ���ƣ�Dev-C++֧�֣�

using namespace std;

// ��ɫ����
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

// ���ÿ���̨�ı���ɫ
void setColor(int textColor, int bgColor = BLACK) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgColor << 4) | textColor);
}

// ��궨λ
void setCursorPosition(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// ����ˮƽ��
void drawHorizontalLine(int length, char symbol = '-') {
    for(int i = 0; i < length; i++) {
        cout << symbol;
    }
    cout << endl;
}

// ѧ���ṹ��
struct Student {
    string name;
    int id;
    float score;
};

// ��������
void addStudent(Student students[], int &count, int maxSize);
void displayStudents(Student students[], int count);
void calculateStatistics(Student students[], int count);
void showMenu();
void printTitle(const string &title);
void pauseScreen();

int main() {
    // ���ÿ���̨����
    SetConsoleTitleA("ѧ���ɼ�����ϵͳ");
    
    const int MAX_STUDENTS = 50;
    Student students[MAX_STUDENTS];
    int studentCount = 0;
    int choice;
    
    do {
        system("cls");
        showMenu();
        
        setColor(CYAN);
        cout << "\n����������ѡ�� (1-4): ";
        setColor(WHITE);
        cin >> choice;
        cin.ignore(); // ������뻺����
        
        switch(choice) {
            case 1:
                system("cls");
                printTitle("���ѧ����Ϣ");
                addStudent(students, studentCount, MAX_STUDENTS);
                pauseScreen();
                break;
            case 2:
                system("cls");
                printTitle("ѧ����Ϣ�б�");
                displayStudents(students, studentCount);
                pauseScreen();
                break;
            case 3:
                system("cls");
                printTitle("�ɼ�ͳ����Ϣ");
                calculateStatistics(students, studentCount);
                pauseScreen();
                break;
            case 4:
                system("cls");
                setColor(YELLOW);
                drawHorizontalLine(50, '=');
                cout << setw(30) << "��лʹ�ñ�ϵͳ��" << endl;
                drawHorizontalLine(50, '=');
                setColor(WHITE);
                break;
            default:
                setColor(LIGHTRED);
                cout << "\n��Ч��ѡ��������1��4֮������֡�" << endl;
                setColor(WHITE);
                pauseScreen();
        }
    } while(choice != 4);
    
    return 0;
}

// ��ʾ��װ�εı���
void printTitle(const string &title) {
    setColor(YELLOW);
    drawHorizontalLine(50, '=');
    cout << setw((50 + title.length()) / 2) << title << endl;
    drawHorizontalLine(50, '=');
    setColor(WHITE);
    cout << endl;
}

// ��ʾ�˵�
void showMenu() {
    printTitle("ѧ���ɼ�����ϵͳ");
    
    setColor(LIGHTGREEN);
    cout << "��1�����ѧ����Ϣ" << endl << endl;
    cout << "��2���鿴ѧ���б�" << endl << endl;
    cout << "��3���ɼ�ͳ�Ʒ���" << endl << endl;
    cout << "��4���˳�ϵͳ" << endl;
    setColor(WHITE);
}

// ���ѧ����Ϣ
void addStudent(Student students[], int &count, int maxSize) {
    if(count >= maxSize) {
        setColor(LIGHTRED);
        cout << "�����Ѵﵽ���ѧ���������� (" << maxSize << "��)��" << endl;
        setColor(WHITE);
        return;
    }
    
    Student s;
    
    setColor(LIGHTCYAN);
    cout << "������ѧ����Ϣ��" << endl;
    drawHorizontalLine(40);
    setColor(WHITE);
    
    cout << "����: ";
    getline(cin, s.name);
    
    cout << "ID��: ";
    cin >> s.id;
    
    cout << "�ɼ�: ";
    cin >> s.score;
    
    // ��֤�ɼ��Ƿ���Ч
    while(s.score < 0 || s.score > 100) {
        setColor(LIGHTRED);
        cout << "�ɼ���Ч��������0-100֮�����ֵ: ";
        setColor(WHITE);
        cin >> s.score;
    }
    
    students[count] = s;
    count++;
    
    setColor(LIGHTGREEN);
    cout << "\n�� ѧ����Ϣ��ӳɹ�����ǰ�� " << count << " ��ѧ��" << endl;
    setColor(WHITE);
}

// ��ʾ����ѧ����Ϣ
void displayStudents(Student students[], int count) {
    if(count == 0) {
        setColor(LIGHTRED);
        cout << "����ѧ����Ϣ����ʾ��" << endl;
        setColor(WHITE);
        return;
    }
    
    // ��ͷ
    setColor(CYAN);
    cout << left << setw(5) << "���" 
         << setw(20) << "����" 
         << setw(15) << "ID��" 
         << setw(10) << "�ɼ�" 
         << setw(10) << "�ȼ�" << endl;
    drawHorizontalLine(60);
    setColor(WHITE);
    
    // ����
    for(int i = 0; i < count; i++) {
        cout << left << setw(5) << (i + 1);
        cout << setw(20) << students[i].name;
        cout << setw(15) << students[i].id;
        
        // ���ݳɼ���ʾ��ͬ��ɫ
        if(students[i].score >= 90) {
            setColor(GREEN);
        } else if(students[i].score >= 60) {
            setColor(WHITE);
        } else {
            setColor(RED);
        }
        
        cout << setw(10) << fixed << setprecision(1) << students[i].score;
        
        // ��ʾ�ȼ�
        if(students[i].score >= 90) {
            cout << setw(10) << "����" << endl;
        } else if(students[i].score >= 80) {
            cout << setw(10) << "����" << endl;
        } else if(students[i].score >= 60) {
            cout << setw(10) << "����" << endl;
        } else {
            cout << setw(10) << "������" << endl;
        }
        setColor(WHITE);
    }
}

// ����ɼ�ͳ����Ϣ
void calculateStatistics(Student students[], int count) {
    if(count == 0) {
        setColor(LIGHTRED);
        cout << "����ѧ����Ϣ��ͳ�ƣ�" << endl;
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
    cout << "ͳ�ƽ����" << endl;
    drawHorizontalLine(40);
    setColor(WHITE);
    
    cout << left << setw(25) << "��������" << count << " ��" << endl;
    cout << left << setw(25) << "ƽ���֣�" << fixed << setprecision(1) << average << endl;
    
    setColor(GREEN);
    cout << left << setw(25) << "��߷֣�" << fixed << setprecision(1) << highest << endl;
    setColor(RED);
    cout << left << setw(25) << "��ͷ֣�" << fixed << setprecision(1) << lowest << endl;
    setColor(WHITE);
    
    cout << left << setw(25) << "�����ʣ�" << fixed << setprecision(1) 
         << (passCount * 100.0 / count) << "%" << endl;
    cout << left << setw(25) << "�����ʣ�90�����ϣ���" << fixed << setprecision(1) 
         << (excellentCount * 100.0 / count) << "%" << endl;
}

// ��ͣ��Ļ�ȴ��û�����
void pauseScreen() {
    setColor(CYAN);
    cout << "\n\n���س�������...";
    setColor(WHITE);
    cin.get();
}
    

