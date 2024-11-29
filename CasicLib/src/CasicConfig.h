#pragma once

// 判断编译器版本
#if __cplusplus >= 202002L
	#define CASIC_USE_STDFORMAT
#endif

// 方法导出设置
#ifdef CASICLIB_EXPORTS
#define CASICLIB_API __declspec(dllexport)  // 导出符号
#else
#define CASICLIB_API __declspec(dllimport)  // 导入符号
#endif