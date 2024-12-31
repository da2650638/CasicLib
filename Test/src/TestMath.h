#pragma once
#include <iostream>

#include "CasicMath.h"
#include "CasicMatrixTransform.h"

using namespace Casic::Math;

bool AreMatricesEqual(const Matrix4& mat1, const Matrix4& mat2, float epsilon = 1e-6f);

void TestIdentityMatrixMultiplication();

void TestMatrixMultiplicationWithComplexMatrix();

void TestTransposeFunction();

void TestRotateAroundXAxis();

void TestRotateAroundYAxis();

void TestRotateAroundZAxis();

void TestRotateAroundAxis();

void TestGenOrthoMat();