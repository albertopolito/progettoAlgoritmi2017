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
    Grafo<string,string> miografo;
    miografo.setNuovoNodo("a","ciao","b");
    miografo.setNuovoNodo("b","boh","d");
    miografo.setNuovoNodo("b","12","e");
    miografo.setNuovoNodo("e","12","a");
    cout<<miografo.aciclico()<<endl;
}
