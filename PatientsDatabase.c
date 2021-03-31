#pragma warning(disable:4996)
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#define _CRT_SECURE_NO_WARNINGS

#define MAX_STR_LEN 1024

void menu();
int liczba(const char *);
char* ileString();
int wyszukiwarka(char *string, char *plik);
int pacjenciPrint();
void dopisywaniePlik();
int pacjenciPlik();

struct pacjent {
	int numerId;
	char *nazwisko;
	char *numerTelefonu;
	char *dataUrodzenia;
	char *adresZamieszkania;
};


void menu()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 48);
	printf("Wcisnij odpowiednia cyfre by przejsc dalej.\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	printf("1.Wyszukiwanie wyrazu w spisie pacjentow.\n");
	printf("2.Wyswietlenie listy pacjentow.\n");
	printf("3.Dodawanie pacjenta do listy.\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

int liczba(const char* a)
{
	int c, n;

	n = 0;
	for (c = 0; a[c] != '\0'; c++)
	{
		if (isdigit(a[c]))
			n = n * 10 + a[c] - '0';
	}

	return n;
}


char* ileString()
{
	char *string;
	char str[100];
	int len = 0;
	gets(str);
	len = strlen(str);
	string = malloc(len + 1);
	strcpy(string, str);
	return string;
}


int wyszukiwarka(char *string, char *plik)
{
	int n = 0;
	int m = 0;
	int ile = 0;
	int len = 0;
	len = strlen(string);
	char *str = strlwr(string);
	char *str2 = strlwr(plik);

	while (str[n] != '\0')
	{
		if (str[n] == str2[m])
		{
			while (str[n] == str2[m] && str[n] != '\0')
			{
				n++;
				m++;
			}
			if (m == len && (str[n] == ' ' || str[n] == '\0'))
			{
				ile++;
			}
		}
		else
		{
			while (str[n] != ' ')
			{
				n++;
				if (str[n] == '\0')
					break;
			}
		}
	}
	return ile;
}

void pacjenciLoad(char *nazwapliku)
{
	FILE *plik = NULL;
	
	if ((plik = fopen("pacjenciprzychodni.csv", "r")) == NULL) {
		printf("Wystapil blad otwarcia pliku.\n");
		system("Pause");
		return 1;
	}



}



int pacjenciPrint()  //zmienna przez referencje która przetrzymuje aktualny rozmiar tabliyc oacjenci , tablica pacjenci przez referenjce 
{
	FILE *plik = NULL;
	char *pmt = NULL;
	char *buf = malloc(MAX_STR_LEN);
	int counter = 0;
	int i = 0;
	int j = 0;

	struct pacjent *pacjenci = malloc(sizeof(struct pacjent));//TODO spradzic jak sie alokuje tablicê

	if (buf == NULL) {
		printf("Brak pamieci.\n");
		system("Pause");
		return 1;
	}

	if ((plik = fopen("pacjenciprzychodni.csv", "r")) == NULL) {
		printf("Wystapil blad otwarcia pliku.\n");
		system("Pause");
		return 1;
	}

	while (fgets(buf, 1024, plik) != NULL) {
		if ((strlen(buf) > 0) && (buf[strlen(buf) - 1] == '\n')) {
			buf[strlen(buf) - 1] = '\0';
		}

		pacjenci = realloc(pacjenci, sizeof(pacjenci) + ++counter * sizeof(struct pacjent));


		pmt = strtok(buf, ",");
		pacjenci[i].numerId = liczba(pmt);

		pmt = strtok(NULL, ",\"");
		pacjenci[i].nazwisko = malloc(strlen(pmt) + 1);
		strcpy(pacjenci[i].nazwisko, pmt);

		pmt = strtok(NULL, ",\"");
		pacjenci[i].numerTelefonu = malloc(strlen(pmt) + 1);
		strcpy(pacjenci[i].numerTelefonu, pmt);

		pmt = strtok(NULL, ",\"");
		pacjenci[i].dataUrodzenia = malloc(strlen(pmt) + 1);
		strcpy(pacjenci[i].dataUrodzenia, pmt);

		pmt = strtok(NULL, ",\"");
		pacjenci[i].adresZamieszkania = malloc(strlen(pmt) + 1);
		strcpy(pacjenci[i].adresZamieszkania, pmt);

		printf("%3i| %13s| %7s| %7s| %s\n", pacjenci[i].numerId, pacjenci[i].nazwisko, pacjenci[i].numerTelefonu, pacjenci[i].dataUrodzenia, pacjenci[i].adresZamieszkania);

		i++;
	}

	free(buf);
	while (j < counter) {
		free(pacjenci[j].nazwisko);
		free(pacjenci[j].dataUrodzenia);
		free(pacjenci[j].adresZamieszkania);
		free(pacjenci[j].numerTelefonu);
		j++;
	}
	free(pacjenci);
	fclose(plik);
	return 0;
}


void dopisywaniePlik()
{
	puts("Wprowadz nazwisko pacjenta:");
	char *nazwisko = ileString();
	puts("Wprowadz numer pacjenta:");
	char *numer = ileString();
	puts("Wprowadz date urodzenia pacjenta:");
	char *data = ileString();
	puts("Wprowadz adres pacjenta:");
	char *adres = ileString();
	
	FILE *plik;

	if ((plik = fopen("pacjenciprzychodni.csv", "a+")) == NULL)
	{
		printf("Wystapil blad otwarcia pliku.\n");
		system("Pause");
		return 1;
	}

	int linie = 0;
	char c;

	for (c = getc(plik); c != EOF; c = getc(plik))
		if (c == '\n')
			linie = linie + 1;

	int id = linie + 1;

	printf("\"%d\",\"%s\",\"%s\",\"%s\",\"%s\"\n", id, nazwisko, numer, data, adres);
	fprintf(plik, "\"%d\",\"%s\",\"%s\",\"%s\",\"%s\"\n", id, nazwisko, numer, data, adres);
}


int pacjenciPlik()
{
	FILE *plik = NULL;
	char *pmt = NULL;
	char *buf = malloc(MAX_STR_LEN);
	puts("Wprowadz szukana fraze:");
	char *string = ileString();
	int counter = 0;
	int ile = 0;
	int i = 0;
	int j = 0;
	int a = 0;
	int b = 0;
	int c = 0;
	int d = 0;
	struct pacjent *pacjenci = malloc(sizeof(struct pacjent));

	if (buf == NULL) {
		printf("Brak pamieci.\n");
		system("Pause");
		return 1;
	}

	if ((plik = fopen("pacjenciprzychodni.csv", "r")) == NULL) {
		printf("Wystapil blad otwarcia pliku.\n");
		system("Pause");
		return 1;
	}

	while (fgets(buf, 1024, plik) != NULL) {
		if ((strlen(buf) > 0) && (buf[strlen(buf) - 1] == '\n')) {
			buf[strlen(buf) - 1] = '\0';
		}

		
		pacjenci = realloc(pacjenci, sizeof(pacjenci) + ++counter * sizeof(struct pacjent));


		pmt = strtok(buf, ",");
		pacjenci[i].numerId = liczba(pmt);

		pmt = strtok(NULL, ",\"");
		pacjenci[i].nazwisko = malloc(strlen(pmt) + 1);
		strcpy(pacjenci[i].nazwisko, pmt);

		pmt = strtok(NULL, ",\"");
		pacjenci[i].numerTelefonu = malloc(strlen(pmt) + 1);
		strcpy(pacjenci[i].numerTelefonu, pmt);

		pmt = strtok(NULL, ",\"");
		pacjenci[i].dataUrodzenia = malloc(strlen(pmt) + 1);
		strcpy(pacjenci[i].dataUrodzenia, pmt);

		pmt = strtok(NULL, ",\"");
		pacjenci[i].adresZamieszkania = malloc(strlen(pmt) + 1);
		strcpy(pacjenci[i].adresZamieszkania, pmt);

		a += wyszukiwarka(string, pacjenci[i].nazwisko);
		b += wyszukiwarka(string, pacjenci[i].numerTelefonu);
		c += wyszukiwarka(string, pacjenci[i].dataUrodzenia);
		d += wyszukiwarka(string, pacjenci[i].adresZamieszkania);
		i++;
	}
	ile = a + b + c + d;
	if (ile > 0) {
		printf("'%s' wystepuje %d raz/razy.\n", string, ile);
	}
	else {
		printf("'%s' nie wystepuje w pliku.\n", string);
	}
	free(buf);
	while (j < counter) {
		free(pacjenci[j].nazwisko);
		free(pacjenci[j].dataUrodzenia);
		free(pacjenci[j].adresZamieszkania);
		free(pacjenci[j].numerTelefonu);
		j++;
	}
	free(pacjenci);
	fclose(plik);
	return 0;
}

int main() {


	int liczbapacjentow = 0;
	char *nazwapliku = "pacjenciprzychodni.csv";
	
	/*

	int wybor;
	menu();
	scanf("%d", &wybor);

	switch (wybor)
	{
	case 1:
		pacjenciPlik();
		break;
	case 2:
		pacjenciPrint();
		break;
	case 3:
		dopisywaniePlik();
		break;
	}
	*/
	//pacjenciPlik();
	struct pacjent *pacjenci = malloc(sizeof(struct pacjent));

	//1. load
	pacjenciLoad(pacjenci, liczbapacjentow, nazwapliku);
	//2. print
	//3. dodaj usun edutyj pacjnta

	//dopisywaniePlik();
	//pacjenciPlik();
	int j = 0;
	while (j < liczbapacjentow) {
		free(pacjenci[j].nazwisko);
		free(pacjenci[j].dataUrodzenia);
		free(pacjenci[j].adresZamieszkania);
		free(pacjenci[j].numerTelefonu);
		j++;
	}
	free(pacjenci);
	system("pause");
	return 0;
}