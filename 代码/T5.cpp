#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include <iomanip>

using namespace std;

// 定义霍夫曼树节点结构体
struct HuffmanNode {
    char symbol;              // 符号
    int frequency;            // 频率
    HuffmanNode* left, * right; // 左右子树指针

    // 节点构造函数
    HuffmanNode(char sym, int freq) : symbol(sym), frequency(freq), left(nullptr), right(nullptr) {}
};

// 比较器，用于优先队列
struct Compare {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->frequency > b->frequency; // 优先队列中频率小的节点优先
    }
};

// 霍夫曼编码类
class Huffman {
private:
    HuffmanNode* root;                      // Huffman树根节点
    unordered_map<char, string> symbol_codes_map;      // 存储字符和对应的前缀码
    unordered_map<char, int> symbol_freq_map;          // 存储字符和对应的频率
    vector<pair<char, int>> frequencies;    // 输入的字符和对应的频率

    // 构造霍夫曼树并返回根节点
    HuffmanNode* BuildTree() {
        // 创建最小堆（优先队列）
        priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> min_heap;

        // 将所有频率和字符放入最小堆中
        for (const auto& entry : frequencies) {
            min_heap.push(new HuffmanNode(entry.first, entry.second));
        }

        // 构建霍夫曼树
        while (min_heap.size() > 1) {
            // 从堆中取出最小的两个节点
            HuffmanNode* left = min_heap.top();
            min_heap.pop();
            HuffmanNode* right = min_heap.top();
            min_heap.pop();

            // 合并两个节点，频率相加，符号为'*'表示非叶子节点
            HuffmanNode* merged = new HuffmanNode('*', left->frequency + right->frequency);
            merged->left = left;
            merged->right = right;

            min_heap.push(merged);
        }

        return min_heap.top(); // 返回根节点
    }

    // 递归生成前缀码
    void GenerateCodesRecursive(HuffmanNode* node, string code) {
        if (!node)
            return;

        // 如果是叶子结点
        if (!node->left && !node->right) {
            symbol_codes_map[node->symbol] = code; // 保存字符的前缀码
        }

        // 递归生成左子树和右子树的前缀码
        GenerateCodesRecursive(node->left, code + "0"); // 左分支加0
        GenerateCodesRecursive(node->right, code + "1"); // 右分支加1
    }

    // 递归打印前缀码
    void PrintCodesRecursive(HuffmanNode* node) {
        if (!node) {
            return;
        }
        // 如果是叶子结点，打印字符及其频率和前缀码
        if (!node->left && !node->right) {
            string temp = string(1, node->symbol) +
                "(" + std::to_string(symbol_freq_map[node->symbol]) + ")" + ":";
            cout << setiosflags(ios::left) << setw(10) << temp << symbol_codes_map[node->symbol] << endl;
        }
        // 递归打印左子树和右子树
        if (node->left) {
            PrintCodesRecursive(node->left);
        }
        if (node->right) {
            PrintCodesRecursive(node->right);
        }
    }

    // 递归打印霍夫曼树, 前序遍历，根左右
    void PrintTreeRecursive(HuffmanNode* node, int depth) {
        if (!node) {
            return;
        }
        // 打印缩进
        for (int i = 0; i < depth; ++i) {
            cout << "      ";
        }
        // 打印当前节点
        if (node->symbol == '*') { // 非叶子结点
            cout << "|" << node->symbol << "(" << node->frequency << ")" << endl;
        }
        else { // 叶子结点
            cout << "|" << node->symbol << "(" << node->frequency << ")" << ": " << symbol_codes_map[node->symbol] << endl;
        }
        // 打印左子树
        if (node->left) {
            PrintTreeRecursive(node->left, depth + 1);
        }
        // 打印右子树
        if (node->right) {
            PrintTreeRecursive(node->right, depth + 1);
        }
    }

    // 递归释放树
    void FreeTreeRecursive(HuffmanNode* node) {
        if (!node) {
            return;
        }
        FreeTreeRecursive(node->left);
        FreeTreeRecursive(node->right);
        delete node; // 删除当前节点
    }

public:
    Huffman() : root(nullptr) {}

    // 输入字符和对应的频率
    void InputFrequencies(const vector<pair<char, int>>& freq) {
        frequencies.resize(freq.size());
        for (int i = 0; i < freq.size(); ++i) {
            frequencies[i] = freq[i];
        }
    }

    // 生成Huffman编码
    void GenerateHuffmanCode() {
        root = BuildTree();                  // 构造霍夫曼树
        GenerateCodesRecursive(root, "");    // 生成前缀码
    }

    // 输出字符及其前缀码
    void PrintCodes() {
        cout << "------------------------" << endl;
        cout << "字符(频率)：前缀码" << endl;
        cout << "------------------------" << endl;
        for (auto& element : frequencies) {
            symbol_freq_map[element.first] = element.second; // 保存字符频率
        }
        PrintCodesRecursive(root);
    }

    // 打印霍夫曼树
    void PrintTree() {
        for (auto& element : frequencies) {
            symbol_freq_map[element.first] = element.second; // 保存字符频率
        }
        cout << "-------------------------------------------------" << endl;
        cout << "             霍夫曼树的目录结构：" << endl;
        cout << "'*'代表非叶子结点，括号里面是频率，冒号后是前缀码" << endl;
        cout << "-------------------------------------------------" << endl;

        PrintTreeRecursive(root, 0);
    }

    ~Huffman() {
        FreeTreeRecursive(root); // 释放霍夫曼树
    }
};

int main() {
    cout << "输入节点个数：" << endl;
    int vertices;
    cin >> vertices;

    vector<pair<char, int>> frequencies(vertices);
    cout << "请输入字符：" << endl;
    for (int i = 0; i < vertices; ++i) {
        cin >> frequencies[i].first; // 输入字符
    }
    cout << "请输入字符对应的频率" << endl;
    for (int i = 0; i < vertices; ++i) {
        cin >> frequencies[i].second; // 输入频率
    }

    Huffman huffman;
    huffman.InputFrequencies(frequencies);
    huffman.GenerateHuffmanCode();
    huffman.PrintTree();
    huffman.PrintCodes();

    return 0;
}
