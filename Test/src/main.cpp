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

    // ��ʼ�� mat1
    mat1.Data.m0 = 1.0f; mat1.Data.m4 = 2.0f; mat1.Data.m8 = 3.0f; mat1.Data.m12 = 4.0f;
    mat1.Data.m1 = 5.0f; mat1.Data.m5 = 6.0f; mat1.Data.m9 = 7.0f; mat1.Data.m13 = 8.0f;
    mat1.Data.m2 = 9.0f; mat1.Data.m6 = 10.0f; mat1.Data.m10 = 11.0f; mat1.Data.m14 = 12.0f;
    mat1.Data.m3 = 13.0f; mat1.Data.m7 = 14.0f; mat1.Data.m11 = 15.0f; mat1.Data.m15 = 16.0f;

    // ��ʼ�� mat2
    mat2.Data.m0 = 17.0f; mat2.Data.m4 = 18.0f; mat2.Data.m8 = 19.0f; mat2.Data.m12 = 20.0f;
    mat2.Data.m1 = 21.0f; mat2.Data.m5 = 22.0f; mat2.Data.m9 = 23.0f; mat2.Data.m13 = 24.0f;
    mat2.Data.m2 = 25.0f; mat2.Data.m6 = 26.0f; mat2.Data.m10 = 27.0f; mat2.Data.m14 = 28.0f;
    mat2.Data.m3 = 29.0f; mat2.Data.m7 = 30.0f; mat2.Data.m11 = 31.0f; mat2.Data.m15 = 32.0f;

    // Ԥ�ڵľ���˷����
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

void TestRotateAroundXAxis() {
    Vector3 v(0.0f, 1.0f, 0.0f);
    v.RotateAroundXAxis(90.0f); // ��ת 90 ��
    Vector3 expected(0.0f, 0.0f, 1.0f); // Ԥ�ڽ������Z��

    if (v.Equals(expected)) {
        std::cout << "TestRotateAroundXAxis passed.\n";
    }
    else {
        std::cout << "TestRotateAroundXAxis failed.\n";
    }
    std::cout << "v: " << v << std::endl;
}

void TestRotateAroundYAxis() {
    Vector3 v(1.0f, 0.0f, 0.0f);
    v.RotateAroundYAxis(90.0f); // ��ת 90 ��
    Vector3 expected(0.0f, 0.0f, -1.0f); // Ԥ�ڽ������Z�Ḻ����

    if (v.Equals(expected)) {
        std::cout << "TestRotateAroundYAxis passed.\n";
    }
    else {
        std::cout << "TestRotateAroundYAxis failed.\n";
    }
    std::cout << "v: " << v << std::endl;
}

void TestRotateAroundZAxis() {
    Vector3 v(1.0f, 0.0f, 0.0f);
    v.RotateAroundZAxis(90.0f); // ��ת 90 ��
    Vector3 expected(0.0f, 1.0f, 0.0f); // Ԥ�ڽ������Y��

    if (v.Equals(expected)) {
        std::cout << "TestRotateAroundZAxis passed.\n";
    }
    else {
        std::cout << "TestRotateAroundZAxis failed.\n";
    }
    std::cout << "v: " << v << std::endl;
}

void TestRotateAroundAxis() {
    // ���� 1: �� Y ����ת 90 ��
    Vector3 v1(1.0f, 0.0f, 0.0f);
    Vector3 axis1(0.0f, 1.0f, 0.0f); // �� Y ����ת
    v1.RotateAroundAxis(90.0f, axis1); // ��ת 90 ��
    Vector3 expected1(0.0f, 0.0f, -1.0f); // Ԥ�ڽ������ Z �Ḻ����
    if (v1.Equals(expected1)) {
        std::cout << "TestRotateAroundAxis (Y 90) passed.\n";
    }
    else {
        std::cout << "TestRotateAroundAxis (Y 90) failed.\n";
    }
    std::cout << "v1: " << v1 << std::endl;

    // ���� 2: �� X ����ת 90 ��
    Vector3 v2(0.0f, 1.0f, 0.0f);
    Vector3 axis2(1.0f, 0.0f, 0.0f); // �� X ����ת
    v2.RotateAroundAxis(90.0f, axis2); // ��ת 90 ��
    Vector3 expected2(0.0f, 0.0f, 1.0f); // Ԥ�ڽ������ Z ��������
    if (v2.Equals(expected2)) {
        std::cout << "TestRotateAroundAxis (X 90) passed.\n";
    }
    else {
        std::cout << "TestRotateAroundAxis (X 90) failed.\n";
    }
    std::cout << "v2: " << v2 << std::endl;

    // ���� 3: �� Z ����ת 180 ��
    Vector3 v3(1.0f, 0.0f, 0.0f);
    Vector3 axis3(0.0f, 0.0f, 1.0f); // �� Z ����ת
    v3.RotateAroundAxis(180.0f, axis3); // ��ת 180 ��
    Vector3 expected3(-1.0f, 0.0f, 0.0f); // Ԥ�ڽ���� X �᷽����
    if (v3.Equals(expected3)) {
        std::cout << "TestRotateAroundAxis (Z 180) passed.\n";
    }
    else {
        std::cout << "TestRotateAroundAxis (Z 180) failed.\n";
    }
    std::cout << "v3: " << v3 << std::endl;

    // ���� 4: �������� (1, 1, 1) ��ת 45 ��
    Vector3 v4(1.0f, 0.0f, 0.0f);
    Vector3 axis4(1.0f, 1.0f, 1.0f); // �� (1, 1, 1) ��ת
    v4.RotateAroundAxis(45.0f, axis4); // ��ת 45 ��
    Vector3 expected4(0.5f, 0.5f, -0.7071f); // Ԥ�ڽ��������ֵ��ȡ���ڸ������ȣ�
    if (v4.Equals(expected4)) {
        std::cout << "TestRotateAroundAxis (45 degrees) passed.\n";
    }
    else {
        std::cout << "TestRotateAroundAxis (45 degrees) failed.\n";
    }
    std::cout << "v4: " << v4 << std::endl;

    // ���� 5: �������� (0, 1, 0) ��ת 180 ��
    Vector3 v5(1.0f, 0.0f, 0.0f);
    Vector3 axis5(0.0f, 1.0f, 0.0f); // �� Y ����ת
    v5.RotateAroundAxis(180.0f, axis5); // ��ת 180 ��
    Vector3 expected5(-1.0f, 0.0f, 0.0f); // Ԥ�ڽ���� X �᷽����
    if (v5.Equals(expected5)) {
        std::cout << "TestRotateAroundAxis (Y 180) passed.\n";
    }
    else {
        std::cout << "TestRotateAroundAxis (Y 180) failed.\n";
    }
    std::cout << "v5: " << v5 << std::endl;
}

int main() {
    TestIdentityMatrixMultiplication();
    TestMatrixMultiplicationWithComplexMatrix();
    TestTransposeFunction();

    // ���� Vector3 ��ת����
    TestRotateAroundXAxis();
    TestRotateAroundYAxis();
    TestRotateAroundZAxis();
    TestRotateAroundAxis();
	return 0;
}