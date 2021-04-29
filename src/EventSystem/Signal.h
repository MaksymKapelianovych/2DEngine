//
// Created by zephyrus on 23.04.21.
//

#ifndef SIGNAL_H
#define SIGNAL_H
#include <iostream>
#include <vector>
#include <utility>
#include <functional>
#include <string>
#include <unordered_set>
#include <set>
#include <type_traits>
#include "FunctionWrapper.h"

enum class ContainerType{
	UNORDERED_SET,
	SET
};

template<ContainerType C, typename ...Args>
class Signal{
public:
	using CallableObject = void(Args...);
	using hashable_function_t = FunctionWrapper<CallableObject,
		FunctionFlags::hashable | FunctionFlags::comparable_eq | FunctionFlags::comparable_less>;
	using Container = std::conditional_t<C == ContainerType::UNORDERED_SET,
		std::unordered_set<hashable_function_t>, std::set<hashable_function_t>>;

private:
	Container objects;

public:
	void add(hashable_function_t g){
		objects.insert(g);
	}

	void remove(hashable_function_t g){
		objects.erase(g);
	}

	void emit(Args... args){
		//removeExpired();
		for(const hashable_function_t&  obj: objects){
			obj(std::forward<Args>(args)...);
		}
	}

private:
//	void removeExpired(){
//		objects.erase(std::remove_if(objects.begin(), objects.end(), [](auto&& function){
//			return bool(function);
//		}), objects.end());
//	}

};

#endif //SIGNAL_H
