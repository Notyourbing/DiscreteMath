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

// ���Է��հ�
Matrix ReflexiveClosure(Matrix& matrix) {
	// ����һ����λ����
	Matrix identity_matrix(matrix.Size());
	// ���Խ���Ԫ��ȫ����Ϊ1����ʾ�Է���ϵ
	for (int i = 0; i < matrix.Size(); ++i) {
		identity_matrix[i][i] = 1;
	}

	// �Է��հ�=��λ����+��ϵ����
	return identity_matrix + matrix;
}

// �󴫵ݱհ�
Matrix TransitiveClosure(Matrix& matrix) {
	// ����������󣬳�ʼ��Ϊ��ϵ����
	Matrix result(matrix);
	// ͨ���������㣬�ۻ�R + R^2 + ... + R^n��ֱ������
	for (int i = 0; i < matrix.Size() - 1; ++i) {
		result = result * matrix + matrix; // ÿ�θ��¾����ֵ
	}
	return result;
}

// ��ԳƱհ�
Matrix SymmetricClosure(Matrix& matrix) {
	// ����������󣬳�ʼ��Ϊ��ϵ����
	Matrix result(matrix);
	// �ԳƱհ�=��ϵ����+��ϵ�����ת��
	result = result + matrix.Trans();
	return result;
}

int main() {
	size_t size;
	cout << "���������Ľ�����" << endl;
	cin >> size; // �������Ľ�������С��
	cout << "�������ϵ����" << endl;
	Matrix matrix(size); // �����������
	matrix.Input(); // �����������

	// �ṩ�˵����û�ѡ��
	while (1) {
		cout << "----------------------" << endl;
		cout << "|�����Ӧ���ѡ���㷨|" << endl;
		cout << "|    1--�Է��հ�     |" << endl;
		cout << "|    2--���ݱհ�     |" << endl;
		cout << "|    3--�ԳƱհ�     |" << endl;
		cout << "|    4--�˳�         |" << endl;
		cout << "----------------------" << endl;
		int choice;
		cin >> choice; // �û�����ѡ��Ĳ���

		// �����������״̬
		if (cin.fail()) {
			cin.clear();
			cin.ignore(65536, '\n');
		}

		// �����û���ѡ��ִ�в�ͬ�Ĳ���
		if (1 == choice) {
			// �����Է��հ�
			Matrix reflexive_closure = ReflexiveClosure(matrix);
			cout << "�Է��հ�Ϊ��" << endl;
			reflexive_closure.Disp(); // ����Է��հ�
		}
		else if (2 == choice) {
			// ���㴫�ݱհ�
			Matrix transitive_closure = TransitiveClosure(matrix);
			cout << "���ݱհ�Ϊ��" << endl;
			transitive_closure.Disp(); // ������ݱհ�
		}
		else if (3 == choice) {
			// ����ԳƱհ�
			Matrix symmetric_closure = SymmetricClosure(matrix);
			cout << "�ԳƱհ�Ϊ��" << endl;
			symmetric_closure.Disp(); // ����ԳƱհ�
		}
		if (4 == choice) {
			// �û�ѡ���˳�
			break;
		}
	}
	return 0;
}
