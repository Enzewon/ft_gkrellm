#include "Ncurses.hpp"

int main(int argc, char *argv[])
{
	(void)argv;
    if (argc == 1)
	{
		Ncurses go;

		go.allplugins();
	}
	else
		std::cout << "Usage: ./ft_gkrellm" << std::endl;
	return (0);
}
