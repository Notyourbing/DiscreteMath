/*2252750 赵卓冰*/
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;


// 逻辑变元结构体
struct Variable {
  char name; // 变元的名字
  int value; // 变元的值

  Variable(const char init_name, const int init_value) : name(init_name), value(init_value) {}
};

// 变量名转换为变量值
int VarNameToValue(const vector<Variable>& variables, const char name) {
  for (auto var : variables) {
	if (name == var.name) {
	  return var.value;
	}
  }
}

// 打印标题和规则
void TitlePrint() {
  cout << "------------------------------------" << endl;
  cout << "|                                  |" << endl;
  cout << "|          欢迎进入逻辑软件        |" << endl;
  cout << "|（可运算真值表，主范式，支持括号）|" << endl;
  cout << "|                                  |" << endl;
  cout << "|           用 ! 表示非            |" << endl;
  cout << "|           用 & 表示与            |" << endl;
  cout << "|           用 | 表示或            |" << endl;
  cout << "|          用 ^ 表示蕴含           |" << endl;
  cout << "|          用 ~ 表示等值           |" << endl;
  cout << "|                                  |" << endl;
  cout << "|      用小写字母表示逻辑变元      |" << endl;
  cout << "|                                  |" << endl;
  cout << "------------------------------------" << endl;
  cout << endl;
}

// 判断是否是变元
bool IsVariable(const char ch) {
  return (ch >= 'a' && ch <= 'z');
}

// 判断是否是运算符（一共5种运算符）
bool IsOperator(const char ch) {
  if ('!' == ch || '&' == ch || '|' == ch || '^' == ch || '~' == ch) {
	return 1;
  }
  return 0;
}

// 输入表达式并验证合法性
string ExpressionInput() {
  while (true) {
    cout << endl << "请输入一个合法的表达式：" << endl;
    string expression;
    getline(cin, expression);

    // 去掉表达式中的空格，方便处理
    expression.erase(remove(expression.begin(), expression.end(), ' '), expression.end());

    bool isValid = true;  // 用于标记表达式是否合法

    // 1. 检查括号匹配
    stack<char> parens;
    for (char ch : expression) {
      if (ch == '(') {
        parens.push(ch);
      }
      else if (ch == ')') {
        if (parens.empty()) {
          cout << "错误：右括号多于左括号。" << endl;
          isValid = false;
          break;
        }
        parens.pop();
      }
    }
    if (!parens.empty()) {
      cout << "错误：左括号多于右括号。" << endl;
      isValid = false;
    }

    // 如果括号有问题，直接跳过后续检查
    if (!isValid) continue;

    // 2. 检查表达式的合法字符和结构
    bool expectVariable = true;  // 标记下一个字符是否期望是变元
    for (unsigned i = 0; i < expression.size(); ++i) {
      char ch = expression[i];

      // 如果是变元
      if (IsVariable(ch)) {
        if (!expectVariable) {
          cout << "错误：操作符缺失，变元 '" << ch << "' 之前需要运算符。" << endl;
          isValid = false;
          break;
        }
        expectVariable = false;  // 下一个应该是运算符或者右括号
      }
      // 如果是运算符
      else if (IsOperator(ch)) {
        if (expectVariable && ch != '!') {  // 单目运算符 "!" 可以在变元前面
          cout << "错误：运算符 '" << ch << "' 前面需要变元或右括号。" << endl;
          isValid = false;
          break;
        }
        expectVariable = true;  // 下一个应该是变元或左括号
      }
      // 左括号
      else if (ch == '(') {
        if (!expectVariable) {
          cout << "错误：左括号前不应该是变元或右括号。" << endl;
          isValid = false;
          break;
        }
        expectVariable = true;  // 左括号后应当是变元或 "!"
      }
      // 右括号
      else if (ch == ')') {
        if (expectVariable) {
          cout << "错误：右括号前需要变元或右括号。" << endl;
          isValid = false;
          break;
        }
        expectVariable = false;  // 右括号后应该是运算符或右括号
      }
      else {
        cout << "错误：非法字符 '" << ch << "'。" << endl;
        isValid = false;
        break;
      }
    }

    // 如果结构有问题，重新输入
    if (!isValid) continue;

    // 检查最后一个字符是否是非法的运算符
    if (expectVariable) {
      cout << "错误：表达式不能以运算符结尾。" << endl;
      continue;
    }

    return expression;  // 如果表达式合法，返回输入的表达式
  }
}

// 用于逻辑变元向量的按照字母序升序排序
bool CompareVar(Variable v1, Variable v2) {
  return (v1.name < v2.name);
}

// 返回逻辑变元的向量,从a到z升序排序
vector<Variable> GetVariablesVec(const string& expression) {
  vector<Variable> variables;
  vector<bool> flag(26, 0); // 0表示逻辑变元没有存进向量，1表示存过了
  for (auto element : expression) {
	if (IsVariable(element) && !flag[element - 'a']) { // 如果是逻辑变元并且没有存过
	  variables.push_back(Variable(element, 0));
	  flag[element - 'a'] = 1;
	}
  }
  sort(variables.begin(), variables.end(), CompareVar); // 升序排序
  return variables;
}

// 返回操作符op的优先级，越大表示优先级越高
int GetPrecedence(const char op) {
  if ('!' == op)
	return 4; // 优先级最高
  if ('&' == op)
	return 3;
  if ('|' == op)
	return 2;
  if ('^' == op)
	return 1;
  if ('~' == op)
	return 0;
  
  return -1;
}

// 执行运算操作
int ApplyOperator(const char op, const int left, const int right) {
  switch (op) {
  case '!': return !right;
  case '&': return left & right;
  case '|': return left | right;
  case '^': return (!left | right);
  case '~': return (left == right);
  default: return 0;
  }
}

// 处理栈顶操作符，并将结果压入操作数栈
// 输入参数： operands 操作数栈; operators 操作符栈
void ProcessTopOperator(stack<int>& operands, stack<char>& operators) {
  // 取出栈顶的操作符
  char op = operators.top();
  operators.pop();

  int right = operands.top(); // 单目和双目运算符都需要right这个操作数
  operands.pop();

  int left = 0;
  if (op != '!') { // 如果是双目运算符
	left = operands.top(); // 从栈顶取出left操作数
	operands.pop();
  }

  operands.push(ApplyOperator(op, left, right)); // 将计算的结果压入操作数栈
}

// 计算表达式，返回表达式的结果
int EvaluateExpression(const string& expression, const vector<Variable>& variables) {
  stack<int> operands; // 操作数栈
  stack<char> operators; // 操作符栈

  // 遍历表达式的每一个字符
  for (unsigned i = 0; i < expression.size(); ++i) {
	char ch = expression[i];
	if (' ' == ch) { // 如果是空格
	  continue;
	}
	if ('(' == ch) { // 如果是左括号
	  operators.push(ch); // 入栈
	}
	else if (')' == ch) { // 如果是右括号,不断处理栈顶的操作符，直到遇到左括号
	  while (operators.top() != '(') {
		ProcessTopOperator(operands, operators);
	  }
	  operators.pop(); // 弹出左括号
	}
	else if (IsVariable(ch)) { // 如果是操作数（逻辑变元）
	  operands.push(VarNameToValue(variables, ch)); // 操作数入栈
	}
	else if (IsOperator(ch)) { // 如果是操作符
	  // 当操作符栈非空，且当前操作符的优先级小于等于（因为是左结合，所以加上等于）栈顶操作符的优先级
	  while (!operators.empty() && GetPrecedence(ch) <= GetPrecedence(operators.top())) {
		ProcessTopOperator(operands, operators); // 处理栈顶操作符
	  }
	  operators.push(ch); // 压当前操作符入栈
	}
  }

  while (!operators.empty()) { // 当还有剩余的操作符
	ProcessTopOperator(operands, operators); // 处理栈顶操作符
  }

  return operands.top(); // 返回操作数栈顶的结果
}

// 打印真值表, 返回真值表结果
vector<int> TruthTable(const string& expression, vector<Variable>& variables) {
  cout<< endl << "--------------真值表------------------" << endl;
  cout << setiosflags(ios::left);
  cout << setw(4 * variables.size()) << "逻辑变元"<< "    " << "逻辑表达式" << endl;

  for (auto var : variables) {
	cout << setw(4) << var.name; 
  }
  cout<< "    " << expression << endl;
  vector<int> table_res;

  unsigned var_num = variables.size(); // 变元数量
  unsigned row = 1 << var_num; // 真值表的行数， 也就是2^n
  for (unsigned i = 0; i < row; ++i) { // 遍历每一行
	for (unsigned j = 0; j < var_num; ++j) { // 遍历每一个变元,也就是每一列
	  variables[j].value = i >> (var_num - 1 - j) & 1; // 把i右移(var_num-1-j)位，然后取最低位
	  cout << setw(4) << variables[j].value;
	}
	int expressionValue = EvaluateExpression(expression, variables); // 计算表达式的值
	table_res.push_back(expressionValue); // 将表达式的值加入真值表结果
	cout<< "    "<< setw(expression.length() / 2) << " " << expressionValue << endl; // 输出
  }

  cout << endl << "--------------------------------------" << endl;
  
  return table_res;
}

// 打印主析取范式和主合取范式
void PrintForm(const vector<int>& table_res) {
  vector<int> dnf; // 主析取范式
  vector<int> cnf; // 主合取范式
  for (unsigned i = 0; i < table_res.size(); ++i) {
	if (table_res[i]) { // 赋值成真，得到极小项i
	  dnf.push_back(i);
	}
	else { // 成假赋值，得到极大项i
	  cnf.push_back(i);
	}
  }
  cout<< endl << "-------------表达式的主范式---------------------" << endl;
  cout << "主析取范式：    ";
  for (auto min_i : dnf) {
	cout << "m(" << min_i << ")";
	if (min_i != dnf.back()) {
	  cout << "\\/";
	}
	else {
	  cout << endl;
	}
  }
  cout << endl;
  cout << "主合取范式：    ";
  for (auto max_i : cnf) {
	cout << "M(" << max_i << ")";
	if (max_i != cnf.back()) {
	  cout << "/\\";
	}
	else {
	  cout << endl;
	}
  }
  cout << "------------------------------------------------" << endl;
}

int main() {
  TitlePrint();
  while (1) {
	string expression = ExpressionInput(); // 输入表达式
	vector<Variable> variables = GetVariablesVec(expression); // 根据表达式得到逻辑变元向量
	cout << endl << "该式子中变元的个数为：" << variables.size() << endl;

	vector<int> table_res = TruthTable(expression, variables); // 打印真值表，得到真值表结果
	PrintForm(table_res); // 根据真值表结果打印主范式

	cout << endl << "是否继续运算？（y/n)" << endl;
	char ch;
	cin >> ch;
	if (ch == 'n' || ch == 'N') {
	  break;
	}
	cin.clear();
	cin.ignore(65536, '\n');
  }

  return 0;
}