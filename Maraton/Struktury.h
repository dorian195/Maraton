#pragma once
/** @file Struktury.h
*	@version Maraton 1.0
*	@date 19/01/2020
*	@author Dorian Barañski
*/
#ifndef FUNKCJE_H
#define FUNKCJE_H
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
using namespace std;

//! Struktura zawodnik
/**
* Ma postaæ drzewa binarnego, przechowuje informacje o zawodnikach. Kazdy zawodnik posiada wskaznik na prawy i lewy element.
*/
struct zawodnik {
	int msce_na_mecie=0;
	string nazwisko;
	int nr_zawodnika=0;
	string czas;
	zawodnik * lewy = nullptr;
	zawodnik * prawy = nullptr;
};
//! Struktura maraton
/**
* Ma postaæ listy jednokierunkowej, przechowuje informacje o maratonie. Kazdy element posiada wskaznik na nastepny oraz na strukture zawodnik.
*/
struct maraton{
	string nazwa_maratonu;
	string data;
	zawodnik* zawodnik_wsk = nullptr;
	maraton* nast = nullptr;
};
//! Struktura nazwiska
/**
* Ma postaæ listy jednokierunkowej, przechowuje nazwiska. Kazdy element posiada wskaznik na nastepnika.
*/
struct nazwiska {
	string nazwisko;
	nazwiska* nast=nullptr;
};

/*-------------------------------Funkcje-------------------------------*/

/**
*@brief Opis funkcji wczytaj
*@param const string& nazwaPliku - nazwa pliku wejsciowego do odczytania danych
*@parammaraton*& glowa - wskaznik na pierwszy element listy maratonow
*@return Zwraca true gdy udalo sie poprawnie wczytac dane z pliku, false gdy plik nie istnieje
*/
bool wczytaj(const string& nazwaPliku, maraton*& glowa);
/**
*@brief Opis funkcji polacz_maratony
*@brief Wywoluje metode wczytaj dla plikow, ktorych nazwy sa zawarte w vectorze maratony. Wywoluje sie do momentu wczytania wszystkich plikow.
*@param vector<string>maratony przechowuje nazwy plikow z maratonami
*@param int ilosc rozmiar wektora
*@param maraton*& glowa wskaznik na pierwszy element listy maraton
*/
void polacz_maratony(vector<string> maratony, int ilosc, maraton*& glowa);
/**
*@brief Opis funkcji zapisz_zawodnika
*@brief Zapisuje zawodnika do pliku w momencie gdy jego nazwisko wystapilo po raz pierwszy.
*@param zawodnik* glowa wskaznik na pierwszy element drzewa zawodnikow
*@param maraton* mGlowa wzkaznik na pierwszy element listy maraton
*/
void zapisz_zawodnika(zawodnik* glowa, maraton* mGlowa);
/**
*@brief Opis funkcji dodaj_wynik_zawodnikowi
*@brief Dopisuje dane do pliku konkretnego zawodnika gdy wystapil w wiecej niz jednym maratonie.
*@param zawodnik* glowa wskaznik na pierwszy element drzewa zawodnikow
*@param maraton* mGlowa wskaznik na pierwszy element listy maratonow
*/
void dodaj_wynik_zawodnikowi(zawodnik* glowa, maraton* mGlowa);
/**
*@brief Opis funkcji zapisz_lub_dodaj
*@brief Sprawdza czy nazwisko danego zawodnika juz wystapilo, jezeli tak to wywoluje funkcje dodaj_wynik_zawodnikowi, jezeli nie to wywoluje zapisz_zawodnika
*@param zawodnik* glowa wskaznik na pierwszy element drzewa zawodnikow
*@param maraton* mGlowa wskaznik na pierwszy element listy maratonow
*@param nazwiska*& nGlowa wskaznik na pierwszy element listy nazwisk
*/
void zapisz_lub_dodaj(zawodnik* glowa, maraton* mGlowa, nazwiska*& nGlowa);
/**
*@brief Opis funkcji zapisz_rekurencja
*@brief Przechodzi po wszystkich elementach drzewa zawodnikow i w zaleznosci od spelnionych warunkow wywoluje funkcje zapisujace
*@param zawodnik* glowa wskaznik na pierwszy element drzewa zawodnikow
*@param maraton* mGlowa wskaznik na pierwszy element listy maratonow
*@param nazwiska*& nGlowa wskaznik na pierwszy element listy nazwisk
*/
void zapisz_rekurencja(zawodnik* glowa, maraton* mGlowa, nazwiska*& nGlowa);
/**
*@brief Opis funkcji zapisz
*@brief Jezeli lista maratonow nie jest pusta wowczas funkcja przechodzi po wszystkich elementach listy i drzewa i wykonuje operacje zapisujace dane zawodnikow w plikach.
*@param maraton* mGlowa wskaznik na pierwszy element listy maratonow
*@param nazwiska* nGlowa wskaznik na pierwszy element listy nazwisk
*/
void zapisz(maraton* mGlowa, nazwiska* nGlowa);
/**
*@brief Opis funkcji usun_liste_i_drzewo
*@brief Zwalnia pamiec ze struktur listy maratonow i drzewa zawodnikow
*@param maraton*& glowa wskaznik na pierwszy element listy maratonow
*/
void usun_liste_i_drzewo(maraton*& glowa);
/**
*@brief Opis funkcji wczytaj_arg
*@brief Odczytuje parametry programu, jezeli sa poprawnie wprowadzone wowczas dodaje nazwy plikow wejsciowych do wektora maratony oraz wywoluje funkcje scalajaca wszystkie podane maratony.
*@param int argc liczba wczytanych argumentow
*@param char* argv[] tablica wskaznikow na znaki badz lancuchy znakow wczytane z linii polecen
*@param maraton*& glowa wskaznik na pierwszy element listy maratonow
*/
bool wczytaj_arg(int argc, char* argv[], maraton*& glowa);
/**
*@brief Opis funkcji maraton_program
*@brief Glowna funkcja programu, wywoluje metody realizujace program w odpowiedniej kolejnosci oraz tworzy dynamicznie nowe elementy strukturalne.
*@param int argc liczba wczytanych argumentow
*@param char* argv[] tablica wskaznikow na znaki badz lancuchy znakow wczytane z linii polecen
*@param
*/
void maraton_program(int argc, char* argv[]);

/*-------------------------------Funkcje Drzewa-------------------------------*/

/**
*@brief Opis funkcji wstaw_do_drzewa
*@brief Wstawia przekazany w argumencie element na odpowiednie miejsce w drzewie
*@param zawodnik*& glowa wskaznik na pierwszy element drzewa zawodnikow
*@param zawodnik*& zawodnikN wskaznik na swiezo wczytany element
*/
void wstaw_do_drzewa(zawodnik*& glowa, zawodnik*& zawodnikN);
/**
*@brief Opis funkcji usun_drzewo
*@brief Funkcja usuwa rekurencyjnie wszystkie elementy drzewa zawodnikow
*@param zawodnik*& glowa wskaznik na pierwszy element drzewa zawodnikow
*/
void usun_drzewo(zawodnik*& glowa);
/**
*@brief Opis funkcji zapisz_zawodnikow_rekurencja
*@brief Rekurencyjnie przechodzi po elementach drzewa zawodnikow i dla kazdego z nich wywoluje funkcje zapisz_zawodnika
*@param zawodnik* glowa wskaznik na pierwszy element drzewa zawodnikow
*@param maraton* mGlowa wskaznik na pierwszy element listy maratonow
*/
void zapisz_zawodnikow_rekurencja(zawodnik* glowa, maraton* pGlowa);

/*-------------------------------Funkcje Listy nazwisk-------------------------------*/

/**
*@brief Opis funkcji dodaj_do_listy_nazwisk
*@brief Obsluguje jednokierunkowa liste nazwisk, dodaje do niej nowe elementy
*@param nazwiska*& glowa wskaznik na pierwszy element listy nazwisk
*@param const string& nazwisko lancuch znakow reprezentujacy nazwisko zawodnika
*/
void dodaj_do_listy_nazwisk(nazwiska*& glowa, const string& nazwisko);
/**
*@brief Opis funkcji znajdz
*@brief Szuka w liscie nazwisko wystapienia przekazanego przez argument nazwiska
*@param nazwiska* glowa wskaznik na pierwszy element listy nazwisk
*@param const string& nazwisko lancuch znakow reprezentujacy nazwisko zawodnika
*@return zwraca wartosc true gdy udalo sie znalezc element w liscie, false gdy sie nie powiodlo
*/
bool znajdz(nazwiska* glowa, const string& nazwisko);
/**
*@brief opis funkcji usun_liste_nazwisk
*@brief Zwalnia pamiec ze struktury listy jednokierunkowej
*@param nazwiska*& glowa wskaznik na pierwszy element listy nazwisk
*/
void usun_liste_nazwisk(nazwiska*& glowa);

#endif