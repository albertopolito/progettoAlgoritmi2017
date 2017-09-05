#ifndef FILELOG_H
#define FILELOG_H
#include <string>
#include<vector>
#include<algorithm>
#include "FileOutput.h"
#include <iostream>
using namespace std;

template<class T, class R>
class FileLog : public FileOutput
{
    public:
        FileLog();
        virtual ~FileLog();
        const bool apriFileLog(const string nome_file);
        FileLog(const FileLog& other);
        void chiudiFileLog();
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
FileLog<T,R>::FileLog(const FileLog& other)
{
    //copy ctor
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
            _file_output << " "<< *it;
        }
        _file_output << "\n";
}

#endif // FILELOG_H
