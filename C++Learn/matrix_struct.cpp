#include <iostream>
#include <vector>

// 定义矩阵结构体
struct Matrix {
    int m; // 矩阵行数
    int n; // 矩阵列数
    std::vector<std::vector<int>> data; // 矩阵数据

    // 构造函数
    Matrix(int m, int n) : m(m), n(n), data(m, std::vector<int>(n, 0)) {}

    // 输入矩阵数据
    void input() {
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                std::cin >> data[i][j];
            }
        }
    }

    // 打印矩阵
    void print() const {
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                std::cout << data[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    // 矩阵加法
    Matrix operator+(const Matrix& other) {
        if (m != other.m || n != other.n) {
            throw std::invalid_argument("Matrices dimensions must agree.");
        }
        Matrix result(m, n);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    // 矩阵乘法
    Matrix operator*(const Matrix& other) {
        if (n != other.m) {
            throw std::invalid_argument("Matrix A's columns must equal Matrix B's rows.");
        }
        Matrix result(m, other.n);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < other.n; ++j) {
                for (int k = 0; k < n; ++k) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }
};

int main() {
    int m, n;
    std::cout << "Enter the number of rows and columns for the matrix (m n): ";
    std::cin >> m >> n;

    Matrix mat1(m, n), mat2(m, n);

    std::cout << "Enter the elements for the first matrix:\n";
    mat1.input();
    std::cout << "Enter the elements for the second matrix:\n";
    mat2.input();

    std::cout << "First Matrix:\n";
    mat1.print();
    std::cout << "Second Matrix:\n";
    mat2.print();

    try {
        Matrix sum = mat1 + mat2;
        std::cout << "Sum of Matrices:\n";
        sum.print();

        Matrix product = mat1 * mat2;
        std::cout << "Product of Matrices:\n";
        product.print();
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}