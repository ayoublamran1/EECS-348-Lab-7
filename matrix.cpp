#include <iostream>
#include <fstream>   // for file operations
#include <iomanip>   // for formatting output

using namespace std;

const int SIZE = 4; // Global variable for matrix size

class Matrix {
private:
    int data[SIZE][SIZE];  // 2D array for matrix data (using int for simplicity)

public:
    // 1. Read values from a file into a matrix
    void readFromFile(const string &filename) {
        ifstream file(filename);
        if (!file) {
            cerr << "Error opening file!" << endl;
            return;
        }

        for (int i = 0; i < SIZE; ++i)
            for (int j = 0; j < SIZE; ++j)
                file >> data[i][j];

        file.close();
    }

    // 2. Display a matrix
    void display() const {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                cout << setw(4) << data[i][j];
            }
            cout << endl;
        }
    }

    // 3. Add two matrices (operator overloading for +)
    Matrix operator+(const Matrix &other) const {
        Matrix result;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    // 4. Multiply two matrices (operator overloading for *)
    Matrix operator*(const Matrix &other) const {
        Matrix result;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                result.data[i][j] = 0;
                for (int k = 0; k < SIZE; ++k) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    // 5. Compute the sum of matrix diagonal elements
    int sumOfDiagonals() const {
        int mainDiagonalSum = 0, secondaryDiagonalSum = 0;
        for (int i = 0; i < SIZE; ++i) {
            mainDiagonalSum += data[i][i];
            secondaryDiagonalSum += data[i][SIZE - 1 - i];
        }
        return mainDiagonalSum + secondaryDiagonalSum;
    }

    // 6. Swap matrix rows
    void swapRows(int row1, int row2) {
        if (row1 < 0 || row1 >= SIZE || row2 < 0 || row2 >= SIZE) {
            cerr << "Invalid row indices!" << endl;
            return;
        }
        for (int j = 0; j < SIZE; ++j) {
            swap(data[row1][j], data[row2][j]);
        }
    }
};

int main() {
    Matrix mat1;
    cout << "Reading Matrix 1 from file 'matrix1.txt':" << endl;
    mat1.readFromFile("matrix1.txt");
    cout << "Matrix 1:" << endl;
    mat1.display();

    Matrix mat2;
    cout << "Reading Matrix 2 from file 'matrix2.txt':" << endl;
    mat2.readFromFile("matrix2.txt");
    cout << "Matrix 2:" << endl;
    mat2.display();

    Matrix sum = mat1 + mat2;
    cout << "Sum of matrices:" << endl;
    sum.display();

    Matrix product = mat1 * mat2;
    cout << "Product of matrices:" << endl;
    product.display();

    cout << "Sum of diagonals of Matrix 1: " << mat1.sumOfDiagonals() << endl;

    mat1.swapRows(0, 2);
    cout << "Matrix 1 after swapping rows:" << endl;
    mat1.display();

    return 0;
}
