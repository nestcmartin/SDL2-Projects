#ifndef __MPL_H__
#define __MPL_H__

#include <type_traits>
#include <initializer_list>

namespace MPL
{
	// Compile-time list of types.
	template<typename ... Ts>
	struct TypeList {
		// Size of the list.
		static constexpr std::size_t size{ sizeof...(Ts) };
	};

	template<typename, typename >
	struct IndexOf;

	// IndexOf base case: found the type we're looking for.
	template<typename T, typename ... Ts>
	struct IndexOf<T, TypeList<T, Ts...>> : std::integral_constant<std::size_t, 0> {
	};

	// IndexOf recursive case: 1 + IndexOf the rest of the types.
	template<typename T, typename TOther, typename ... Ts>
	struct IndexOf<T, TypeList<TOther, Ts...>> : std::integral_constant < std::size_t,
		1 + IndexOf<T, TypeList<Ts...>> { } > {
	};

	template<typename TFunction, typename ... Ts>
	constexpr decltype(auto) forArgs(TFunction&& mFunction, Ts&&... mArgs) {
		return (void)std::initializer_list<int> { (mFunction(ECS_FWD(mArgs)), 0)... };
	}
};

#endif // !__MPL_H__