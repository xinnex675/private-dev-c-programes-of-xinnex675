#include <iostream>
#include <string>
using namespace std;

// �������ܣ��򵥵ĸ�����Ϣ¼����ɼ��ж�
int main() {
    // 1. �����������
    string name;
    int age;
    float mathScore, englishScore;
    float averageScore;

    // 2. �Ѻ���ʾ����Ϣ����
    cout << "===== ������Ϣ¼�빤�� =====" << endl;
    cout << "���������������";
    getline(cin, name);  // ��ȡ�����ո������

    cout << "������������䣺";
    cin >> age;

    cout << "��������ѧ�ɼ���";
    cin >> mathScore;
    cout << "������Ӣ��ɼ���";
    cin >> englishScore;

    // 3. �򵥼��㣨ƽ���ɼ���
    averageScore = (mathScore + englishScore) / 2;

    // 4. �����жϣ��ɼ��ȼ��жϣ�
    string grade;
    if (averageScore >= 90) {
        grade = "����";
    } else if (averageScore >= 80) {
        grade = "����";
    } else if (averageScore >= 60) {
        grade = "����";
    } else {
        grade = "������";
    }

    // 5. ѭ����ʾ����ӡ3�ν����ʾ��
    cout << "\n===== �����Ϣ���� =====" << endl;
    for (int i = 0; i < 1; i++) {  // ��Ϊ1�δ�ӡ��������ֿ��޸�ѭ������
        cout << "������" << name << endl;
        cout << "���䣺" << age << "��" << endl;
        cout << "��ѧ�ɼ���" << mathScore << "��Ӣ��ɼ���" << englishScore << endl;
        cout << "ƽ���ɼ���" << averageScore << "���ȼ���" << grade << endl;
    }

    // 6. ���������ʾ
    cout << "\n���س����˳�����...";
    cin.ignore();  // ������뻺��������
    cin.get();     // �ȴ��û����س�

    return 0;
}

   
