/*2252750 ��׿��*/
#include <iostream>
using namespace std;

// ��ӡ����
void TitlePrint() {
  cout << "-------------------------------------------" << endl;
  cout << "|                                         |" << endl;
  cout << "|          ��ӭ�����߼��������           |" << endl;
  cout << "|                                         |" << endl;
  cout << "-------------------------------------------" << endl <<endl;
}

// �������
void VarInput(int& p, int& q) {
  cout << "������P��ֵ��0��1�����Իس�������";
  cin >> p;
  while (cin.fail() || (p != 0 && p != 1)) {
	cout << endl;
	cout << "P��ֵ������������������" << endl;;
	cout << "������P��ֵ��0��1�����Իس�������";
	cin.clear();
	cin.ignore(65535, '\n');
	cin >> p;
  }

  cout << "������Q��ֵ��0��1�����Իس�������";
  cin >> q;
  while (cin.fail() || (q != 0 && q != 1)) {
	cout << endl;
	cout << "Q��ֵ������������������" << endl;
	cout << "������Q��ֵ��0��1�����Իس�������";
	cin.clear();
	cin.ignore(65535, '\n');
	cin >> q;
  }
}

// ������
void ResPrint(const int& p, const int& q) {
  printf("\n-------------�߼�����������------------\n");
  printf("|  ��ȡ  |         P/\\Q = %d             |\n", p & q);
  printf("|  ��ȡ  |         P\\/Q = %d             |\n", p | q);
  printf("|  ����  |         P->Q = %d             |\n", !p | q);
  printf("| ˫���� |         P<->Q = %d            |\n", p == q);
  printf("-----------------------------------------");
}

/*1. �Ӽ����������������ԪP��Q����ֵ�������ǵĺ�ȡ����ȡ��������˫����������ֵ����A��*/
int main() {
  while (1) {
	TitlePrint();
	int p, q;
	VarInput(p, q);
	ResPrint(p, q);

	cout << endl << "�Ƿ�������㣿��y/n)" << endl;
	char ch;
	cin >> ch;
	if (ch == 'n' || ch == 'N') {
	  break;
	}
  }
  cout << "��ӭ�´�ʹ��!" << endl;

  return 0;
}
