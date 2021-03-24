#include "Struktury.h"

/*-------------------------------Funkcje Glowne-------------------------------*/

bool wczytaj_arg(int argc, char* argv[], maraton*& glowa) {
	vector<string> maratony;
	if (argc > 1)//sprawdzamy czy dany prefiks wystepuje w lini polecen
	{
		for (int i = 1; i < argc; i++)
		{
			if (argv[i][0] == '-')//i wiersz 0 element ³ancucha
			{
				switch (argv[i][1])//i wiersz 1 elment ³ancucha
				{
				case 'i'://dla danego prefiku zapisz nazwe maratonu podana z lini polecen do vektora
				{
					maratony.push_back(argv[i + 1]);
					break;
				}
				default:
					cout << "Wprowadzono niepoprawne parametry\n";//w razie bledu gdy podano bledy prefiks
					break;
				}
			}
		}
		polacz_maratony(maratony, maratony.size(), glowa);//wywolanie funkcji scal maratony dla wczytanych nazw plikow 
		return true;
	}
	else//gdy nie podano zadnych argumentow do programu 
	{
		cout << "nie podano protokolow" << endl;
		return false;
	}
}
//--------------------------------------------------------------------
void maraton_program(int argc, char* argv[]) {//funkcja wykonujaca program 
	maraton* mGlowa = new maraton();//tworzymy dynamicznie nowa liste maratonow
	nazwiska* nGlowa = new nazwiska();//tworzymy dynamicznie nowa liste nazwisk
	wczytaj_arg(argc, argv, mGlowa);//wczytujemy dane tworzac strukture listy drzew
	zapisz(mGlowa, nGlowa);//zapisujemy dane do plikow
	usun_liste_i_drzewo(mGlowa);//zwalniamy pamiec ze wszystkich struktur
	delete mGlowa;//usuwamy liste maratonow
	//delete nGlowa;
}