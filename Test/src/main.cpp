#include <iostream>

#include "CasicMath.h"

using namespace Casic::Math;

bool AreMatricesEqual(const Matrix4& mat1, const Matrix4& mat2, float epsilon = 1e-6f) {
	return mat1.Equals(mat2, epsilon);
}

void TestIdentityMatrixMultiplication() {
    Matrix4 identity = Matrix4::Identity();
    Matrix4 mat;
    mat.Data.m0 = 2.0f; mat.Data.m5 = 2.0f; mat.Data.m10 = 2.0f; mat.Data.m15 = 2.0f;

    Matrix4 result = identity * mat;

    if (AreMatricesEqual(result, mat)) {
        std::cout << "TestIdentityMatrixMultiplication passed.\n";
    }
    else {
        std::cout << "TestIdentityMatrixMultiplication failed.\n";
    }
    std::cout << "identity " << identity << std::endl;
    std::cout << "mat " << mat << std::endl;
    std::cout << "result " << result << std::endl;
}

void TestMatrixMultiplicationWithComplexMatrix() {
    Matrix4 mat1, mat2, expected;

    // 初始化 mat1
    mat1.Data.m0 = 1.0f; mat1.Data.m4 = 2.0f; mat1.Data.m8 = 3.0f; mat1.Data.m12 = 4.0f;
    mat1.Data.m1 = 5.0f; mat1.Data.m5 = 6.0f; mat1.Data.m9 = 7.0f; mat1.Data.m13 = 8.0f;
    mat1.Data.m2 = 9.0f; mat1.Data.m6 = 10.0f; mat1.Data.m10 = 11.0f; mat1.Data.m14 = 12.0f;
    mat1.Data.m3 = 13.0f; mat1.Data.m7 = 14.0f; mat1.Data.m11 = 15.0f; mat1.Data.m15 = 16.0f;

    // 初始化 mat2
    mat2.Data.m0 = 17.0f; mat2.Data.m4 = 18.0f; mat2.Data.m8 = 19.0f; mat2.Data.m12 = 20.0f;
    mat2.Data.m1 = 21.0f; mat2.Data.m5 = 22.0f; mat2.Data.m9 = 23.0f; mat2.Data.m13 = 24.0f;
    mat2.Data.m2 = 25.0f; mat2.Data.m6 = 26.0f; mat2.Data.m10 = 27.0f; mat2.Data.m14 = 28.0f;
    mat2.Data.m3 = 29.0f; mat2.Data.m7 = 30.0f; mat2.Data.m11 = 31.0f; mat2.Data.m15 = 32.0f;

    // 预期的矩阵乘法结果
    expected.Data.m0 = 250.0f; expected.Data.m4 = 260.0f; expected.Data.m8 = 270.0f; expected.Data.m12 = 280.0f;
    expected.Data.m1 = 618.0f; expected.Data.m5 = 644.0f; expected.Data.m9 = 670.0f; expected.Data.m13 = 696.0f;
    expected.Data.m2 = 986.0f; expected.Data.m6 = 1028.0f; expected.Data.m10 = 1070.0f; expected.Data.m14 = 1112.0f;
    expected.Data.m3 = 1354.0f; expected.Data.m7 = 1412.0f; expected.Data.m11 = 1470.0f; expected.Data.m15 = 1528.0f;

    Matrix4 result = mat1 * mat2;

    if (AreMatricesEqual(result, expected)) {
        std::cout << "TestMatrixMultiplicationWithComplexMatrix passed.\n";
    }
    else {
        std::cout << "TestMatrixMultiplicationWithComplexMatrix failed.\n";
    }
    std::cout << "mat1 " << mat1 << std::endl;
    std::cout << "mat2 " << mat2 << std::endl;
    std::cout << "expected " << expected << std::endl;
    std::cout << "result " << result << std::endl;
}

void TestTransposeFunction() {
    Matrix4 mat;
    mat.Data.m0 = 1.0f; mat.Data.m1 = 2.0f; mat.Data.m2 = 3.0f; mat.Data.m3 = 4.0f;
    mat.Data.m4 = 5.0f; mat.Data.m5 = 6.0f; mat.Data.m6 = 7.0f; mat.Data.m7 = 8.0f;
    mat.Data.m8 = 9.0f; mat.Data.m9 = 10.0f; mat.Data.m10 = 11.0f; mat.Data.m11 = 12.0f;
    mat.Data.m12 = 13.0f; mat.Data.m13 = 14.0f; mat.Data.m14 = 15.0f; mat.Data.m15 = 16.0f;

    Matrix4 expected;
    expected.Data.m0 = 1.0f; expected.Data.m1 = 5.0f; expected.Data.m2 = 9.0f; expected.Data.m3 = 13.0f;
    expected.Data.m4 = 2.0f; expected.Data.m5 = 6.0f; expected.Data.m6 = 10.0f; expected.Data.m7 = 14.0f;
    expected.Data.m8 = 3.0f; expected.Data.m9 = 7.0f; expected.Data.m10 = 11.0f; expected.Data.m11 = 15.0f;
    expected.Data.m12 = 4.0f; expected.Data.m13 = 8.0f; expected.Data.m14 = 12.0f; expected.Data.m15 = 16.0f;

    Matrix4 result = Matrix4::Transpose(mat);

    if (AreMatricesEqual(result, expected)) {
        std::cout << "TestTransposeFunction passed.\n";
    }
    else {
        std::cout << "TestTransposeFunction failed.\n";
    }
    std::cout << "mat " << mat << std::endl;
    std::cout << "expected " << expected << std::endl;
    std::cout << "result " << result << std::endl;
}

int main() {
    TestIdentityMatrixMultiplication();
    TestMatrixMultiplicationWithComplexMatrix();
    TestTransposeFunction();
	return 0;
}