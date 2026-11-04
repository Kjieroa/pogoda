#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <emscripten.h>

using namespace std;

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
    void wczytajZTekstu(const string& tekst, ostream& out)
    {
        baza.clear();

        stringstream plik(tekst);
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
                    throw runtime_error("Brak wymaganych danych");

                size_t poz1, poz2;

                p.temperatura = stod(temperatura, &poz1);
                p.wiatr = stod(wiatr, &poz2);

                if(poz1 != temperatura.size() ||
                   poz2 != wiatr.size())
                    throw runtime_error("Niepoprawny format liczby");

                baza.push_back(p);
            }
            catch(const exception& e)
            {
                out << "Blad w linii " << numerLinii
                    << ": " << e.what() << "\n";
            }
        }

        out << "Wczytano " << baza.size()
            << " pomiarow\n\n";
    }

    Pomiar znajdzTemperatureMinimalna()
    {
        if(baza.empty())
            throw runtime_error("Baza pomiarow jest pusta!");

        Pomiar minimum = baza[0];

        for(const Pomiar& p : baza)
            if(p.temperatura < minimum.temperatura)
                minimum = p;

        return minimum;
    }

    void wyswietlPomiar(const Pomiar& p, ostream& out)
    {
        out << "ID stacji: " << p.idStacji << "\n";
        out << "Data: " << p.data << "\n";
        out << "Temperatura: " << p.temperatura << " C\n";
        out << "Wiatr: " << p.wiatr << "\n";
        out << "------------------------\n";
    }

    void wyswietlWszystkie(ostream& out)
    {
        for(const Pomiar& p : baza)
            wyswietlPomiar(p, out);
    }

    void wyszukajPowyzejProgu(double prog, ostream& out)
    {
        bool znaleziono = false;

        for(const Pomiar& p : baza)
        {
            if(p.temperatura > prog)
            {
                wyswietlPomiar(p, out);
                znaleziono = true;
            }
        }

        if(!znaleziono)
            out << "Brak pomiarow powyzej "
                << prog << " stopni\n";
    }
};

extern "C"
{
    EMSCRIPTEN_KEEPALIVE
    const char* przetworzDane(const char* tekst, double prog)
    {
        static string wynik;

        try
        {
            Pomiary stacja;
            ostringstream out;

            stacja.wczytajZTekstu(tekst, out);

            out << "\nWSZYSTKIE POMIARY:\n";
            stacja.wyswietlWszystkie(out);

            out << "\nTEMPERATURA MINIMALNA:\n";
            Pomiar min = stacja.znajdzTemperatureMinimalna();
            stacja.wyswietlPomiar(min, out);

            out << "\nPOMIARY POWYZEJ "
                << prog << " STOPNI:\n";

            stacja.wyszukajPowyzejProgu(prog, out);

            wynik = out.str();
        }
        catch(const exception& e)
        {
            wynik = string("BLAD: ") + e.what();
        }

        return wynik.c_str();
    }
}
