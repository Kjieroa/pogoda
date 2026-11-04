#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

// Struktura przechowujaca jeden pomiar
struct Pomiar
{
    string idStacji;
    string data;
    double temperatura;
    double wiatr;
};

class Pomiary
{
private:
    vector<Pomiar> baza;

public:

    // Wczytywanie danych z pliku
    void wczytajZPliku(string nazwaPliku)
    {
        ifstream plik(nazwaPliku);

        if(!plik.is_open())
        {
            throw runtime_error("Nie mozna otworzyc pliku!");
        }

        string linia;
        int numerLinii = 0;

        while(getline(plik, linia))
        {
            numerLinii++;

            if(linia.empty())
                continue;

            try
            {
                stringstream ss(linia);
                Pomiar p;
                string temperatura, wiatr;

                getline(ss, p.idStacji, ';');
                getline(ss, p.data, ';');
                getline(ss, temperatura, ';');
                getline(ss, wiatr, ';');

                if(p.idStacji.empty() || p.data.empty() ||
                    temperatura.empty() || wiatr.empty())
                {
                    throw runtime_error("Brak wymaganych danych");
                }

                size_t poz1, poz2;

                p.temperatura = stod(temperatura, &poz1);
                p.wiatr = stod(wiatr, &poz2);

                if(poz1 != temperatura.size() || poz2 != wiatr.size())
                {
                    throw runtime_error("Niepoprawny format liczby");
                }

                baza.push_back(p);
            }
            catch(const exception& e)
            {
                cerr<<"Blad w linii "<<numerLinii<<": "<<e.what()<<endl;
            }
        }

        plik.close();

        cout<<"Wczytano "<<baza.size()<<" pomiarow"<<endl;
    }

    // Znalezienie pomiaru z minimalna temperatura
    Pomiar znajdzTemperatureMinimalna()
    {
        if(baza.empty())
        {
            throw runtime_error("Baza pomiarow jest pusta!");
        }

        Pomiar minimum = baza[0];

        for(const Pomiar& p : baza)
        {
            if(p.temperatura < minimum.temperatura)
            {
                minimum = p;
            }
        }

        return minimum;
    }

    // wyszukiwanie pomiarow powyzej zadanego progu
    void wyszukajPowyzejProgu(double prog)
    {
        bool znaleziono=false;

        for(const Pomiar& p : baza)
        {
            if(p.temperatura > prog)
            {
                wyswietlPomiar(p);
                znaleziono = true;
            }
        }

        if(!znaleziono)
        {
            cout<<"Brak pomiarow powyzej "<<prog<<" stopni"<<endl;
        }
    }

    // wyswietlanie pojedynczego pomiaru
    void wyswietlPomiar(const Pomiar& p)
    {
        cout<<"ID stacji: "<<p.idStacji<<endl;
        cout<<"Data: "<<p.data<<endl;
        cout<<"Temperatura: "<<p.temperatura<<" C"<<endl;
        cout<<"Wiatr: "<<p.wiatr<<endl;
        cout<<"------------------------"<<endl;
    }

    // wyswietlanie wszystkich pomiarow
    void wyswietlWszystkie()
    {
        for(const Pomiar& p : baza)
        {
            wyswietlPomiar(p);
        }
    }
};


// program glowny
int main()
{
    Pomiary stacja;

    try
    {
        stacja.wczytajZPliku("dane.txt");
        cout<<endl;
        cout<<"WSZYSTKIE POMIARY:"<<endl;
        stacja.wyswietlWszystkie();
        cout<<endl;
        cout<<"TEMPERATURA MINIMALNA:"<<endl;
        Pomiar min = stacja.znajdzTemperatureMinimalna();
        stacja.wyswietlPomiar(min);
        cout<<endl;
        cout<<"POMIARY POWYZEJ 25 STOPNI:"<<endl;
        stacja.wyszukajPowyzejProgu(25);
    }
    catch(const exception& e)
    {
        cerr<<"BLAD: "<<e.what()<<endl;
    }

    return 0;
}
