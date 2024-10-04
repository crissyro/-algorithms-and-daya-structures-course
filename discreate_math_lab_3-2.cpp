#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include <utility>

bool A_relation(int x, int y) {
    return y > x + 5 || x > y + 5;
}

bool B_relation(int x, int y) {
    return x % 2 == 0 && y % 2 == 0;
}

bool C_relation(int x, int y) {
    return std::abs(x - y) > 5;
}

template <typename T>
class BinMatrix {
private:
    unsigned short size;
    std::vector<std::vector<T>> matrix;

public:
    explicit BinMatrix(unsigned short size) {
        if (size <= 0) throw std::invalid_argument("Недопустимый размер матрицы");
        
        this->size = size;
        matrix.resize(size);

        for (auto& row : matrix) row.resize(size);
    }

    ~BinMatrix() {};

    short getSize(BinMatrix& M) {
        return M.size;
    }

    void setElement(unsigned short row, unsigned short col, T value) {
        if (row >= size || col >= size) throw std::out_of_range("Выход за пределы матрицы");
        
        matrix[row][col] = value;
    }

    T getElement(unsigned short row, unsigned short col) {
        if (row >= this->size || col >= this->size) throw std::out_of_range("Выход за пределы матрицы");
        
        return matrix[row][col];
    }

    template <typename RelationFunction>
    static void MakeRelationMatrix(RelationFunction relation, BinMatrix& result) {
        for (size_t i = 0; i < result.size; ++i) {
            for (size_t j = 0; j < result.size; ++j) {

                if (relation(i, j)) result.matrix[i][j] = 1;

                else result.matrix[i][j] = 0;

            }
        }
    }

    bool isReflection(const BinMatrix& m) {
        for (int i = 0; i < m.size; i++) {
            if (!m.matrix[i][i]) {
                std::cout << "Отношение не является рефлексивным Отсутствует пара (" << ++i << ", " << ++i << ")\n";
                return false;
            }
        }

        std::cout << "Отношение является рефлексивным" << std::endl;

        return true;
    }

    bool isAntiReflection(const BinMatrix& m) {
        for (int i = 0; i < m.size; i++) {
            if (m.matrix[i][i]) {
                std::cout << "Отношение не является антирефлексивным. Присутсвует пара (" << ++i << ", " << ++i << ")\n";
                return false;
            }
        }

        std::cout << "Отношение является антирефлексивным\n";

        return true;
    }

    bool isSymmetric(const BinMatrix& m) {
        for (int i = 0; i < m.size; i++) {
            for (int j = 0; j < m.size; j++) {
                if (m.matrix[i][j] != m.matrix[j][i]) {
                    std::cout << "Отношение не является симметричным. Есть такая пара (" << ++i << ", " << ++j << "), что принадлежит отношению, a (" << ++j << ", " << ++i << ") нет\n";
                    return false;
                }
            }
        }
        std::cout << "Отношение является симметричным\n";
        return true;
    }

    bool isAntiSymmetric(const BinMatrix& m) {
        for (int i = 0; i < m.size; i++) {
            for (int j = 0; j < m.size; j++) {
                if (m.matrix[i][j] == m.matrix[j][i] && (m.matrix[i][j] && m.matrix[j][i])) {
                    std::cout << "Отношение не является антисимметричным. Есть такая пара (" << ++i << ", " << ++j << "), что принадлежит отношению и (" << ++j << ", " << ++i << ") тоже принадлежит \n";
                    return false;
                }
            }
        }
        std::cout << "Отношение является антисимметричным\n";

        return true;
    }

    bool isTransitive(const BinMatrix& m) {
        for (int i = 0; i < m.size; i++) {
            for (int j = 0; j < m.size; j++) {
                if (m.matrix[i][j]) {
                    for (int k = 0; k < m.size; k++) {
                        if (m.matrix[j][k] && !m.matrix[i][k]) {
                            std::cout << "Отношение не является транзитивным, т.к (" << ++i << ", " << ++j << ") принадлежат R и (" \
                                << ++j << ", " << ++k << ") принадлежат R, а (" << ++i << ", " << ++k << ") не принадлежат R, что противоречит усл транзитивности" \
                                << std::endl;

                            return false;
                        }
                    }
                }
            }
        }

        std::cout << "Отношения являются транзитивными" << std::endl;

        return true;
    }

    bool isAntiTransitive(const BinMatrix& m) {
        for (int i = 0; i < m.size; i++) {
            for (int j = 0; j < m.size; j++) {
                if (m.matrix[i][j]) {
                    for (int k = 0; k < m.size; k++) {
                        if (m.matrix[i][k] && m.matrix[j][k]) {
                            std::cout << "Отношение не является антитранзитивным, т.к (" << ++i << ", " << ++j << ") принадлежат R и (" \
                                << ++j << ", " << ++k << ") принадлежат R и (" << ++i << ", " << ++k << ") тоже принадлежат R, что противоречит усл антитранзитивности" \
                                << std::endl;
                            return false;
                        }
                    }
                }
            }
        }
        std::cout << "Отношение является антитранзитивным\n";

        return true;
    }

    bool isFull(const BinMatrix& m) {
        for (int i = 0; i < m.size; i++) {
            for (int j = 0; j < m.size; j++) {
                if (!(m.matrix[i][j] || m.matrix[j][i])) {
                    std::cout << "Отношение не является полным. Отсутствует пара (" << ++i << ", " << ++j << ")\n";
                    return false;
                }
            }
        }
        std::cout << "Отношение является полным\n";

        return true;
    }

    void printMatrix() {
        for (const auto& row : matrix) {
            for (int val : row) {
                std::cout << val << " ";
            }
            std::cout << std::endl;
        }
    }

    bool IsSubset(const BinMatrix& S, const BinMatrix& C) {
        for (int i = 0; i < S.size; i++) {
            for (int j = 0; j < S.size; j++) {
                if (S.matrix[i][j] & ~C.matrix[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    bool IsEqual(const BinMatrix& m1, const BinMatrix& m2) {
        for (int i = 0; i < m1.size; i++) {
            for (int j = 0; j < m1.size; j++) {
                if (m1.matrix[i][j] != m2.matrix[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    bool IsProperSubset(const BinMatrix& m1, const BinMatrix& m2) {
        return !IsEqual(m1, m2) && IsSubset(m1, m2);
    }

    BinMatrix UnionMatrix(const BinMatrix& m1, const BinMatrix& m2) {
        BinMatrix res(size);
        for (int i = 0; i < res.size; i++) {
            for (int j = 0; j < res.size; j++) {
                res.matrix[i][j] = (m1.matrix[i][j] || m2.matrix[i][j]) ? 1 : 0;
            }
        }
        return res;
    }

    BinMatrix IntersectionMatrix(const BinMatrix& A, const BinMatrix& B) {
        if (A.size != B.size) throw std::invalid_argument("Размеры матриц не совпадают");

        BinMatrix result(A.size);
        for (int i = 0; i < A.size; i++) {
            for (int j = 0; j < A.size; j++) {
                result.matrix[i][j] = A.matrix[i][j] && B.matrix[i][j]; // Логическое И для пересечения
            }
        }
        return result;
    }

    BinMatrix DiffMatrix(const BinMatrix& m1, const BinMatrix& m2) {
        BinMatrix res(size);
        for (int i = 0; i < res.size; i++) {
            for (int j = 0; j < res.size; j++) {
                res.matrix[i][j] = (m2.matrix[i][j] ? 0 : m1.matrix[i][j]);
            }
        }
        return res;
    }

    BinMatrix SymDiffMatrix(const BinMatrix& m1, const BinMatrix& m2) {
        BinMatrix res(size);
        for (int i = 0; i < res.size; i++) {
            for (int j = 0; j < res.size; j++) {
                res.matrix[i][j] = (m1.matrix[i][j] + m2.matrix[i][j] == 1) ? 1 : 0;
            }
        }
        return res;
    }

    BinMatrix ComplMatrix(const BinMatrix& m) {
        BinMatrix res(size);
        for (int i = 0; i < res.size; i++) {
            for (int j = 0; j < res.size; j++) {
                res.matrix[i][j] = ~m.matrix[i][j];
            }
        }
        return res;
    }

    BinMatrix InverseMatrix(const BinMatrix& m) {
        BinMatrix res(size);
        for (int i = 0; i < res.size; i++) {
            for (int j = 0; j < res.size; j++) {
                res.matrix[i][j] = m.matrix[j][i];
            }
        }
        return res;
    }

    BinMatrix CompositeMatrix(const BinMatrix& A, const BinMatrix& B) {
        if (A.size != B.size) throw std::invalid_argument("Размеры матриц не совпадают");

        BinMatrix result(A.size);
        for (int i = 0; i < A.size; i++) {
            for (int j = 0; j < A.size; j++) {
                result.matrix[i][j] = 0;
                for (int k = 0; k < A.size; k++) {
                    if (A.matrix[i][k] && B.matrix[k][j]) {   // A.matrix[i][k] == B.matrix[k][j]
                        result.matrix[i][j] = 1;   // (A.matrix[i][j] | A.matrix[i][k]) & B.matrix[k][j]
                        break; 
                    }
                }
            }
        }
        return result;
    }

    void copy(BinMatrix& M1, BinMatrix& M2) {
        for (int i = 0; i < M1.size; i++) {
            for (int j = 0; j < M1.size; j++) {
                M2.matrix[i][j] = M1.matrix[i][j];
            }
        }
    }

    BinMatrix algorithm1(BinMatrix& A) {
        BinMatrix C(A.size);
        copy(A, C);

        BinMatrix S(A.size);
        S = CompositeMatrix(A, A); 

        while (!IsSubset(S, C)) {
            C = UnionMatrix(C, S);
            S = CompositeMatrix(S, C);
        }

        return C;
    }

    BinMatrix algorithm2(BinMatrix& A) {
        BinMatrix C(A.size);
        A.copy(A, C); 

        BinMatrix C2 = CompositeMatrix(C, C);  

        while (!IsSubset(C2, C)) {
            C = UnionMatrix(C, C2);     
            C2 = CompositeMatrix(C2, C2);     
        }

        return C;
    }

    BinMatrix algorithm1Counter(BinMatrix& A, int& compositionCount, int& comparisonCount) {
        BinMatrix C(A.size);
        copy(A, C);

        BinMatrix S(A.size);
        S = CompositeMatrix(A, A);
        compositionCount++;
        while (!IsSubset(S, C)) {
            comparisonCount += A.size * A.size; // Количество сравнений при проверке подмножества
            C = UnionMatrix(C, S);
            S = CompositeMatrix(S, C);
            compositionCount++;
        }

        return C;
    }

    static BinMatrix algorithm2Counter(BinMatrix& A, int& compositionCount, int& comparisonCount) {
        BinMatrix C(A.size);
        A.copy(A, C);

        BinMatrix C2 = CompositeMatrix(C, C);
        compositionCount++;

        while (!IsSubset(C2, C)) {
            comparisonCount += A.size * A.size; // Количество сравнений при проверке подмножества
            C = UnionMatrix(C, C2);
            C2 = CompositeMatrix(C2, C2);
            compositionCount++;
        }

        return C;
    }

   /* BinMatrix algorithm3(BinMatrix& A) {
        return void;
    }*/

        
};

bool IsRelationA(int x, int y) {
    return (x % 2 == 0) && (x + y < 10);
}

bool IsRelationB(int x, int y) {
    return x + 2 * y < 20;
}

bool IsRelationC(int x, int y) {
    return x > 7 || y % 3 == 0;
}

bool IsRelationT(int x, int y) {
    return x == 9 && y == 9;
}

bool equal(int x, int y) {
    return x == y;
}

void task2() {
    try {
        BinMatrix<bool> mat(10);
        BinMatrix<bool>::MakeRelationMatrix(equal, mat);

        int compositionCount = 0; // Счетчик операций композиции
        int comparisonCount = 0;  // Счетчик операций сравнени

        std::cout << std::endl;

        BinMatrix<bool> res(10);

        res = mat.algorithm1Counter(mat, compositionCount, comparisonCount);

        std::cout << "Результирующая матрица:" << std::endl;
        res.printMatrix();

        std::cout << "Кол-во композиций: " << compositionCount << std::endl;
        std::cout << "Кол-во сравнений: " << comparisonCount << std::endl;


    }
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}

void task3() {
    try {
        BinMatrix<bool> mat(10);
        BinMatrix<bool>::MakeRelationMatrix([](int x, int y) { return x | y; }, mat);

        int compositionCount = 0; // Счетчик операций композиции
        int comparisonCount = 0;  // Счетчик операций сравнени

        std::cout << std::endl;

        BinMatrix<bool> res(10);

        res = mat.algorithm1Counter(mat, compositionCount, comparisonCount);

        std::cout << "Результирующая матрица:" << std::endl;
        res.printMatrix();

        std::cout << "Кол-во композиций: " << compositionCount << std::endl;
        std::cout << "Кол-во сравнений: " << comparisonCount << std::endl;


    }
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    task2();
    task3();

    return 0;
}