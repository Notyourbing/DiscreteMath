/*��׿�� 2252750*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <iomanip>
#include <algorithm>
#include <climits>
// �������룬���window��linux�Ĳ���
#ifdef _WIN32
#include <conio.h>
#endif

using namespace std;

// ������
template<typename T>
class Vector {
private:
    T* data;  // ����ָ�룬�洢Ԫ��
    size_t capacity; //������ڴ�����
    size_t size; // ��ǰ�洢��Ԫ������

    // ��չ����
    void ExpandCapacity() {
        size_t new_capacity = (capacity == 0) ? 1 : capacity * 2;
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < size; ++i) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

public:
    // Ĭ�Ϲ��캯��
    Vector() : data(nullptr), capacity(0), size(0) {}

    // ����capacity�Ĺ��캯��
    Vector(size_t n) : capacity(n), size(n) {
        data = new T[capacity];
        for (size_t i = 0; i < size; ++i) {
            data[i] = T();
        }
    }

    // ����capacity�ͳ�ʼֵ�Ĺ��캯��
    Vector(size_t n, const T& value) : capacity(n), size(n) {
        data = new T[capacity];
        for (size_t i = 0; i < size; ++i) {
            data[i] = value;
        }
    }

    // �������캯���������ʼ�� Vector ��Ԫ�������� Vector ����
    Vector(const Vector& other) : capacity(other.capacity), size(other.size) {
        data = new T[capacity];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }

    // ��������
    ~Vector() {
        delete[] data;
    }

    // ����size
    size_t Size() const {
        return size;
    }

    bool Empty() {
        return (size == 0);
    }

    void PushBack(const T& value) {
        if (size == capacity) {
            ExpandCapacity();
        }
        data[size++] = value;
    }

    void PopBack() {
        if (size == 0) {
            throw out_of_range("Vector is empty");
        }
        else {
            --size;
        }
    }

    void Reverse() {
        int start = 0, end = size - 1;
        while (start < end) {
            swap(data[start], data[end]);
            ++start, --end;
        }
    }

    void Resize(size_t new_size, const T& default_value = T()) {
        if (new_size > capacity) {
            size_t new_capacity = max(new_size, capacity * 2);
            T* new_data = new T[new_capacity];
            for (size_t i = 0; i < size; ++i) {
                new_data[i] = data[i]; // ����ԭ��Ԫ��
            }
            for (size_t i = size; i < new_size; ++i) {
                new_data[i] = default_value; // ��ʼ���·���Ŀռ�
            }
            delete[] data;
            data = new_data;
            capacity = new_capacity;
        }
        else {
            for (size_t i = size; i < new_size; ++i) {
                data[i] = default_value;
            }
        }
        size = new_size;
    }

    void Clear() {
        size = 0;
    }

    // ����ָ��λ�õ�Ԫ�أ������߽��飩
    T& operator[](size_t index) {
        return data[index];
    }

    const T& operator[](size_t index) const {
        return data[index];
    }

    // ��ֵ������
    Vector& operator=(const Vector& other) {
        if (this == &other) {
            return *this;
        }
        delete[] data;  // �ͷŵ�ǰ���ݵ��ڴ�
        capacity = other.capacity;
        size = other.size;
        data = new T[capacity];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
        return *this;
    }

    class Iterator {
    private:
        T* ptr;

    public:
        Iterator(T* p) : ptr(p) {}

        //  �����ò�����
        T& operator*() {
            return *ptr;
        }

        T* operator->() {
            return ptr;
        }

        Iterator& operator++() {
            ++ptr;
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++ptr;
            return tmp;
        }

        bool operator!=(const Iterator& other) const {
            return ptr != other.ptr;
        }

        int operator-(const Iterator& other) const {
            return ptr - other.ptr;
        }



        Iterator operator+(const int x) {
            if (ptr + x > data + size) {
                throw out_of_range("Vector Iterator out of range!");
            }
            return Iterator(ptr + x);
        }

        bool operator>=(const Iterator& other) const {
            return (ptr >= other.ptr);
        }

        bool operator>(const Iterator& other) const {
            return (ptr > other.ptr);
        }

        bool operator<=(const Iterator& other) const {
            return (ptr <= other.ptr);
        }

        bool operator<(const Iterator& other) const {
            return (ptr < other.ptr);
        }
    };

    Iterator begin() {
        return Iterator(data);
    }

    Iterator end() {
        return Iterator(data + size);
    }

    const Iterator begin() const {
        return Iterator(data);
    }

    const Iterator end() const {
        return Iterator(data + size);
    }

    // ɾ��index��Ԫ��
    void erase(const size_t index) {
        if (index >= size) {
            throw out_of_range("Index out of range");
        }
        for (size_t i = index; i < size - 1; ++i) {
            data[i] = data[i + 1];
        }
        --size;
    }

    // ɾ��positionָ���Ԫ��
    Iterator erase(const Iterator position) {
        // ���������Ƿ�����Ч��Χ��
        if (position.ptr < data || position.ptr >= data + size) {
            throw out_of_range("Iterator out of range");
        }
        // ����Ҫɾ��λ�õ�ƫ����
        size_t index = position.ptr - data;
        for (size_t i = index; i < size - 1; ++i) {
            data[i] = data[i + 1];
        }
        --size;
        // ����ɾ��Ԫ�ص���һ��Ԫ�صĵ�����
        return Iterator(data + index);
    }

    // ɾ����start��end��Ԫ�أ�����start��������end
    Iterator erase(const Iterator start, const Iterator end) {
        if (start.ptr < data || end.ptr > data + size || start.ptr > end.ptr) {
            throw out_of_range("Iterator out of range");
        }
        const int erase_len = end - start;
        size_t index = start.ptr - data;
        for (size_t i = index; i < size - erase_len; ++i) {
            data[i] = data[i + erase_len];
        }
        size -= erase_len;
        return Iterator(data + index);
    }
};

// ���ȶ����ࣨ��С��ʵ�֣�
template <typename T, typename Compare>
class PriorityQueue {
private:
    T* data;
    size_t size;
    size_t capacity;
    Compare comp;

    void Resize() {
        size_t new_capacity = (capacity == 0) ? 1 : capacity * 2;
        T* new_data = new T[new_capacity];
        for (int i = 0; i < size; ++i) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

    void HeapifyUp(size_t index) {
        while (index > 0) {
            size_t parent = (index - 1) / 2;
            if (comp(data[index], data[parent])) {
                swap(data[index], data[parent]);
                index = parent;
            }
            else {
                break;
            }
        }
    }

    void HeapifyDown(size_t index) {
        while (index * 2 + 1 < size) {
            size_t left = index * 2 + 1;
            size_t right = index * 2 + 2;
            size_t smallest = left;
            if (right < size && comp(data[right], data[left])) {
                smallest = right;
            }
            if (!comp(data[index], data[smallest])) {
                swap(data[index], data[smallest]);
                index = smallest;
            }
            else {
                break;
            }
        }
    }

public:
    PriorityQueue() : data(nullptr), size(0), capacity(0) {}

    ~PriorityQueue() {
        delete[] data;
    }

    void Push(const T& value) {
        if (size == capacity) {
            Resize();
        }
        data[size] = value;
        ++size;
        HeapifyUp(size - 1);
    }

    void Pop() {
        if (Empty()) {
            throw out_of_range("PriorityQueue is empty!");
        }
        data[0] = data[size - 1];
        --size;
        HeapifyDown(0);
    }

    const T& Top() const {
        if (Empty()) {
            throw out_of_range("PriorityQueue is empty!");
        }
        return data[0];
    }

    bool Empty() const {
        return (size == 0);
    }
};

// ���鼯��
class UnionFind {
private:
    Vector<int> parent; // ÿ���ڵ�ĸ��ڵ�
    Vector<int> rank; // ÿ���ڵ���ȣ������Ż����ĸ߶�

public:
    UnionFind(int n) {
        parent.Resize(n);
        rank.Resize(n);
        // ��ʼ����ÿ���ڵ㶼�Ƕ����ļ���
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int Find(int x) {
        if (parent[x] != x) {
            parent[x] = Find(parent[x]); //·��ѹ��
        }
        return parent[x];
    }

    void Union(int x, int y) {
        int root_x = Find(x);
        int root_y = Find(y);
        if (root_x != root_y) {
            // ���Ⱥϲ�����������ƽ��
            if (rank[root_x] > rank[root_y]) {
                parent[root_y] = root_x;
            }
            else if (rank[root_x] < rank[root_y]) {
                parent[root_x] = root_y;
            }
            else {
                parent[root_y] = root_x;
                ++rank[root_x];
            }
        }
    }
};

// ��С�ѵıȽϺ���
struct PairGreater {
    bool operator()(const pair<int, int> p1, const pair<int, int> p2) {
        return p1.first < p2.first;
    }
};

// ��С��������
class MinSpanTree {
private:
    int vertices; // ͼ�Ķ�����
    int mst_cost;
    Vector<char> v_names; // ���������
    Vector<Vector<int> > graph_matrix; // ͼ���ڽӾ���
    Vector<Vector<pair<int, int>>> graph_list; // ͼ���ڽӱ�
    Vector<pair<int, int> > mst_edges; // ��С�������ı߼���

public:
    // ���캯������������
    MinSpanTree() : vertices(0), mst_cost(0) {}
    ~MinSpanTree() {}

    // �жϿ�ͼ
    bool Empty() {
        return (vertices == 0);
    }

    // ���ö�����
    void SetVertices(const int v) {
        vertices = v;
        graph_matrix.Resize(v, Vector<int>(v, 0));
        graph_list.Resize(v);
        v_names.Resize(v);
    }

    // ��ȡ������������
    Vector<char> GetVerticesName() const {
        return v_names;
    }

    // ���ö�������
    void SetVerticesName(const Vector<char>& names) {
        if (vertices != names.Size()) {
            throw out_of_range("v_names out of range");
        }
        v_names = names;
    }

    // ��ӱ�
    void AddEdge(const int v1, const int v2, const int value) {
        graph_matrix[v1][v2] = value;
        graph_matrix[v2][v1] = value;
        graph_list[v1].PushBack({ v2, value });
        graph_list[v2].PushBack({ v1, value });
    }

    // �ڽӾ����Prim�㷨
    void PrimWithMatrix() {
        mst_edges.Clear();
        mst_cost = 0;

        Vector<bool> visited(vertices, false); // ��¼�ڵ��Ƿ񱻷���
        Vector<int> min_weight(vertices, INT_MAX); // ������������С��Ȩֵ
        Vector<int> parent(vertices, -1); // ��¼��С������ÿ���ڵ�ĸ��ڵ�
        min_weight[0] = 0; // �ӵ�һ���ڵ㿪ʼ

        for (int i = 0; i < vertices; ++i) {
            int u = -1, min_edge = INT_MAX;

            // �ҵ�δ������Ȩֵ��С�Ķ���
            for (int v = 0; v < vertices; ++v) {
                if (!visited[v] && min_weight[v] < min_edge) {
                    u = v;
                    min_edge = min_weight[v];
                }
            }
            if (-1 == u) { // û�п��Լ���Ľڵ�
                break;
            }
            visited[u] = true; // ���Ϊ�Ѿ�����
            mst_cost += min_edge; // �ۼ���СȨֵ
            if (parent[u] != -1) { // u �и��ڵ�
                mst_edges.PushBack({ parent[u], u });
            }
            // �����ڽӽڵ����С��Ȩֵ
            for (int v = 0; v < vertices; ++v) {
                if (graph_matrix[u][v] != 0 && !visited[v] && graph_matrix[u][v] < min_weight[v]) {
                    min_weight[v] = graph_matrix[u][v];
                    parent[v] = u;
                }
            }
        }
    }

    // �ڽ������Prim�㷨
    void PrimWithList() {
        mst_edges.Clear();
        mst_cost = 0;

        Vector<bool> visited(vertices, false); // ��¼�ڵ��Ƿ񱻷��ʹ�
        Vector<int> min_weight(vertices, INT_MAX); // ������������С��Ȩֵ
        Vector<int> parent(vertices, -1); // ��¼��С������ÿ���ڵ�ĸ��ڵ�
        min_weight[0] = 0;

        // ���ȶ��У���С�ѣ������������Ľڵ㣬pair�ĵ�һ��Ԫ����Ȩֵ���ڶ���Ԫ���Ƕ���
        PriorityQueue<pair<int, int>, PairGreater> pq;
        pq.Push({ 0, 0 }); // ��ʼ�ڵ㣬ȨֵΪ0

        while (!pq.Empty()) {
            // ȡ��Ȩֵ��С�Ķ���
            int weight = pq.Top().first;
            int u = pq.Top().second;
            pq.Pop();

            if (visited[u]) continue;
            visited[u] = true;
            mst_cost += weight; // �ۼӵ�ǰ�ߵ�Ȩ��

            if (parent[u] != -1) {
                mst_edges.PushBack({ parent[u], u });
            }

            // ������ǰ�ڵ�u�������ڵı�
            for (auto& element : graph_list[u]) {
                int& v = element.first;
                int& w = element.second;
                // ���vδ�����ʣ��Ҹñߵ�Ȩ�ظ�С
                if (!visited[v] && w < min_weight[v]) {
                    min_weight[v] = w;
                    parent[v] = u;
                    pq.Push({ w, v }); // �����º�Ľڵ�v�������ȶ���
                }

            }
        }

    }

    // Kruskal�㷨
    void Kruskal() {
        mst_edges.Clear();
        mst_cost = 0;

        // ����һ�����鼯
        UnionFind uf(vertices);

        // �����б߰�Ȩ������ÿ���ߵĸ�ʽΪ(weight, (v1, v2))
        Vector<pair<int, pair<int, int > > > edges;

        // ����ͼ�����еıߣ��ڽӾ����ʾ��
        for (int i = 0; i < vertices; ++i) {
            for (int j = i + 1; j < vertices; ++j) {
                if (graph_matrix[i][j] != 0) {
                    edges.PushBack({ graph_matrix[i][j], {i, j} });
                }
            }
        }

        // ���ձߵ�Ȩ����������
        for (int i = 0; i < edges.Size(); ++i) {
            for (int j = 0; j < edges.Size() - 1 - i; ++j) {
                if (edges[j].first > edges[j + 1].first) {
                    swap(edges[j], edges[j + 1]);
                }
            }
        }

        // ���δ���ÿ����
        for (auto& edge : edges) {
            int weight = edge.first;
            int u = edge.second.first;
            int v = edge.second.second;

            // ���u��v�ڲ�ͬ�ļ����У��Ͱ������߼��뵽��������
            if (uf.Find(u) != uf.Find(v)) {
                uf.Union(u, v);
                mst_edges.PushBack({ u, v });
                mst_cost += weight;
            }
        }

    }

    // ��ȡ��С����
    int GetMstCost() const {
        return mst_cost;
    }

    // ��ӡ��С������
    void Disp() {
        cout << "��С�������ı�:\n";
        for (int i = 0; i < mst_edges.Size(); ++i) {
            auto temp = mst_edges[i];
            cout << v_names[mst_edges[i].first] << "---" << v_names[mst_edges[i].second] << " :" << graph_matrix[mst_edges[i].first][mst_edges[i].second] << endl;
        }
    }
};

// ��ӡ����
void PrintTitle() {
    cout << "|------------------------------------------------|" << endl;
    cout << "|                  ��С������                     |" << endl;
    cout << "|------------------------------------------------|" << endl;
    cout << "|                A---����ͼ�Ķ���                |" << endl;
    cout << "|                B---���ͼ�ı�                  |" << endl;
    cout << "|                C---ѡ����С�������㷨          |" << endl;
    cout << "|                D---��ʾ��С������              |" << endl;
    cout << "|                E---�˳�����                    |" << endl;
    cout << "|------------------------------------------------|" << endl;
    cout << endl;
}

int main() {
    PrintTitle();
    char choice;

    MinSpanTree min_span_tree;
    int vertices = 0;
    while (1) {
        cout << endl << "��ѡ�������";
        cin >> choice;
        if (choice >= 'a' && choice <= 'z') {
            choice = choice - 'a' + 'A';
        }
        if ('A' == choice) {
            cout << "�����붥�����" << endl;
            while (true) {
                cin >> vertices;
                if (cin.fail() || vertices <= 0) {
                    cin.clear();  // ��������־
                    cin.ignore(INT_MAX, '\n');  // ������뻺��
                    cout << "������Ч�����������붥�����������0����" << endl;
                }
                else {
                    break;
                }
            }
            min_span_tree.SetVertices(vertices);
            cout << "��������������������" << endl;
            Vector<char> v_names(vertices);
            for (int i = 0; i < vertices; ++i) {
                cin >> v_names[i];
            }
            min_span_tree.SetVerticesName(v_names);
            cout << "��������ɹ�" << endl;
        }
        else if ('B' == choice) {
            if (vertices == 0) {
                cout << "ͼû�ж���" << endl;
                break;
            }
            while (1) {
                cout << "�����������߶������Ƽ��ߵ�Ȩֵ(����0����)" << endl;
                char name1, name2;
                int value;
                cin >> name1;
                if (name1 == '0') {
                    cout << "�������" << endl;
                    break;
                }
                cin >> name2;
                cin >> value;
                Vector<char> v_names = min_span_tree.GetVerticesName();
                int v1 = -1, v2 = -1;
                for (int i = 0; i < v_names.Size(); ++i) {
                    char ch = v_names[i];
                    if (name1 == ch) {
                        v1 = i;
                    }
                    if (name2 == ch) {
                        v2 = i;
                    }
                }
                if (-1 == v1 || -1 == v2 || v1 == v2) {
                    cout << "�������" << endl;
                    break;
                }
                min_span_tree.AddEdge(v1, v2, value);
            }
        }
        else if ('C' == choice) {
            cout << "��ѡ����С�������㷨" << endl;
            cout << "---------------------------" << endl;
            cout << " 1---Prim�㷨���ڽӾ���ʵ�֣�" << endl;
            cout << " 2---Prim�㷨���ڽ�����ʵ�֣�" << endl;
            cout << " 3---Kruskal�㷨" << endl;
            cout << "---------------------------" << endl;

            cout << "���ѡ���ǣ�";
            int algo;
            cin >> algo;
            if (1 == algo) {
                min_span_tree.PrimWithMatrix();
            }
            else if (2 == algo) {
                min_span_tree.PrimWithList();
            }
            else if (3 == algo) {
                min_span_tree.Kruskal();
            }
            cout << endl << "��С���������ɳɹ�!" << endl;
        }
        else if ('D' == choice) {
            min_span_tree.Disp();
            cout << "�������Ϊ��" << min_span_tree.GetMstCost() << endl;
        }
        else if ('E' == choice) {
            break;
        }
    }

    return 0;
}