#include "Struktury.h"

/*-------------------------------Funkcje-------------------------------*/

bool wczytaj(const string& nazwaPliku, maraton*& glowa)
{
	fstream plik;
	if (plik.good())
	{
		plik.open(nazwaPliku, ios::in);//otwarcie pliku do odczytu
		zawodnik* zawodnikPierwszy = new zawodnik();//stworzenie nowego elementu listy
		zawodnik* zawodnikN = new zawodnik();//stworzenie nowego elementu listy
		glowa->zawodnik_wsk = zawodnikPierwszy;//polaczenie drzewa z lista
		string przecinek;

		if (!plik.eof())//dopoki plik sie nie skonczy
		{
			getline(plik, glowa->nazwa_maratonu); //wczytuje nazwe
			plik >> glowa->data;//wczytuje date
			plik >> zawodnikPierwszy->msce_na_mecie >> przecinek >> zawodnikPierwszy->nazwisko >> zawodnikPierwszy->nr_zawodnika >> przecinek >> zawodnikPierwszy->czas;//wczytuje dane pierwszemu elementowi drzewa
			zawodnikPierwszy->nazwisko = zawodnikPierwszy->nazwisko.substr(0, zawodnikPierwszy->nazwisko.size() - 1);//usuwa niepotrzebny przecinek z nazwiska

			while (plik >> zawodnikN->msce_na_mecie >> przecinek >> zawodnikN->nazwisko >> zawodnikN->nr_zawodnika >> przecinek >> zawodnikN->czas) {//wczytuje dane kolejnym elementom drzewa
				zawodnikN->nazwisko = zawodnikN->nazwisko.substr(0, zawodnikN->nazwisko.size() - 1);//usuwa przecinek z nazwisk
				wstaw_do_drzewa(zawodnikPierwszy, zawodnikN);//wywolanie funkcji wstaw_do_drzewa() w celu wstawienia elementow w odpowiedniej kolejnosci do drzewa
				if (!plik.eof()) {
					zawodnikN = new zawodnik;//utworzenie nowego elementu
				}
			}
		}
		plik.close();//zamkniecie pliku
		return true;
	}
	else//blad w pliku
	{
		return false;
	}
}

void polacz_maratony(vector<string> maratony, int ilosc, maraton*& glowa)//³aczy listy maratonow 
{
	if (ilosc == 1)
	{
		wczytaj(maratony[0], glowa);
	}
	else
	{
		maraton* wsk = glowa; //wskaznik na glowe listy
		wczytaj(maratony[0], glowa);//wczytanie pierwszego elementu listy 
		for (int i = 1; i < ilosc; i++)//ilosc=maratony.size()
		{
			maraton* tmp = new maraton();
			wczytaj(maratony[i], tmp);

			if (wsk->data > tmp->data)//dodawanie na poczatek listy 
			{
				tmp->nast = wsk;
				wsk = tmp;
			}
			else//jezeli go nie dodwalo na poczatek listy 
			{
				while (glowa->nast)//sprawdz czy jest mniejszy od elementow w liscie 
				{

					if (glowa->nast->data > tmp->data)//dodwanie w srodku listy 
					{
						tmp->nast = glowa->nast;
						glowa->nast = tmp;
						break;
					}
					glowa = glowa->nast;
				}
				if (glowa->nast == nullptr)//dodwanie na koniec listy 
				{
					glowa->nast = tmp;
					tmp->nast = nullptr;

				}
				glowa = wsk;
			}
		}
		glowa = wsk;//przywrocenie glowy na poczatkowe miejsce
	}
}

void zapisz_zawodnika(zawodnik*glowa,maraton *mGlowa)
{
	ofstream plikwy;//zmienna plikowa
	string nazwa = glowa->nazwisko + ".txt";//nazwa pliku wyjsciowego
	plikwy.open(nazwa, ios::trunc);//otwieramy plik i usuwamy poprzednia zawartosc pliku
	plikwy << glowa->nazwisko << "\n" << "\n";//zapisujemy dane do pliku 
	plikwy << mGlowa->data << " " << mGlowa->nazwa_maratonu << " " << glowa->czas << "\n";
	plikwy.close();//zamykamy plik po zakonczeniu operacji na nim
}

void dodaj_wynik_zawodnikowi(zawodnik*glowa,maraton* mGlowa)
{
	ofstream plikwy;//zmienna plikowa
	string nazwa = glowa->nazwisko + ".txt";
	plikwy.open(nazwa, ios::app);//otwarcie pliku w trybie dopisywania
	plikwy << mGlowa->data << " " << mGlowa->nazwa_maratonu << " " << glowa->czas << "\n";//zapisujemy dane do pliku
	plikwy.close();//zamykamy plik po zakonczeniu opercji na nim
}

void zapisz_lub_dodaj(zawodnik* glowa, maraton* mGlowa, nazwiska*& nGlowa) {
	if (znajdz(nGlowa, glowa->nazwisko)) { //jezeli funkcja znajdz() zwroci true
		dodaj_wynik_zawodnikowi(glowa, mGlowa); //to wywoluje funkcje dodaj_wynik_zawodnikowi()
	}
	else { //jezeli zwroci false
		zapisz_zawodnikow_rekurencja(mGlowa->zawodnik_wsk, mGlowa);//to wywoluje funkcje zapisz_zawodnikowi_rekurencja()
		dodaj_do_listy_nazwisk(nGlowa, glowa->nazwisko);//oraz wywoluje funkcje dodaj_do_listy_nazwisk();
	}
}

void zapisz(maraton* mGlowa, nazwiska *nGlowa)
{
	if (mGlowa)
	{
		maraton* tmp = mGlowa;//wskaznik na pierwszy element listy maratonow
		while (mGlowa)
		{
			zawodnik* zad = mGlowa->zawodnik_wsk;//zapisanie korzenia drzewa
			zapisz_rekurencja(mGlowa->zawodnik_wsk, mGlowa,nGlowa);//wywolanie funkcji zapisz_rekurencja() dla danego maratonu
			mGlowa->zawodnik_wsk = zad;//aby nie zgubic elementow drzewa, przypisujemy korzeniowi jego pierwotny stan
			mGlowa = mGlowa->nast;//przesuwamy glowe listy maratonow na nastepny element
		}
		mGlowa = tmp;//aby nie zgubic elementow, przywracamy wskaznik na pierwszy element
		usun_liste_nazwisk(nGlowa);//usuwa liste nazwisk zwalniajac pamiec
		delete nGlowa;
	}
	else//gdyby nie istaniala lista maratonow do zapisania do wyswietlamy blad
	{
		cout << "brak list maratonow" << endl;
	}
}

void wypisz(maraton* glowa) {
	while (glowa) {
		cout << glowa->nazwa_maratonu << endl;
		glowa = glowa->nast;
	}
}

void usun_liste_i_drzewo(maraton*& glowa)
{
	//maraton* tmp = glowa;
	//while (glowa)
	//{
	//	zawodnik* wsk = glowa->zawodnik_wsk;
	//	if (wsk) {//jezeli istnieje element drzewa zawodnikow
	//		usun_drzewo(wsk);//usuwamy drzewo
	//	}
	//	tmp = glowa->nast;
	//	delete glowa;
	//	glowa = tmp;
	//}
	//delete tmp;
	while (glowa)
	{
		maraton* tmp = glowa;
		zawodnik* wsk = glowa->zawodnik_wsk;
		if (wsk) {//jezeli istnieje element drzewa zawodnikow
			usun_drzewo(wsk);//usuwamy drzewo
		}
		glowa = glowa->nast;
		delete tmp;
		cout << wsk << endl;
	}
	delete glowa;
}