#include <iostream>
#include"VocabolarioId.h"
#include"Nodo.h"
#include"Grafo.h"
#include"FileInput.h"
#include"FileDomande.h"
#include"FileRisposte.h"
#include"FileStart.h"
using namespace std;

int main()
{
    string nome_A;
    cin >> nome_A;
    cin.ignore();
    FileStart<int> A(nome_A);
    A.leggiFile();
    A.testStampaListaDomande();
    return 0;
}
