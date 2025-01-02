#pragma once

namespace TMPLab 
{
	template <typename _Ty>
	struct remove_cv {
		using type = _Ty;

		template <template <class> class _Fn>
		using _Apply = _Fn<_Ty>;
	};

	template <typename _Ty>
	struct remove_cv<const _Ty> {
		using type = _Ty;

		template <template <class> class _Fn>
		using _Apply = const _Fn<_Ty>;
	};

	template <typename _Ty>
	struct remove_cv<volatile _Ty> {
		using type = _Ty;

		template <template <class> class _Fn>
		using _Apply = volatile _Fn<_Ty>;
	};

	template <typename _Ty>
	struct remove_cv<const volatile _Ty> {
		using type = _Ty;

		template <template <class> class _Fn>
		using _Apply = const volatile _Fn<_Ty>;
	};

	template <typename _Ty>
	using remove_cv_t = typename remove_cv<_Ty>::type;

	struct in_place_t {
		explicit in_place_t() = default;
	};
	inline constexpr in_place_t in_place;
}


