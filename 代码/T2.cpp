#include <iostream>
#include <conio.h>
using namespace std;

int main() {
	int A; // A偷了手表
	int B; // B偷了手表
	int C; // 作案在营业时间
	int D; // B的证据正确
	int E; // 货柜上锁

	for (A = 0; A <= 1; ++A) {
		for (B = 0; B <= 1; ++B) {
			for (C = 0; C <= 1; ++C) {
				for (D = 0; D <= 1; ++D) {
					for (E = 0; E <= 1; ++E) {
						int condition = (A || B) && (!A || !C) && (!D || !E) && (D || !C) && (E);
						if (condition) {
							cout << "A =" << A << ", B = " << B << endl;
							cout << endl << "按回车键退出..." << endl;
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