#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    // ��ʼ�������������
    srand(time(0));
    int secretNumber = rand() % 100 + 1; // ����1-100�������
    int guess;
    int attempts = 0;

    cout << "��������Ϸ�����Ѿ������һ��1-100֮������֡�" << endl;

    // ������ѭ��
    do {
        cout << "��������Ĳ²�: ";
        cin >> guess;
        attempts++;

        if (guess > secretNumber) {
            cout << "̫���ˣ������ԡ�" << endl;
        } else if (guess < secretNumber) {
            cout << "̫С�ˣ������ԡ�" << endl;
        } else {
            cout << "��ϲ��¶��ˣ����� " << secretNumber 
                 << "�������� " << attempts << " �β¶ԡ�" << endl;
        }
    } while (guess != secretNumber);

    return 0;
}
    
