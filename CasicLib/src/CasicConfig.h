#pragma once

// �жϱ������汾
#if __cplusplus >= 202002L
	#define CASIC_USE_STDFORMAT
#endif

// ������������
#ifdef CASICLIB_EXPORTS
#define CASICLIB_API __declspec(dllexport)  // ��������
#else
#define CASICLIB_API __declspec(dllimport)  // �������
#endif