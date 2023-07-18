#pragma once
#include <iostream>


#define vprint(var) print(#var ":", var)

inline void print(auto val)
{
	std::cout << val;
}

inline void print(auto first, auto ...args)
{
	if constexpr (sizeof ...(args) == 1)
	{
		print(first);
		std::cout << " ";
		print(args...);
		std::cout << std::endl;
	} else
	{
		print(first);
		std::cout << " ";
		print(args...);
	}
}