/*2252750 ��׿��*/
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;


// �߼���Ԫ�ṹ��
struct Variable {
  char name; // ��Ԫ������
  int value; // ��Ԫ��ֵ

  Variable(const char init_name, const int init_value) : name(init_name), value(init_value) {}
};

// ������ת��Ϊ����ֵ
int VarNameToValue(const vector<Variable>& variables, const char name) {
  for (auto var : variables) {
	if (name == var.name) {
	  return var.value;
	}
  }
}

// ��ӡ����͹���
void TitlePrint() {
  cout << "------------------------------------" << endl;
  cout << "|                                  |" << endl;
  cout << "|          ��ӭ�����߼����        |" << endl;
  cout << "|����������ֵ������ʽ��֧�����ţ�|" << endl;
  cout << "|                                  |" << endl;
  cout << "|           �� ! ��ʾ��            |" << endl;
  cout << "|           �� & ��ʾ��            |" << endl;
  cout << "|           �� | ��ʾ��            |" << endl;
  cout << "|          �� ^ ��ʾ�̺�           |" << endl;
  cout << "|          �� ~ ��ʾ��ֵ           |" << endl;
  cout << "|                                  |" << endl;
  cout << "|      ��Сд��ĸ��ʾ�߼���Ԫ      |" << endl;
  cout << "|                                  |" << endl;
  cout << "------------------------------------" << endl;
  cout << endl;
}

// �ж��Ƿ��Ǳ�Ԫ
bool IsVariable(const char ch) {
  return (ch >= 'a' && ch <= 'z');
}

// �ж��Ƿ����������һ��5���������
bool IsOperator(const char ch) {
  if ('!' == ch || '&' == ch || '|' == ch || '^' == ch || '~' == ch) {
	return 1;
  }
  return 0;
}

// ������ʽ����֤�Ϸ���
string ExpressionInput() {
  while (true) {
    cout << endl << "������һ���Ϸ��ı��ʽ��" << endl;
    string expression;
    getline(cin, expression);

    // ȥ�����ʽ�еĿո񣬷��㴦��
    expression.erase(remove(expression.begin(), expression.end(), ' '), expression.end());

    bool isValid = true;  // ���ڱ�Ǳ��ʽ�Ƿ�Ϸ�

    // 1. �������ƥ��
    stack<char> parens;
    for (char ch : expression) {
      if (ch == '(') {
        parens.push(ch);
      }
      else if (ch == ')') {
        if (parens.empty()) {
          cout << "���������Ŷ��������š�" << endl;
          isValid = false;
          break;
        }
        parens.pop();
      }
    }
    if (!parens.empty()) {
      cout << "���������Ŷ��������š�" << endl;
      isValid = false;
    }

    // ������������⣬ֱ�������������
    if (!isValid) continue;

    // 2. �����ʽ�ĺϷ��ַ��ͽṹ
    bool expectVariable = true;  // �����һ���ַ��Ƿ������Ǳ�Ԫ
    for (unsigned i = 0; i < expression.size(); ++i) {
      char ch = expression[i];

      // ����Ǳ�Ԫ
      if (IsVariable(ch)) {
        if (!expectVariable) {
          cout << "���󣺲�����ȱʧ����Ԫ '" << ch << "' ֮ǰ��Ҫ�������" << endl;
          isValid = false;
          break;
        }
        expectVariable = false;  // ��һ��Ӧ�������������������
      }
      // ����������
      else if (IsOperator(ch)) {
        if (expectVariable && ch != '!') {  // ��Ŀ����� "!" �����ڱ�Ԫǰ��
          cout << "��������� '" << ch << "' ǰ����Ҫ��Ԫ�������š�" << endl;
          isValid = false;
          break;
        }
        expectVariable = true;  // ��һ��Ӧ���Ǳ�Ԫ��������
      }
      // ������
      else if (ch == '(') {
        if (!expectVariable) {
          cout << "����������ǰ��Ӧ���Ǳ�Ԫ�������š�" << endl;
          isValid = false;
          break;
        }
        expectVariable = true;  // �����ź�Ӧ���Ǳ�Ԫ�� "!"
      }
      // ������
      else if (ch == ')') {
        if (expectVariable) {
          cout << "����������ǰ��Ҫ��Ԫ�������š�" << endl;
          isValid = false;
          break;
        }
        expectVariable = false;  // �����ź�Ӧ�����������������
      }
      else {
        cout << "���󣺷Ƿ��ַ� '" << ch << "'��" << endl;
        isValid = false;
        break;
      }
    }

    // ����ṹ�����⣬��������
    if (!isValid) continue;

    // ������һ���ַ��Ƿ��ǷǷ��������
    if (expectVariable) {
      cout << "���󣺱��ʽ�������������β��" << endl;
      continue;
    }

    return expression;  // ������ʽ�Ϸ�����������ı��ʽ
  }
}

// �����߼���Ԫ�����İ�����ĸ����������
bool CompareVar(Variable v1, Variable v2) {
  return (v1.name < v2.name);
}

// �����߼���Ԫ������,��a��z��������
vector<Variable> GetVariablesVec(const string& expression) {
  vector<Variable> variables;
  vector<bool> flag(26, 0); // 0��ʾ�߼���Ԫû�д��������1��ʾ�����
  for (auto element : expression) {
	if (IsVariable(element) && !flag[element - 'a']) { // ������߼���Ԫ����û�д��
	  variables.push_back(Variable(element, 0));
	  flag[element - 'a'] = 1;
	}
  }
  sort(variables.begin(), variables.end(), CompareVar); // ��������
  return variables;
}

// ���ز�����op�����ȼ���Խ���ʾ���ȼ�Խ��
int GetPrecedence(const char op) {
  if ('!' == op)
	return 4; // ���ȼ����
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

// ִ���������
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

// ����ջ�����������������ѹ�������ջ
// ��������� operands ������ջ; operators ������ջ
void ProcessTopOperator(stack<int>& operands, stack<char>& operators) {
  // ȡ��ջ���Ĳ�����
  char op = operators.top();
  operators.pop();

  int right = operands.top(); // ��Ŀ��˫Ŀ���������Ҫright���������
  operands.pop();

  int left = 0;
  if (op != '!') { // �����˫Ŀ�����
	left = operands.top(); // ��ջ��ȡ��left������
	operands.pop();
  }

  operands.push(ApplyOperator(op, left, right)); // ������Ľ��ѹ�������ջ
}

// ������ʽ�����ر��ʽ�Ľ��
int EvaluateExpression(const string& expression, const vector<Variable>& variables) {
  stack<int> operands; // ������ջ
  stack<char> operators; // ������ջ

  // �������ʽ��ÿһ���ַ�
  for (unsigned i = 0; i < expression.size(); ++i) {
	char ch = expression[i];
	if (' ' == ch) { // ����ǿո�
	  continue;
	}
	if ('(' == ch) { // �����������
	  operators.push(ch); // ��ջ
	}
	else if (')' == ch) { // �����������,���ϴ���ջ���Ĳ�������ֱ������������
	  while (operators.top() != '(') {
		ProcessTopOperator(operands, operators);
	  }
	  operators.pop(); // ����������
	}
	else if (IsVariable(ch)) { // ����ǲ��������߼���Ԫ��
	  operands.push(VarNameToValue(variables, ch)); // ��������ջ
	}
	else if (IsOperator(ch)) { // ����ǲ�����
	  // ��������ջ�ǿգ��ҵ�ǰ�����������ȼ�С�ڵ��ڣ���Ϊ�����ϣ����Լ��ϵ��ڣ�ջ�������������ȼ�
	  while (!operators.empty() && GetPrecedence(ch) <= GetPrecedence(operators.top())) {
		ProcessTopOperator(operands, operators); // ����ջ��������
	  }
	  operators.push(ch); // ѹ��ǰ��������ջ
	}
  }

  while (!operators.empty()) { // ������ʣ��Ĳ�����
	ProcessTopOperator(operands, operators); // ����ջ��������
  }

  return operands.top(); // ���ز�����ջ���Ľ��
}

// ��ӡ��ֵ��, ������ֵ����
vector<int> TruthTable(const string& expression, vector<Variable>& variables) {
  cout<< endl << "--------------��ֵ��------------------" << endl;
  cout << setiosflags(ios::left);
  cout << setw(4 * variables.size()) << "�߼���Ԫ"<< "    " << "�߼����ʽ" << endl;

  for (auto var : variables) {
	cout << setw(4) << var.name; 
  }
  cout<< "    " << expression << endl;
  vector<int> table_res;

  unsigned var_num = variables.size(); // ��Ԫ����
  unsigned row = 1 << var_num; // ��ֵ��������� Ҳ����2^n
  for (unsigned i = 0; i < row; ++i) { // ����ÿһ��
	for (unsigned j = 0; j < var_num; ++j) { // ����ÿһ����Ԫ,Ҳ����ÿһ��
	  variables[j].value = i >> (var_num - 1 - j) & 1; // ��i����(var_num-1-j)λ��Ȼ��ȡ���λ
	  cout << setw(4) << variables[j].value;
	}
	int expressionValue = EvaluateExpression(expression, variables); // ������ʽ��ֵ
	table_res.push_back(expressionValue); // �����ʽ��ֵ������ֵ����
	cout<< "    "<< setw(expression.length() / 2) << " " << expressionValue << endl; // ���
  }

  cout << endl << "--------------------------------------" << endl;
  
  return table_res;
}

// ��ӡ����ȡ��ʽ������ȡ��ʽ
void PrintForm(const vector<int>& table_res) {
  vector<int> dnf; // ����ȡ��ʽ
  vector<int> cnf; // ����ȡ��ʽ
  for (unsigned i = 0; i < table_res.size(); ++i) {
	if (table_res[i]) { // ��ֵ���棬�õ���С��i
	  dnf.push_back(i);
	}
	else { // �ɼٸ�ֵ���õ�������i
	  cnf.push_back(i);
	}
  }
  cout<< endl << "-------------���ʽ������ʽ---------------------" << endl;
  cout << "����ȡ��ʽ��    ";
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
  cout << "����ȡ��ʽ��    ";
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
	string expression = ExpressionInput(); // ������ʽ
	vector<Variable> variables = GetVariablesVec(expression); // ���ݱ��ʽ�õ��߼���Ԫ����
	cout << endl << "��ʽ���б�Ԫ�ĸ���Ϊ��" << variables.size() << endl;

	vector<int> table_res = TruthTable(expression, variables); // ��ӡ��ֵ���õ���ֵ����
	PrintForm(table_res); // ������ֵ������ӡ����ʽ

	cout << endl << "�Ƿ�������㣿��y/n)" << endl;
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