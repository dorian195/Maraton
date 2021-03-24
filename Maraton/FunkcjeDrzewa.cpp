#include "Struktury.h"

/*-------------------------------Funkcje Drzewa Zawodnikow-------------------------------*/

void wstaw_do_drzewa(zawodnik*& glowa, zawodnik*& zawodnikN) {
	if (glowa == NULL) {//jezeli element to NULL, wstawia nowy element
		glowa = zawodnikN;
	}
	else if (zawodnikN->nazwisko < glowa->nazwisko) {//jezeli element jest wiekszy od przekazanego
		wstaw_do_drzewa(glowa->lewy, zawodnikN);//przejscie na lewy element
	}
	else {//jezeli element jest mniejszy lub rowny przekazanemu
		wstaw_do_drzewa(glowa->prawy, zawodnikN);//przejscie na prawy element
	}
}

void usun_drzewo(zawodnik*& glowa) {
	if (glowa) {//jezeli istnieje element
		usun_drzewo(glowa->lewy);//przejscie rekurencyjnie na koniec drzewo i usuwanie od konca
		usun_drzewo(glowa->prawy);
		delete glowa;
	}
}

void zapisz_zawodnikow_rekurencja(zawodnik* glowa, maraton* pGlowa) {
	if (glowa != NULL) {//jezeli istnieje element
		zapisz_zawodnikow_rekurencja(glowa->lewy, pGlowa);//przejscie rekurencyjnie na koniec
		zapisz_zawodnika(glowa, pGlowa);//wywolanie funkcji zapisz_zawodnika()
		zapisz_zawodnikow_rekurencja(glowa->prawy, pGlowa);
	}
}

void zapisz_rekurencja(zawodnik* glowa, maraton* mGlowa, nazwiska*& nGlowa) {
	if (glowa != NULL) {
		zapisz_rekurencja(glowa->lewy, mGlowa, nGlowa);//rekurencyjne przejscie po drzewie od konca
		zapisz_lub_dodaj(glowa, mGlowa, nGlowa);//dla kazdegu elmentu wywolanie funkcji zapisz_lub_dodaj()
		zapisz_rekurencja(glowa->prawy, mGlowa, nGlowa);
	}
}