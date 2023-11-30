/* Equipe:
 * Estevão Augusto da Fonseca Santos
 * Felipe Geraldo de Oliveira
 * Eduardo Cesar Cauduro Coelho
 */


#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>

using namespace std;

struct call911{
	int e;
	int id; //atributo secundario
	float lat, lng, zip;
	char addr[66]; //atributo primario
	char desc[121], title[37];
	char timeStamp[20], twp[18];

	void ImprimirDados();
};

void call911::ImprimirDados() {
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

void intercala(call911 v[], int p, int q, int r) {
    int i = p, j = q + 1;
    int tamanho = r - p + 1;
    call911 w[tamanho]; // vetor auxiliar
	int resultado;
    int k = 0;

    while ((i <= q) && (j <= r)) {
		resultado = strcmp(v[i].addr,v[j].addr);
        if (0 > resultado) {
            w[k++] = v[i++];
        } else if(resultado > 0) {
            w[k++] = v[j++];
        }
		else{
			if (v[i].id > v[j].id) {
        	    w[k++] = v[i++];
        	} else {
            	w[k++] = v[j++];
        	}
		}
    }

    // terminou um dos vetores, agora copia o outro
    while (i <= q) {
        w[k++] = v[i++];
    }

    while (j <= r) {
        w[k++] = v[j++];
    }

    // agora copiamos do vetor auxiliar aux[] em v[p:r]
    for (int m = 0; m < tamanho; m++) {
        v[p + m] = w[m];
    }
}

void mergesort(call911* a, int inicio, int fim) {
    int meio;
    if (inicio < fim) {
        meio = (inicio + fim) / 2;
        mergesort(a, inicio, meio);
        mergesort(a, meio + 1, fim);
        intercala(a, inicio, meio, fim);
    }
}
	
void ordenacao_externa(){
    call911 dado;
    ifstream arquivoBin("binario.dat", ios::binary);
	arquivoBin.seekg(0, ios::end);
	int numero_de_structs = arquivoBin.tellg()/sizeof(call911);
	int numero_de_arquivos;
	if(numero_de_structs%2000 == 0){
		numero_de_arquivos = numero_de_structs/2000;
	}
	else
		numero_de_arquivos = numero_de_structs/2000 + 1;
	string nome_dos_arquivos[numero_de_arquivos];
	arquivoBin.seekg(0, ios::beg);
	int contador = 0;
	for(int i = 0; i < numero_de_arquivos; i++){
		nome_dos_arquivos[i] = "arquivo" + to_string(i) + ".dat";
		ofstream arq(nome_dos_arquivos[i], ios::binary);
		for(int j = 0; j < 2000; j++){
			if(arquivoBin.read((char *) &dado, sizeof(call911))){
				arq.write((const char *) &dado, sizeof(call911));
				contador++;
			}
		}
		arq.close();
	}
	for(int i = 0; i < numero_de_arquivos; i++){
		ifstream arq(nome_dos_arquivos[i], ios::binary);
		arq.seekg(0, ios::end);
		int tamanho_do_vetor = arq.tellg()/sizeof(call911);
		call911 vetor[tamanho_do_vetor];
		arq.seekg(0, ios::beg);
		for(int j = 0; j < tamanho_do_vetor; j++){
			arq.read((char *) &vetor[j], sizeof(call911));
		}
		mergesort(vetor, 0, tamanho_do_vetor-1);
		arq.close();
	}
}

int main(){
	ordenacao_externa();
	return 0;
}
