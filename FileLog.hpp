#ifndef FILELOG_HPP_INCLUDED
#define FILELOG_HPP_INCLUDED
#include <string>
#include<vector>
#include<algorithm>
#include "FileOutput.h"
using namespace std;

template<class T, class R>
class FileLog : public FileOutput
{
    public:
        FileLog();
        virtual ~FileLog();
        ///apre il file richiamando il metodo del padre (FileOutput) ritornando il successo di tale operazione
        const bool apriFileLog(const string nome_file);
        ///chiude il file di log
        void chiudiFileLog();
        ///scrive sul file di log la refertazione con la giusta formattazione
        void scriviFileOutput(const R id_risposta,const T id_domanda, const string domanda, const string risposta, const vector<T> domande_successive);
    protected:
    private:
};

template<class T, class R>
FileLog<T,R>::FileLog()
{
    //ctor
}

template<class T, class R>
FileLog<T,R>::~FileLog()
{
    //dtor
}

template<class T, class R>
const bool FileLog<T,R>::apriFileLog(const string nome_file)
{
    return apriFileOutput(nome_file);
}

template<class T, class R>
void FileLog<T,R>::chiudiFileLog()
{
    chiudiFileOutput();
}


template<class T, class R>
// Scrive il file di log
void FileLog<T,R>::scriviFileOutput(const R id_risposta,const T id_domanda, const string domanda, const string risposta,const vector<T> domande_successive)
{
        _file_output << id_domanda << " " << id_risposta << "\n";
        _file_output << domanda << " "<< risposta << "\n" << "Nuove domande:";
        vector<T> domande=domande_successive;
        typename vector<T>::iterator it;
        for (it=domande.begin();it!=domande.end(); it++){
                if(*it!=T())
                {
                    _file_output << " "<< *it;
                }
        }
        _file_output << endl<<endl;
}


#endif // FILELOG_HPP_INCLUDED
