#include"Struktury.h"
int main(int argc, char* argv[])/*!< Parametry sa wprowadzane z linii polecen */
{
	maraton_program(argc, argv);//wywolanie glownej metody maraton_program()
	_CrtDumpMemoryLeaks();//sprawdza czy program posiada wycieki pamieci
	return 0;
}