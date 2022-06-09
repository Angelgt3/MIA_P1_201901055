#include<iostream>
#include <fstream> 
#include<stdlib.h>
#include "time.h"
#include <stdio.h>

#include "estructuras.h"

using namespace std;

class mkdisk
{
public:
    mkdisk();
    void crear(int size,string path,string name);
    void acceso(string path);
    void CrearMBR(int tam,string path,string name);
    ~mkdisk();
};

mkdisk::mkdisk(){
}

//da todos lo permisos
void mkdisk::acceso(string path){
    int pos=0;
    string temp;
    while((pos=path.find("/"))!=string::npos){
        temp += path.substr(0,pos)+"/";
        //cout<<temp<<endl;
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
        //creando binario
        int tam=size*1024;
        comand = "dd if=/dev/zero of="+ path+ name +" count=1024 bs="+to_string(tam);
        system(comand.c_str());
        CrearMBR(tam,path,name);
    }else{
        cout<<"error"<<endl;
    }
}

void mkdisk::CrearMBR(int tam,string path,string name){
    time_t fecha = time(NULL); //obtener la fecha de creacion
    int valor = rand() % 1000; //numero random 0 a 1000

    //Asignar valores mbr
    MBR mbr;
    mbr.fecha_creacion=fecha;
    mbr.tamanio=tam;
    mbr.disk_signature=valor;

    //escribir el mbr en el disco
    FILE *archivo;
    archivo=fopen((path+name).c_str(),"r+");
    
    fseek(archivo,0, SEEK_SET);
    fwrite(&mbr,sizeof(mbr),1,archivo);
    fclose(archivo);
    
    /*
    FILE *arch;
    arch=fopen((path+name).c_str(),"r");
    if (arch==NULL)
        printf("ERROR");
    MBR mbr2;
    fseek(arch,0, SEEK_SET);
    fread(&mbr2, sizeof(mbr2), 1, arch);

    cout<<""<<endl;
    cout<<mbr2.tamanio<<endl;
    cout<<mbr2.disk_signature<<endl;
    cout<<mbr2.fecha_creacion<<endl;
    */

}

mkdisk::~mkdisk(){

}