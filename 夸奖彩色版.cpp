#include<iostream>
#include<string>
#include<cstdlib>
#include<ctime> 
using namespace std;
void initDevColor(){
	 system("chcp 936 > nul");
	 system("cls");
}


int main()
{  
    initDevColor();
	int num ;
    cout << "������ɼ�:" ,cin >> num;
	printf("��ĳɼ��ǣ�%d\n",num);
	
	srand((unsigned int) time (NULL));
	int colorCode[] = {31,32,33,34,35,36,37,90} ;
	
	for(int i =1 ; i<=10000;i++ )
    {
	    int randomColor = colorCode[rand()%8];
        cout << "\033[" << randomColor <<  "m" << "�Բۣ���ţ�ƣ�����"<<"\033[0m" ;
    }
    return 0;
 } 
