#include <iostream>
#include <cstdlib>

class NodArbore {
public:
    char cheie;
    int numar;
    NodArbore* stanga;
    NodArbore* dreapta;

    NodArbore(char element) : cheie(element), numar(1), stanga(nullptr), dreapta(nullptr) {}
};

class ArboreBinarDeCautare {
private:
    NodArbore* radacina;

    NodArbore* inserare(NodArbore* nod, char cheie) {
        if (nod == nullptr) return new NodArbore(cheie);

        if (cheie == nod->cheie) {
            (nod->numar)++;
        } else if (cheie < nod->cheie) {
            nod->stanga = inserare(nod->stanga, cheie);
        } else {
            nod->dreapta = inserare(nod->dreapta, cheie);
        }

        return nod;
    }

    NodArbore* difSimetricaArbori(NodArbore* arbore1, NodArbore* arbore2) {
        if (arbore1 == nullptr && arbore2 == nullptr) return nullptr;
        if (arbore1 == nullptr) return new NodArbore(arbore2->cheie);
        if (arbore2 == nullptr) return new NodArbore(arbore1->cheie);

        NodArbore* rezultat = new NodArbore(arbore1->cheie);
        rezultat->numar = abs(arbore1->numar - arbore2->numar);

        rezultat->stanga = difSimetricaArbori(arbore1->stanga, arbore2->stanga);
        rezultat->dreapta = difSimetricaArbori(arbore1->dreapta, arbore2->dreapta);

        return rezultat;
    }

    void parcurgereInordine(NodArbore* radacina) {
        if (radacina != nullptr) {
            parcurgereInordine(radacina->stanga);
            if (radacina->numar != 0) {
                std::cout << radacina->cheie << "(" << radacina->numar << ") ";
            }
            parcurgereInordine(radacina->dreapta);
        }
    }

public:
    ArboreBinarDeCautare() : radacina(nullptr) {}

    void inserare(char cheie) {
        radacina = inserare(radacina, cheie);
    }

    void difSimetricaArbori(ArboreBinarDeCautare& arbore2) {
        radacina = difSimetricaArbori(radacina, arbore2.radacina);
    }

    void parcurgereInordine() {
        parcurgereInordine(radacina);
        std::cout << std::endl;
    }
};

int main() {

    ArboreBinarDeCautare arbore1, arbore2;

    // Inserare elemente în arborele 1
    arbore1.inserare('a');
    arbore1.inserare('a');
    arbore1.inserare('a');
    arbore1.inserare('b');
    arbore1.inserare('b');
    arbore1.inserare('c');
    arbore1.inserare('c');
    arbore1.inserare('a');
    arbore1.inserare('c');
    arbore1.inserare('c');
    arbore1.inserare('c');
    arbore1.inserare('c');
    arbore1.inserare('c');
    arbore1.inserare('a');
    arbore1.inserare('a');
    arbore1.inserare('a');
    arbore1.inserare('a');



    // Inserare elemente în arborele 2
    arbore2.inserare('a');
    arbore2.inserare('a');
    arbore2.inserare('b');
    arbore2.inserare('b');
    arbore2.inserare('b');
    arbore2.inserare('b');
    arbore2.inserare('c');
    arbore2.inserare('c');
    arbore2.inserare('c');
    arbore2.inserare('a');
    arbore2.inserare('a');
    arbore2.inserare('a');
    arbore2.inserare('a');

    std::cout << "Parcurgere a arborelui 1: ";
    arbore1.parcurgereInordine();

    std::cout << "Parcurgere arborelui 2: ";
    arbore2.parcurgereInordine();

    arbore1.difSimetricaArbori(arbore2);

    std::cout << "Diferenta simetrica: ";
    arbore1.parcurgereInordine();

    return 0;
}
