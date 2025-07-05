#pragma once

#include <iostream>
#include <type_traits>

#include "CommonLab.h"

namespace TMPLab
{
	struct _Nontrivial_Dummy_Type {
		constexpr _Nontrivial_Dummy_Type() noexcept {}
	};

	template <typename _Ty, bool = std::is_trivially_destructible_v<_Ty>>
	struct _Optional_destruct_base {
		union {
			_Nontrivial_Dummy_Type _Dummy;
			remove_cv_t<_Ty> _Value;
		};
		bool _Has_value;

		constexpr _Optional_destruct_base() noexcept
			: _Dummy{}, _Has_value{ false } {}

		template <typename... _Types>
		constexpr _Optional_destruct_base(in_place_t, _Types&&... _Args) noexcept(std::is_nothrow_constructible_v<_Ty, _Types...>)
			: _Value(std::forward<_Types>(_Args)...), _Has_value(true) {}

		constexpr void reset() noexcept {
			_Has_value = false;
		}
	};

	template <typename _Ty>
	struct _Optional_destruct_base<_Ty, false> {
		union {
			_Nontrivial_Dummy_Type _Dummy;
			remove_cv_t<_Ty> _Value;
		};
		bool _Has_value;

		constexpr _Optional_destruct_base() noexcept
			: _Dummy{}, _Has_value{ false } {}

		template <typename... _Types>
		constexpr _Optional_destruct_base(in_place_t, _Types&&... _Args) noexcept(std::is_nothrow_constructible_v<_Ty, _Types...>)
			: _Value(std::forward<_Types>(_Args)...), _Has_value(true) {}

		constexpr ~_Optional_destruct_base() noexcept
		{
			if (_Has_value)
			{
				_Value.~_Ty();
			}
			// NOTE: 都析构了，肯定没必要设置某个标志位了。
			//_Has_value = false;
		}

		_Optional_destruct_base(_Optional_destruct_base&) = default;
		_Optional_destruct_base(const _Optional_destruct_base&) = default;
		_Optional_destruct_base& operator=(_Optional_destruct_base&) = default;
		_Optional_destruct_base& operator=(const _Optional_destruct_base&) = default;

		constexpr void reset() noexcept
		{
			if (_Has_value)
			{
				_Value.~_Ty();
				_Has_value = false;
			}
		}
	};
}

