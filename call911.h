#ifndef REGISTRO_H_
#define REGISTRO_H_
#include <iostream>
#include <iomanip>
using namespace std;

struct call911{
    int e;
    int id; //atributo secundario
    float lat, lng, zip;
    char addr[66]; //atributo primario
    char desc[121], title[37];
    char timeStamp[20], twp[18];

    void ImprimirDados() {
        string linha = "------------------------------------------------------------------------------------------------------------------------------------";
        cout << "====================================================================================================================================" << endl;
        cout << left << setfill(' ') << setw(9) << "id";
        cout << " | " << id << endl;
        cout << linha << endl;
        cout << setw(9) << "lat";
        cout << " | " << lat << endl;
        cout << linha << endl;
        cout << setw(9) << "lng";
        cout << " | " << lng << endl;
        cout << linha << endl;
        cout << setw(9) << "desc";
        cout << " | " << desc << endl;
        cout << linha << endl;
        cout << setw(9) << "zip";
        cout << " | " << zip << endl;
        cout << linha << endl;
        cout << setw(9) << "title";
        cout << " | " << title << endl;
        cout << linha << endl;
        cout << setw(9) << "timeStamp";
        cout << " | " << timeStamp << endl;
        cout << linha << endl;
        cout << setw(9) << "twp";
        cout << " | " << twp << endl;
        cout << linha << endl;
        cout << setw(9) << "addr";
        cout << " | " << addr << endl;
        cout << linha << endl;
        cout << setw(9) << "e";
        cout << " | " << e << endl;
        cout << "====================================================================================================================================" << endl << endl;	
    }
};

#endif