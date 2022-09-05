#ifdef USE_FMT
#include <fmt/core.h>

struct world
{
	world()
	{
		fmt::print("Hello, world!\n");
	}
	~world()
	{
		fmt::print("Goodbye! (with fmt)\n");
	}
};
#else
#include <iostream>

struct world
{
	world()
	{
		std::cout << "Hello, world!\n";
	}
	~world()
	{
		std::cout << "Goodbye! (with iostreams)\n" << std::endl;
	}
};
#endif

int main()
{
	world w;
	return 0;
}
