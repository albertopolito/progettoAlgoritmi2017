#ifndef FILELOG_H
#define FILELOG_H
#include <string>
#include<vector>
#include<algorithm>
#include "FileOutput.h"
using namespace std;

template<class T, class R>
class FileLog : public FileOutput
{
    public:
        FileLog(const string nome_file) : FileOutput(nome_file)
        {
        };
        virtual ~FileLog();
        FileLog(const FileLog& other);
        void scriviFileOutput(const R id_risposta,const T id_domanda, const string domanda, const string risposta, const vector<T> domande_successive);

    protected:

    private:
};

#endif // FILELOG_H
