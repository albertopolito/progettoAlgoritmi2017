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
    FileDomande<int,int> file("mio.txt");
    Grafo<int,int> miografo;
    miografo.setNuovoNodo(10,20,30);
    file.getErroreInLettura();
    file.getDomandaDaId(5);
    file.getDomandaDataRisposta(5,10);
    file.getTutteLeRispostePossibili();
    file.getRispostaDataLaDomanda(5);
}
