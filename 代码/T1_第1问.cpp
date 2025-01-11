/*2252750 赵卓冰*/
#include <iostream>
using namespace std;

// 打印标题
void TitlePrint() {
  cout << "-------------------------------------------" << endl;
  cout << "|                                         |" << endl;
  cout << "|          欢迎进入逻辑运算软件           |" << endl;
  cout << "|                                         |" << endl;
  cout << "-------------------------------------------" << endl <<endl;
}

// 输入变量
void VarInput(int& p, int& q) {
  cout << "请输入P的值（0或1），以回车结束：";
  cin >> p;
  while (cin.fail() || (p != 0 && p != 1)) {
	cout << endl;
	cout << "P的值输入有误，请重新输入" << endl;;
	cout << "请输入P的值（0或1），以回车结束：";
	cin.clear();
	cin.ignore(65535, '\n');
	cin >> p;
  }

  cout << "请输入Q的值（0或1），以回车结束：";
  cin >> q;
  while (cin.fail() || (q != 0 && q != 1)) {
	cout << endl;
	cout << "Q的值输入有误，请重新输入" << endl;
	cout << "请输入Q的值（0或1），以回车结束：";
	cin.clear();
	cin.ignore(65535, '\n');
	cin >> q;
  }
}

// 输出结果
void ResPrint(const int& p, const int& q) {
  printf("\n-------------逻辑运算结果如下------------\n");
  printf("|  合取  |         P/\\Q = %d             |\n", p & q);
  printf("|  析取  |         P\\/Q = %d             |\n", p | q);
  printf("|  条件  |         P->Q = %d             |\n", !p | q);
  printf("| 双条件 |         P<->Q = %d            |\n", p == q);
  printf("-----------------------------------------");
}

/*1. 从键盘输入两个命题变元P和Q的真值，求它们的合取、析取、条件和双向条件的真值。（A）*/
int main() {
  while (1) {
	TitlePrint();
	int p, q;
	VarInput(p, q);
	ResPrint(p, q);

	cout << endl << "是否继续运算？（y/n)" << endl;
	char ch;
	cin >> ch;
	if (ch == 'n' || ch == 'N') {
	  break;
	}
  }
  cout << "欢迎下次使用!" << endl;

  return 0;
}
