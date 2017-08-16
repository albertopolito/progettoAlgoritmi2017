#ifndef FILEDOMANDE_H
#define FILEDOMANDE_H
#include"FileInput.h"
#include"VocabolarioId.h"
#include"Grafo.h"
#include <string>
#include<vector>
#include<algorithm>
using namespace std;
template<class T, class R>

class FileDomande : public FileInput
{
    public:
        FileDomande(const string nome_file): FileInput(nome_file)
        {
            apriFileInput();
        };
        virtual ~FileDomande();
        FileDomande(const FileDomande& other);
        bool leggiFile();
        vector<R> getRispostaDataLaDomanda(const T id_domanda);
        vector<T> getDomandaDataRisposta(const T id_domanda, const R id_risposta);
        string getDomandaDaId(const T id_domanda);
        vector<R> getTutteLeRispostePossibili();
    protected:

    private:
        VocabolarioId<R> _vocabolario_domande;
        Grafo<T,R> _grafo_domande_da_sottoporre;
};

#endif // FILEDOMANDE_H
