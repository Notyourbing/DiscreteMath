#include <iostream>
#include <vector>
using namespace std;

// ��ϵ������
class Matrix {
private:
	vector<vector<int>> data; // �洢�������ݵĶ�άvector
	size_t size;              // ����Ĵ�С��������������
public:
	// ���캯������ʼ����СΪinput_size�ľ��󣬲�������Ԫ������Ϊ0
	Matrix(const size_t input_size) {
		size = input_size;
		// ����������ڴ棬��������Ԫ�س�ʼ��Ϊ0
		data.assign(size, vector<int>(size, 0));
	}

	// ����һ��Matrix��������ʼ��
	Matrix(const Matrix& other) {
		size = other.size;
		data = other.data;
	}

	// ������������Ϊʹ�õ���vector�������ڴ���Զ��ͷţ�ʲôҲ����
	~Matrix() {}

	// ���ؾ���Ĵ�С
	size_t Size() {
		return size;
	}

	// ����[]����������ڷ��ص�i�е�����
	vector<int>& operator[](const size_t i) {
		if (i > size - 1) {
			throw::out_of_range("Matrix index out of range"); // ������Χ�쳣
		}
		return data[i];
	}

	// const���ã�������const����
	const vector<int>& operator[](const size_t i) const {
		return data[i];
	}

	// �����ת��
	Matrix Trans() {
		Matrix result(size); // ����һ����ԭ����ͬ����С�ľ���
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j) {
				result[i][j] = data[j][i]; // ��ԭ�����(i, j)Ԫ�ط��õ�ת�þ����(j, i)λ��
			}
		}
		return result;
	}

	// ����+���������ʾ������߼��ӷ���������
	Matrix operator+(const Matrix& other) {
		if (other.size != size) {
			throw::invalid_argument("�����ά�Ȳ�ͬ"); // ����ά�Ȳ�ͬ�����ܽ��мӷ�
		}
		Matrix result(size); // �������
		for (size_t i = 0; i < size; ++i) {
			for (size_t j = 0; j < size; ++j) {
				result[i][j] = data[i][j] || other[i][j]; // �߼����򡱲�����������
			}
		}
		return result;
	}

	// ����*���������ʾ����ĳ˷����߼������㣩
	Matrix operator*(const Matrix& other) {
		if (other.size != size) {
			throw::invalid_argument("�����ά�Ȳ�ͬ"); // ����ά�Ȳ�ͬ�����ܽ��г˷�
		}
		Matrix result(size); // �������
		for (size_t i = 0; i < size; ++i) {
			for (size_t j = 0; j < size; ++j) {
				for (size_t k = 0; k < size; ++k) {
					result[i][j] = result[i][j] || (data[i][k] && other[k][j]); // �߼��������Ȼ���߼������ۼ�
				}
			}
		}
		return result;
	}

	// �����������
	void Input() {
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j) {
				cin >> data[i][j]; // �������ȡ����
			}
		}
	}

	// ��ӡ����
	void Disp() {
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j) {
				cout << data[i][j] << ' '; // �������Ԫ��
			}
			cout << endl;
		}
	}
};

Matrix Warshell(Matrix& matrix) {
	Matrix result(matrix);
	// �����м�ڵ�
	for (int k = 0; k < matrix.Size(); ++k) {
		for (int i = 0; i < matrix.Size(); ++i) {
			for (int j = 0; j < matrix.Size(); ++j) {
				result[i][j] = result[i][j] || (result[i][k] && result[k][j]);
			}
		}
	}
	return result;
}

int main() {
	size_t size;
	cout << "���������Ľ�����" << endl;
	cin >> size; // �������Ľ�������С��
	cout << "�������ϵ����" << endl;
	Matrix matrix(size); // �����������
	matrix.Input(); // �����������
	cout << endl << "��WarShell�㷨����Ĵ��ݱհ�Ϊ��" << endl;
	Warshell(matrix).Disp();

	return 0;
}