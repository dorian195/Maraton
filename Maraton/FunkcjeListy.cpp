#include "Struktury.h"

/*-------------------------------Funkcje Jednokierunkowej Listy Nazwisk-------------------------------*/

void dodaj_do_listy_nazwisk(nazwiska*& glowa, const string& nazwisko) {
	nazwiska* tmp = new nazwiska{ nazwisko, glowa };//tworzy nowy element ze wskaznikiem na wczesniejszy pierwszy element
	glowa = tmp;//nowy element jako pierwszy w liscie
}

bool znajdz(nazwiska* glowa, const string& nazwisko) {
	while (glowa) {
		if (nazwisko == glowa->nazwisko) {//jezeli znaleziono nazwisko zwraca 1
			return true;
		}
		glowa = glowa->nast;//przejscie na kolejny element
	}
	return false;//jezeli nie znaleziono nazwiska, zwraca 0
}

void usun_liste_nazwisk(nazwiska*& glowa) {
	if (glowa) {//jezeli istnieje element
		while (glowa) {
			nazwiska* tmp = glowa;//nowy element jako pierwszy
			glowa = glowa->nast;//przesuniecie elementu
			delete tmp;//usuniecie pierwszego elementu
		}
	}
	delete glowa;
}