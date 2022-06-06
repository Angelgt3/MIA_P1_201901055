#include<iostream>
#include<stdlib.h>
#include<fstream>

#include <stdio.h>

using namespace std;

class mkfile
{
public:
    mkfile();
    void crear(string path);
};


mkfile::mkfile(){

}

void mkfile::crear(string path){
    string npath,parch,temp=path;
    int pos;
    while((pos=temp.find("/"))!=string::npos){
        npath += temp.substr(0,pos)+"/";
        temp.erase(0,pos + 1);
    }
    npath+="\"";
    parch="\""+temp;
    
    //cout<<npath<<endl;
    //cout<<parch<<endl;

    //Creo las carpetas hasta llegar a la ruta 
    string comand="sudo mkdir -p "+npath; 
    system(comand.c_str());
    comand="sudo chmod 777 "+npath;
    system(comand.c_str());

    

    //Creo el archivo de texto
    ofstream archivo;
    archivo.open(path.substr(1,path.length()-1),ios::out);
    if (!archivo.fail()){
        archivo<<"hola mundo";
        archivo.close();
    }
       

    
    
}