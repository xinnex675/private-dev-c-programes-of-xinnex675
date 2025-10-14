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
    cout << "请输入成绩:" ,cin >> num;
	printf("你的成绩是：%d\n",num);
	
	srand((unsigned int) time (NULL));
	int colorCode[] = {31,32,33,34,35,36,37,90} ;
	
	for(int i =1 ; i<=10000;i++ )
    {
	    int randomColor = colorCode[rand()%8];
        cout << "\033[" << randomColor <<  "m" << "卧槽，真牛逼！！！"<<"\033[0m" ;
    }
    return 0;
 } 
