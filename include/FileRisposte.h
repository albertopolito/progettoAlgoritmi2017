#ifndef FILERISPOSTE_H
#define FILERISPOSTE_H
#include"FileInput.h"
#include"VocabolarioId.h"
#include <string>
#include<vector>
#include<algorithm>
using namespace std;
template<class R>
class FileRisposte : public FileInput
{
    public:
        FileRisposte(const string nome_file): FileInput(nome_file)
        {
            apriFileInput();
        };
        virtual ~FileRisposte();
        FileRisposte(const FileRisposte& other);
        ///ritorna il valore 1 se ho un errore in lettura del file altrimenti 0
        const bool getErroreInLettura();
        const string getRispostaDaId(const R id);
        const R getIdDaRisposta(const string risposta);
    protected:

    private:
        VocabolarioId<R> _vocabolario_risposte;
        ///variabile di errore
        bool _errore_lettura_file;
        const bool leggiFile();
};

#endif // FILERISPOSTE_H
