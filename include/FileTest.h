#ifndef FILETEST_H
#define FILETEST_H
#include <string>
#include<vector>
#include<algorithm>
#include "FileOutput.h"
#include "FileInput.h"
using namespace std;

template<class T, class R>
class FileTest : public FileInput , FileOutput
{
    struct test {
        R id_risposta;
        T id_domanda;
        bool ho_risposto;
    };
    public:
        FileTest(const string nome_file):FileInput(nome_file),FileOutput(nome_file)
        {
        };
        virtual ~FileTest();
        //aggiungere copy ctr
        R getRispostaDaDomanda(const T id_domanda);
        bool hoFinitoLeDomande();
        void immettiNuovoElemento(const T id_domanda,const R id_risposta);
        void scriviFileOutput();
        bool leggiFile();
    protected:

    private:
        vector<test> _domande_con_risposta;

};

#endif // FILETEST_H
