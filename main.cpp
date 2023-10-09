#include <iostream>
#include <fstream>
using namespace std;

// placeholder struct
struct Teste {
    int id, e;
    float lat, lng, zip;
    string desc, title, timeStamp, twp, addr;
};

// implementar
void imprimirDados(Teste);

void adicionar(fstream& arquivoBin, int posicao) {
    int tamanho;
    Teste dado;

    arquivoBin.seekg(0, ios::end);
    tamanho = arquivoBin.tellg() / sizeof(Teste);

    arquivoBin.seekg(-sizeof(Teste), ios::end);
    arquivoBin.seekp(0, ios::end);

    for (int i = tamanho; i > posicao; i--) {
        arquivoBin.read((char *) &dado, sizeof(Teste));
        arquivoBin.write((const char *) &dado, sizeof(Teste));

        arquivoBin.seekg(-sizeof(Teste), ios::cur);
        arquivoBin.seekp(-sizeof(Teste), ios::cur);
    }

    cout << "===========================================================" << endl;
    cout << "Insira os dados:";
    cout << endl << "id: ";
    cin >> dado.id;
    cout << endl << "lat: ";
    cin >> dado.lat;
    cout << endl << "lng: ";
    cin >> dado.lng;
    cout << endl << "desc: ";
    cin >> dado.desc;
    cout << endl << "zip: ";
    cin >> dado.zip;
    cout << endl << "title: ";
    cin >> dado.title;
    cout << endl << "timeStamp: ";
    cin >> dado.timeStamp;
    cout << endl << "twp: ";
    cin >> dado.twp;
    cout << endl << "addr: ";
    cin >> dado.addr;
    cout << endl << "e: ";
    cin >> dado.e;
    cout << endl << "===========================================================" << endl;

    arquivoBin.write((const char *) &dado, sizeof(Teste));
}

void visualizar(fstream& arquivoBin, int inicio, int fim) { // não inclui a posição final
    Teste dado;
    arquivoBin.seekg(inicio * sizeof(Teste), ios::beg);
    for (int i = inicio; i < fim; i++) {
        arquivoBin.read((char *) &dado, sizeof(Teste));
        imprimirDados(dado);
        arquivoBin.seekg(sizeof(Teste), ios::cur);
    }
}

void visualizar(fstream& arquivoBin) { // visualizar todos
    Teste dado;
    arquivoBin.seekg(0, ios::beg);
    while(not arquivoBin.eof()) {
        arquivoBin.read((char *) &dado, sizeof(Teste));
        imprimirDados(dado);
        arquivoBin.seekg(sizeof(Teste), ios::cur);
    }
}

int main() {
    return 0;
}
