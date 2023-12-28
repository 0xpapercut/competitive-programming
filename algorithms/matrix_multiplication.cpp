#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class Matrix {
private:
    vector<vector<T>> elem;
public:
    Matrix(int n) {
        elem = vector<vector<T>>(n, vector<T>(n));
    }

    Matrix(initializer_list<initializer_list<T>> list) {
        for (const auto &sub_list: list) {
            elem.push_back(vector<T>(sub_list));
        }
    }

    Matrix(const vector<vector<T>>& elements) : elem(elements) { }

    Matrix operator+(Matrix other) {
        Matrix<T> result(elem);
        for (int i = 0; i < elem.size(); i++) {
            for (int j = 0; j < elem[0].size(); j++) {
                result.elem[i][j] += other.elem[i][j];
            }
        }
        return result;
    }

    Matrix operator-(Matrix other) {
        Matrix<T> result(elem);
        for (int i = 0; i < elem.size(); i++) {
            for (int j = 0; j < elem[0].size(); j++) {
                result.elem[i][j] -= other.elem[i][j];
            }
        }
        return result;
    }

    int size() {
        return elem.size();
    }

    vector<T>& operator[](int index) {
        return elem[index];
    }
};

template<typename T>
tuple<Matrix<T>, Matrix<T>, Matrix<T>, Matrix<T>> split_matrix(Matrix<T> A) {
    int n = A.size() / 2;

    Matrix<T> A11(n);
    Matrix<T> A12(n);
    Matrix<T> A21(n);
    Matrix<T> A22(n);

    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < A[0].size(); j++) {
            if (i < n && j < n)
                A11[i][j] = A[i][j];
            else if (i < n && j >= n)
                A12[i][j - n] = A[i][j];
            else if (i >= n && j < n)
                A21[i - n][j] = A[i][j];
            else
                A22[i - n][j - n] = A[i][j];
        }
    }

    return make_tuple(A11, A12, A21, A22);
}

template<typename T>
Matrix<T> join_matrix(Matrix<T> A11, Matrix<T> A12, Matrix<T> A21, Matrix<T> A22) {
    int n = A11.size();
    Matrix<T> A(2 * n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = A11[i][j];
            A[i][j + n] = A12[i][j];
            A[i + n][j] = A21[i][j];
            A[i + n][j + n] = A22[i][j];
        }
    }

    return A;
}

template<typename T>
Matrix<T> matmul(Matrix<T> A, Matrix<T> B) {
    if (A[0].size() == 1) {
        return Matrix<T> {{A[0][0] * B[0][0]}};
    }

    auto [A11, A12, A21, A22] = split_matrix(A);
    auto [B11, B12, B21, B22] = split_matrix(B);

    auto S1 = B12 - B22;
    auto S2 = A11 + A12;
    auto S3 = A21 + A22;
    auto S4 = B21 - B11;
    auto S5 = A11 + A22;
    auto S6 = B11 + B22;
    auto S7 = A12 - A22;
    auto S8 = B21 + B22;
    auto S9 = A11 - A21;
    auto S10 = B11 + B12;

    auto P1 = matmul(S1, A11);
    auto P2 = matmul(S2, B22);
    auto P3 = matmul(S3, B11);
    auto P4 = matmul(S4, A22);
    auto P5 = matmul(S5, S6);
    auto P6 = matmul(S7, S8);
    auto P7 = matmul(S9, S10);

    auto C11 = P5 + P4 - P2 + P6;
    auto C12 = P1 + P2;
    auto C21 = P3 + P4;
    auto C22 = P5 + P1 - P3 - P7;

    return join_matrix(C11, C12, C21, C22);
}

template<typename T>
void print_matrix(Matrix<T> matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

// Implementation right now is kinda buggy, uses too much memory, and doesn't give the right results.
int main() {
    Matrix<int> A = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    Matrix<int> B = {{16, 15, 14, 13}, {12, 11, 10, 9}, {8, 7, 6, 5}, {4, 3, 2, 1}};
    print_matrix(matmul(A, B));

    return 0;
}
