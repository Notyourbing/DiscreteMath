#include <iostream>
#include <conio.h>
using namespace std;

int main() {
	int A; // A͵���ֱ�
	int B; // B͵���ֱ�
	int C; // ������Ӫҵʱ��
	int D; // B��֤����ȷ
	int E; // ��������

	for (A = 0; A <= 1; ++A) {
		for (B = 0; B <= 1; ++B) {
			for (C = 0; C <= 1; ++C) {
				for (D = 0; D <= 1; ++D) {
					for (E = 0; E <= 1; ++E) {
						int condition = (A || B) && (!A || !C) && (!D || !E) && (D || !C) && (E);
						if (condition) {
							cout << "A =" << A << ", B = " << B << endl;
							cout << endl << "���س����˳�..." << endl;
							while (_getch() != '\r')
								continue;
							return 0;
						}
					}
				}
			}
		}
	}

	return 0;
}