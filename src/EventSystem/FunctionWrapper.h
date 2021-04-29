//
// Created by zephyrus on 23.04.21.
//

#ifndef FUNCTION_WRAPPER_H
#define FUNCTION_WRAPPER_H

#include <functional>
#include <utility>

enum class FunctionFlags
{
	none            = 0,
	comparable_less = 0b1,
	comparable_eq   = 0b10,
	hashable        = 0b100,
};
constexpr FunctionFlags operator|(FunctionFlags a, FunctionFlags b) {return FunctionFlags(int(a) | int(b));}
constexpr FunctionFlags operator&(FunctionFlags a, FunctionFlags b) {return FunctionFlags(int(a) & int(b));}

template <typename T, FunctionFlags Flags = FunctionFlags::none>
class FunctionWrapper;

template <typename ReturnType, typename ...ParamTypes, FunctionFlags Flags>
class FunctionWrapper<ReturnType(ParamTypes...), Flags>
{
	std::function<ReturnType(ParamTypes...)> func;
	void* owner = nullptr;
	size_t function_address = 0;

public:
	inline static constexpr bool
		comparable_less = bool(Flags & FunctionFlags::comparable_less),
		comparable_eq   = bool(Flags & FunctionFlags::comparable_eq),
		hashable        = bool(Flags & FunctionFlags::hashable);

	FunctionWrapper() = delete;

	template <typename Clazz>
	FunctionWrapper(ReturnType(Clazz::*function)(ParamTypes...), Clazz* owner)
	{
		if constexpr(sizeof...(ParamTypes) == 0){
			func = [owner, function]() -> ReturnType
			{
				return (owner->*function)();
			};
		}else
		{
			func = [owner, function](ParamTypes&&... args) -> ReturnType
			{
				return (owner->*function)(std::forward<ParamTypes>(args)...);
			};
		}
		this->owner = owner;
	}

	FunctionWrapper(ReturnType(*function)(ParamTypes...))
	{
		if constexpr(sizeof...(ParamTypes) == 0){
			func = [function]() -> ReturnType
			{
				return function();
			};
		}else {
			func = [function](ParamTypes&&... args) -> ReturnType
			{
				return function(std::forward<ParamTypes>(args)...);
			};
		}

		function_address = (size_t) function;
	}

	explicit operator bool() const
	{
		return bool(func);
	}

	ReturnType operator()(ParamTypes ... params) const
	{
		return ReturnType(func(std::forward<ParamTypes>(params)...));
	}

	bool less(const FunctionWrapper &other) const
	{
		static_assert(comparable_less, "This function is disabled.");
		if(owner != nullptr && other.owner != nullptr) return owner < other.owner;
		if(owner == nullptr && other.owner != nullptr) return true;
		if(owner != nullptr && other.owner == nullptr) return false;
		return function_address < other.function_address;
	}

	bool equal_to(const FunctionWrapper &other) const
	{
		static_assert(comparable_eq, "This function is disabled.");
		if(owner != nullptr && other.owner != nullptr) return owner == other.owner;
		if(owner == nullptr && other.owner == nullptr) return function_address == other.function_address;
		return false;
	}

	[[nodiscard]] std::size_t hash() const
	{
		static_assert(hashable, "This function is disabled.");
		return (size_t) owner ^ function_address;
	}

	friend bool operator<(const FunctionWrapper &a, const FunctionWrapper &b) {return a.less(b);}
	friend bool operator>(const FunctionWrapper &a, const FunctionWrapper &b) {return b.less(a);}
	friend bool operator<=(const FunctionWrapper &a, const FunctionWrapper &b) {return !b.less(a);}
	friend bool operator>=(const FunctionWrapper &a, const FunctionWrapper &b) {return !a.less(b);}
	friend bool operator==(const FunctionWrapper &a, const FunctionWrapper &b) {return a.equal_to(b);}
	friend bool operator!=(const FunctionWrapper &a, const FunctionWrapper &b) {return !a.equal_to(b);}
};

namespace std
{
	template <typename T, FunctionFlags Flags> struct hash<FunctionWrapper<T, Flags>>
	{
		using argument_type [[maybe_unused]] = FunctionWrapper<T, Flags>;
		using result_type [[maybe_unused]] = std::size_t;
		result_type operator()(const argument_type &f) const
		{
			return f.hash();
		}
	};
}
#endif //FUNCTION_WRAPPER_H
