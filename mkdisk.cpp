#include<iostream>
#include<stdlib.h>
#include "time.h"
#include <stdio.h>

using namespace std;

class mkdisk
{
public:
    mkdisk();
    void crear(int size,string path,string name);
    void acceso(string path);
    void CrearMBR();
};

typedef struct {
    int tamanio;
    time_t fecha_creacion;
    int disk_signature;
}MBR;

typedef struct {
    char part_status;
    char part_type;
    char part_fit;
    int part_start;
    int part_size;
    char part_name[16];
    
}PARTITION;


mkdisk::mkdisk(){

}

//da todos lo permisos
void mkdisk::acceso(string path){
    int pos=0;
    string temp;
    while((pos=path.find("/"))!=string::npos){
        temp += path.substr(0,pos)+"/";
        cout<<temp<<endl;
        string comand="sudo chmod 777 "+temp;
        system(comand.c_str());
        path.erase(0,pos + 1);
    }
}

void mkdisk::crear(int size,string path,string name){
    if(size>=0 && (size%8)==0){
        //Creo las carpetas
        string comand="sudo mkdir -p "+path; 
        system(comand.c_str());
        //Le doy todos los permisos
        acceso(path);
        //crenado binario
        int tam=size*1024;
        comand = "dd if=/dev/random of="+ path+ name +" count=1024 bs="+to_string(tam);
        system(comand.c_str());
    }else{
        cout<<"error"<<endl;
    }
}

void mkdisk::CrearMBR(){

}