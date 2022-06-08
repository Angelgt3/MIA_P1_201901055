#include<iostream>
#include <stdlib.h>
#include <stdio.h>
#include <bits/stdc++.h>
#include "mkdisk.cpp"

using namespace std;

class fdisk
{
public:
    fdisk();
    void crear(int size, char unit, string path,char type, string fit, string dilit, string name,int add, string mov);
    void logica(int inicio, int tamanio,string path,int size,string fit,string name);
    ~fdisk();
};

fdisk::fdisk(){
                
}
//crear particiones logicas
void fdisk::logica(int inicio, int tamanio,string path,int size,string fit,string name){
    FILE *archivo;
    archivo=fopen((path).c_str(),"r");
    if (archivo==NULL)
        printf("HOLA");
    EBR ebr;
    printf("\n");
    fseek(archivo,inicio,SEEK_SET);
    fread(&ebr, sizeof(ebr), 1, archivo); // Guarda el ebr del archivo en "ebr"
    fclose(archivo);
    if (ebr.part_next==0){ //si no hay ebr es 0 
        if (tamanio>size){ //hay espacio disponible
            //Se guarda todo los datos en la estructura
            EBR newebr;
            newebr.part_fit = fit[0];
            strcpy(newebr.part_name, name.c_str());
            newebr.part_next = -1;
            newebr.part_size = tamanio;
            newebr.part_start = inicio;

            // se guarda la estructura en el archivo
            FILE *archivo;
            archivo=fopen(path.c_str(),"r+");
            if (archivo==NULL)
                cout<<"ERROR: No se pudo abrir el archivo"<<endl;
            fseek(archivo,inicio, SEEK_SET);
            fwrite(&newebr, sizeof(EBR), 1, archivo); // Guarda el mbr del archivo
            fclose(archivo);
        }
        else
            cout<<"ERROR: no hay suficiente espacio disponible"<<endl;
    }
    else{ // Ya hay un ebr inicial

    }
    


}

//falta add, mov, delete    -- crear particiones extendidas y primarias
void fdisk::crear(int size, char unit, string path,char type, string fit, string dilit, string name,int add, string mov){
    if(size>0){
        FILE *archivo;  // Se abre el archivo
        archivo=fopen(path.c_str(),"r");
        if (archivo==NULL){
            MBR mbr;
            fseek(archivo,0, SEEK_SET);
            fread(&mbr, sizeof(mbr), 1, archivo); // Guarda el mbr del archivo en "rbm"
            fclose(archivo); // Se cierra el archivo
            
            int nsize;
            if (unit=='b')//nuevo tamaño en bytes
                nsize=size;
            else if(unit=='k')
                nsize=size*1024;
            else if(unit=='m')
                nsize=size*1024*1024;

            for(size_t i=0; i <4;i++){ //busco particion disponible
                if (type=='p'){//Es una particion primaria
                    if (mbr.particiones[i].part_status=='s'){//Encontro una particion disponible - ingresa los datos
                        mbr.particiones[i].part_status='n';
                        mbr.particiones[i].part_fit=fit[0];
                        strcpy(mbr.particiones[i].part_name , name.c_str());//convirtiendo una cadena a un vector char
                        mbr.particiones[i].part_type=type;
                        mbr.particiones[i].part_size=nsize;
                        if(i==0)//si es la primera particion empieza en 0
                            mbr.particiones[i].part_start=0;
                        else
                            mbr.particiones[i].part_start=mbr.particiones[i-1].part_start+mbr.particiones[i-1].part_size;
                        break;
                    }
                    else
                        cout<<"No hay particiones disponibles"<<endl;
                }
                else{
                    if(mbr.particiones[i].part_type=='e'){//si hay particion extendida
                        if (type=='e')//es una extendida
                            cout<<"ERROR: no se puede tener dos particiones extendidas en el disco"<<endl;
                        else if(type=='l'){//es una logica
                            //Crear logica
                            logica(mbr.particiones[i].part_start,mbr.particiones[i].part_size,path,nsize,fit,name);
                        }
                    }
                }
            }
        }
        else
            cout<<"ERRROR: no se encontro el disco"<<endl;
    }
    else   
        cout<<"ERRROR: size <=0"<<endl;
}

fdisk::~fdisk(){}