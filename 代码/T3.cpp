#include <iostream>
#include <vector>
using namespace std;

// 关系矩阵类
class Matrix {
private:
	vector<vector<int>> data; // 存储矩阵数据的二维vector
	size_t size;              // 矩阵的大小（行数和列数）
public:
	// 构造函数：初始化大小为input_size的矩阵，并将所有元素设置为0
	Matrix(const size_t input_size) {
		size = input_size;
		// 给矩阵分配内存，并将所有元素初始化为0
		data.assign(size, vector<int>(size, 0));
	}

	// 用另一个Matrix对象来初始化
	Matrix(const Matrix& other) {
		size = other.size;
		data = other.data;
	}

	// 析构函数：因为使用的是vector容器，内存会自动释放，什么也不做
	~Matrix() {}

	// 返回矩阵的大小
	size_t Size() {
		return size;
	}

	// 重载[]运算符，用于返回第i行的引用
	vector<int>& operator[](const size_t i) {
		if (i > size - 1) {
			throw::out_of_range("Matrix index out of range"); // 超出范围异常
		}
		return data[i];
	}

	// const引用，适用于const对象
	const vector<int>& operator[](const size_t i) const {
		return data[i];
	}

	// 矩阵的转置
	Matrix Trans() {
		Matrix result(size); // 创建一个与原矩阵同样大小的矩阵
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j) {
				result[i][j] = data[j][i]; // 将原矩阵的(i, j)元素放置到转置矩阵的(j, i)位置
			}
		}
		return result;
	}

	// 重载+运算符，表示矩阵的逻辑加法（并集）
	Matrix operator+(const Matrix& other) {
		if (other.size != size) {
			throw::invalid_argument("矩阵的维度不同"); // 矩阵维度不同，不能进行加法
		}
		Matrix result(size); // 结果矩阵
		for (size_t i = 0; i < size; ++i) {
			for (size_t j = 0; j < size; ++j) {
				result[i][j] = data[i][j] || other[i][j]; // 逻辑“或”操作（并集）
			}
		}
		return result;
	}

	// 重载*运算符，表示矩阵的乘法（逻辑与运算）
	Matrix operator*(const Matrix& other) {
		if (other.size != size) {
			throw::invalid_argument("矩阵的维度不同"); // 矩阵维度不同，不能进行乘法
		}
		Matrix result(size); // 结果矩阵
		for (size_t i = 0; i < size; ++i) {
			for (size_t j = 0; j < size; ++j) {
				for (size_t k = 0; k < size; ++k) {
					result[i][j] = result[i][j] || (data[i][k] && other[k][j]); // 逻辑与操作，然后逻辑“或”累加
				}
			}
		}
		return result;
	}

	// 输入矩阵数据
	void Input() {
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j) {
				cin >> data[i][j]; // 从输入读取数据
			}
		}
	}

	// 打印矩阵
	void Disp() {
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j) {
				cout << data[i][j] << ' '; // 输出矩阵元素
			}
			cout << endl;
		}
	}
};

// 求自反闭包
Matrix ReflexiveClosure(Matrix& matrix) {
	// 创建一个单位矩阵
	Matrix identity_matrix(matrix.Size());
	// 主对角线元素全部设为1，表示自反关系
	for (int i = 0; i < matrix.Size(); ++i) {
		identity_matrix[i][i] = 1;
	}

	// 自反闭包=单位矩阵+关系矩阵
	return identity_matrix + matrix;
}

// 求传递闭包
Matrix TransitiveClosure(Matrix& matrix) {
	// 创建结果矩阵，初始化为关系矩阵
	Matrix result(matrix);
	// 通过迭代计算，累积R + R^2 + ... + R^n，直到收敛
	for (int i = 0; i < matrix.Size() - 1; ++i) {
		result = result * matrix + matrix; // 每次更新矩阵的值
	}
	return result;
}

// 求对称闭包
Matrix SymmetricClosure(Matrix& matrix) {
	// 创建结果矩阵，初始化为关系矩阵
	Matrix result(matrix);
	// 对称闭包=关系矩阵+关系矩阵的转置
	result = result + matrix.Trans();
	return result;
}

int main() {
	size_t size;
	cout << "请输入矩阵的阶数：" << endl;
	cin >> size; // 输入矩阵的阶数（大小）
	cout << "请输入关系矩阵：" << endl;
	Matrix matrix(size); // 创建矩阵对象
	matrix.Input(); // 输入矩阵数据

	// 提供菜单供用户选择
	while (1) {
		cout << "----------------------" << endl;
		cout << "|输入对应序号选择算法|" << endl;
		cout << "|    1--自反闭包     |" << endl;
		cout << "|    2--传递闭包     |" << endl;
		cout << "|    3--对称闭包     |" << endl;
		cout << "|    4--退出         |" << endl;
		cout << "----------------------" << endl;
		int choice;
		cin >> choice; // 用户输入选择的操作

		// 清除输入错误的状态
		if (cin.fail()) {
			cin.clear();
			cin.ignore(65536, '\n');
		}

		// 根据用户的选择执行不同的操作
		if (1 == choice) {
			// 计算自反闭包
			Matrix reflexive_closure = ReflexiveClosure(matrix);
			cout << "自反闭包为：" << endl;
			reflexive_closure.Disp(); // 输出自反闭包
		}
		else if (2 == choice) {
			// 计算传递闭包
			Matrix transitive_closure = TransitiveClosure(matrix);
			cout << "传递闭包为：" << endl;
			transitive_closure.Disp(); // 输出传递闭包
		}
		else if (3 == choice) {
			// 计算对称闭包
			Matrix symmetric_closure = SymmetricClosure(matrix);
			cout << "对称闭包为：" << endl;
			symmetric_closure.Disp(); // 输出对称闭包
		}
		if (4 == choice) {
			// 用户选择退出
			break;
		}
	}
	return 0;
}
