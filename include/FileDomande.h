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
            _errore_lettura_file=(leggiFile());
        };
        virtual ~FileDomande();
        FileDomande(const FileDomande& to_copy);
        const bool getErroreInLettura();
        const vector<R> getRispostaDataLaDomanda(const T id_domanda);
        const vector<T> getDomandaDataRisposta(const T id_domanda, const R id_risposta);
        const string getDomandaDaId(const T id_domanda);
        const vector<R> getTutteLeRispostePossibili();
    protected:

    private:
        VocabolarioId<R> _vocabolario_domande;
        Grafo<T,R> _grafo_domande_da_sottoporre;
        bool _errore_lettura_file;
        const bool leggiFile();
};

#endif // FILEDOMANDE_H
