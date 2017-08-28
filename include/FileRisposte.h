#ifndef FILERISPOSTE_H
#define FILERISPOSTE_H
#include"FileInput.h"
#include"VocabolarioId.h"
#include <string>
#include<vector>
#include<algorithm>
#include<iostream>
using namespace std;
template<class R>
class FileRisposte : public FileInput
{
    public:
        FileRisposte(const string nome_file): FileInput(nome_file)
        {
            cout << "call FileRisposte" << endl;
            apriFileInput();
        };
        virtual ~FileRisposte();
        FileRisposte(const FileRisposte& other): FileInput(other)
        {
            apriFileInput();
        };

        bool leggiFile();
        string getRispostaDaId(const R id);
    protected:

    private:
        VocabolarioId<R> _vocabolario_risposte;
};

#endif // FILERISPOSTE_H
