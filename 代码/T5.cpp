#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include <iomanip>

using namespace std;

// ������������ڵ�ṹ��
struct HuffmanNode {
    char symbol;              // ����
    int frequency;            // Ƶ��
    HuffmanNode* left, * right; // ��������ָ��

    // �ڵ㹹�캯��
    HuffmanNode(char sym, int freq) : symbol(sym), frequency(freq), left(nullptr), right(nullptr) {}
};

// �Ƚ������������ȶ���
struct Compare {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->frequency > b->frequency; // ���ȶ�����Ƶ��С�Ľڵ�����
    }
};

// ������������
class Huffman {
private:
    HuffmanNode* root;                      // Huffman�����ڵ�
    unordered_map<char, string> symbol_codes_map;      // �洢�ַ��Ͷ�Ӧ��ǰ׺��
    unordered_map<char, int> symbol_freq_map;          // �洢�ַ��Ͷ�Ӧ��Ƶ��
    vector<pair<char, int>> frequencies;    // ������ַ��Ͷ�Ӧ��Ƶ��

    // ����������������ظ��ڵ�
    HuffmanNode* BuildTree() {
        // ������С�ѣ����ȶ��У�
        priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> min_heap;

        // ������Ƶ�ʺ��ַ�������С����
        for (const auto& entry : frequencies) {
            min_heap.push(new HuffmanNode(entry.first, entry.second));
        }

        // ������������
        while (min_heap.size() > 1) {
            // �Ӷ���ȡ����С�������ڵ�
            HuffmanNode* left = min_heap.top();
            min_heap.pop();
            HuffmanNode* right = min_heap.top();
            min_heap.pop();

            // �ϲ������ڵ㣬Ƶ����ӣ�����Ϊ'*'��ʾ��Ҷ�ӽڵ�
            HuffmanNode* merged = new HuffmanNode('*', left->frequency + right->frequency);
            merged->left = left;
            merged->right = right;

            min_heap.push(merged);
        }

        return min_heap.top(); // ���ظ��ڵ�
    }

    // �ݹ�����ǰ׺��
    void GenerateCodesRecursive(HuffmanNode* node, string code) {
        if (!node)
            return;

        // �����Ҷ�ӽ��
        if (!node->left && !node->right) {
            symbol_codes_map[node->symbol] = code; // �����ַ���ǰ׺��
        }

        // �ݹ���������������������ǰ׺��
        GenerateCodesRecursive(node->left, code + "0"); // ���֧��0
        GenerateCodesRecursive(node->right, code + "1"); // �ҷ�֧��1
    }

    // �ݹ��ӡǰ׺��
    void PrintCodesRecursive(HuffmanNode* node) {
        if (!node) {
            return;
        }
        // �����Ҷ�ӽ�㣬��ӡ�ַ�����Ƶ�ʺ�ǰ׺��
        if (!node->left && !node->right) {
            string temp = string(1, node->symbol) +
                "(" + std::to_string(symbol_freq_map[node->symbol]) + ")" + ":";
            cout << setiosflags(ios::left) << setw(10) << temp << symbol_codes_map[node->symbol] << endl;
        }
        // �ݹ��ӡ��������������
        if (node->left) {
            PrintCodesRecursive(node->left);
        }
        if (node->right) {
            PrintCodesRecursive(node->right);
        }
    }

    // �ݹ��ӡ��������, ǰ�������������
    void PrintTreeRecursive(HuffmanNode* node, int depth) {
        if (!node) {
            return;
        }
        // ��ӡ����
        for (int i = 0; i < depth; ++i) {
            cout << "      ";
        }
        // ��ӡ��ǰ�ڵ�
        if (node->symbol == '*') { // ��Ҷ�ӽ��
            cout << "|" << node->symbol << "(" << node->frequency << ")" << endl;
        }
        else { // Ҷ�ӽ��
            cout << "|" << node->symbol << "(" << node->frequency << ")" << ": " << symbol_codes_map[node->symbol] << endl;
        }
        // ��ӡ������
        if (node->left) {
            PrintTreeRecursive(node->left, depth + 1);
        }
        // ��ӡ������
        if (node->right) {
            PrintTreeRecursive(node->right, depth + 1);
        }
    }

    // �ݹ��ͷ���
    void FreeTreeRecursive(HuffmanNode* node) {
        if (!node) {
            return;
        }
        FreeTreeRecursive(node->left);
        FreeTreeRecursive(node->right);
        delete node; // ɾ����ǰ�ڵ�
    }

public:
    Huffman() : root(nullptr) {}

    // �����ַ��Ͷ�Ӧ��Ƶ��
    void InputFrequencies(const vector<pair<char, int>>& freq) {
        frequencies.resize(freq.size());
        for (int i = 0; i < freq.size(); ++i) {
            frequencies[i] = freq[i];
        }
    }

    // ����Huffman����
    void GenerateHuffmanCode() {
        root = BuildTree();                  // �����������
        GenerateCodesRecursive(root, "");    // ����ǰ׺��
    }

    // ����ַ�����ǰ׺��
    void PrintCodes() {
        cout << "------------------------" << endl;
        cout << "�ַ�(Ƶ��)��ǰ׺��" << endl;
        cout << "------------------------" << endl;
        for (auto& element : frequencies) {
            symbol_freq_map[element.first] = element.second; // �����ַ�Ƶ��
        }
        PrintCodesRecursive(root);
    }

    // ��ӡ��������
    void PrintTree() {
        for (auto& element : frequencies) {
            symbol_freq_map[element.first] = element.second; // �����ַ�Ƶ��
        }
        cout << "-------------------------------------------------" << endl;
        cout << "             ����������Ŀ¼�ṹ��" << endl;
        cout << "'*'�����Ҷ�ӽ�㣬����������Ƶ�ʣ�ð�ź���ǰ׺��" << endl;
        cout << "-------------------------------------------------" << endl;

        PrintTreeRecursive(root, 0);
    }

    ~Huffman() {
        FreeTreeRecursive(root); // �ͷŻ�������
    }
};

int main() {
    cout << "����ڵ������" << endl;
    int vertices;
    cin >> vertices;

    vector<pair<char, int>> frequencies(vertices);
    cout << "�������ַ���" << endl;
    for (int i = 0; i < vertices; ++i) {
        cin >> frequencies[i].first; // �����ַ�
    }
    cout << "�������ַ���Ӧ��Ƶ��" << endl;
    for (int i = 0; i < vertices; ++i) {
        cin >> frequencies[i].second; // ����Ƶ��
    }

    Huffman huffman;
    huffman.InputFrequencies(frequencies);
    huffman.GenerateHuffmanCode();
    huffman.PrintTree();
    huffman.PrintCodes();

    return 0;
}
