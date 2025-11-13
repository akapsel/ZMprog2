#include "Logger.h"
#include <iostream>
#include <stdexcept>
#include <sstream>

class Kalkulator {
public:
    virtual ~Kalkulator() = default;
    virtual float Dzialanie(float a, float b) const = 0;
};

class KalkulatorDodawanie : public Kalkulator {
public:
    float Dzialanie(float a, float b) const override {
        return a + b;
    }
};

class KalkulatorOdejmowanie : public Kalkulator {
public:
    float Dzialanie(float a, float b) const override {
        return a - b;
    }
};

class KalkulatorMnozenie : public Kalkulator {
public:
    float Dzialanie(float a, float b) const override {
        return a * b;
    }
};

class KalkulatorIloraz : public Kalkulator {
public:
    float Dzialanie(float a, float b) const override {
        if (b == 0.0f) return 0.0f;   // dzielenie przez 0 -> 0
        return a / b;
    }
};

class KreatorKalkulatora {
    Kalkulator* kalkulator;
public:
    explicit KreatorKalkulatora(char typ) : kalkulator(nullptr) {
        switch (typ) {
        case 'd': kalkulator = new KalkulatorDodawanie();   break;
        case 'o': kalkulator = new KalkulatorOdejmowanie(); break;
        case 'm': kalkulator = new KalkulatorMnozenie();    break;
        case 'i': kalkulator = new KalkulatorIloraz();      break;
        default:
            throw std::invalid_argument("Nieznany typ dzialania");
        }
    }

    Kalkulator* PobierzKalkulator() const {
        return kalkulator;
    }

    void Sprzataj() {
        delete kalkulator;
        kalkulator = nullptr;
    }

    ~KreatorKalkulatora() {
        Sprzataj();
    }
};

int main() {
    try {
        while (true) {

            std::cout << "\n===== MENU =====\n";
            std::cout << "d - dodawanie\n";
            std::cout << "o - odejmowanie\n";
            std::cout << "m - mnozenie\n";
            std::cout << "i - dzielenie\n";
            std::cout << "h - wyswietl historie\n";
            std::cout << "q - wyjscie\n";
            std::cout << "Wybor: ";

            char wybor;
            std::cin >> wybor;

            if (!std::cin) {
                std::cerr << "Blad odczytu danych. Koniec programu.\n";
                break;
            }

            if (wybor == 'q') {
                std::cout << "Koniec programu.\n";
                break;
            }

            if (wybor == 'h') {
                Logger::GetInstance().PrintHistory();
                continue;
            }

            float a, b;
            std::cout << "Podaj pierwszy argument: ";
            std::cin >> a;

            std::cout << "Podaj drugi argument: ";
            std::cin >> b;

            if (!std::cin) {
                std::cerr << "Blad: niepoprawne dane liczbowe.\n";
                // czyścimy strumień wejścia
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            try {
                KreatorKalkulatora k(wybor);

                float wynik = k.PobierzKalkulator()->Dzialanie(a, b);
                std::cout << "Wynik: " << wynik << std::endl;

                // ----------- LOGOWANIE ---------------
                std::stringstream ss;
                ss << a << " ";

                switch (wybor) {
                case 'd': ss << "+"; break;
                case 'o': ss << "-"; break;
                case 'm': ss << "*"; break;
                case 'i': ss << "/"; break;
                default:  ss << "?"; break;
                }

                ss << " " << b << " = " << wynik;
                Logger::GetInstance().Log(ss.str());
                // --------------------------------------

            }
            catch (const std::invalid_argument& e) {
                std::cerr << "Blad: " << e.what() << std::endl;
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Nieoczekiwany blad: " << e.what() << std::endl;
    }

    return 0;
}
