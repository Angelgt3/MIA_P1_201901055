#include<iostream>
#include <stdlib.h>
#include <stdio.h>
#include <bits/stdc++.h>

#include "estructuras.h"

using namespace std;

class fdisk
{
public:
    fdisk();
    void borrar(string dilit,string path,string name);
    void agregar(int add,char unit,string path,string name);
    void crear(int size, char unit, string path,char type, string fit, string dilit, string name,int add, string mov);
    void logica(int inicio, int tamanio,string path,int size,string fit,string name);
    ~fdisk();
};

fdisk::fdisk(){

}

//parametro delete
void fdisk::borrar(string dilit, string path, string name){

}

// parametro add
void fdisk::agregar(int add,char unit,string path,string name){    
    //GUardo leo y guardo en mbr
    FILE *archivo;
    archivo=fopen(path.c_str(),"r");
    MBR mbr;
    fseek(archivo,0, SEEK_SET);
    fread(&mbr, sizeof(mbr), 1, archivo); 
    fclose(archivo);

    vector<int>inicio;
    vector<int>fin;
    int nsize;
    if (unit=='b')//nuevo tamaño en bytes
        nsize=add;
    else if(unit=='k')//kilobyte a bytes
        nsize=add*1024;
    else if(unit=='m')//megabyte a bytes
        nsize=add*1024*1024; 
    int restante=mbr.tamanio-nsize; //espacio total disco
     for (size_t i = 0; i < 4; i++){ //si hay espacio en la particion
        restante-=mbr.particiones[i].part_size;
    }
    if(restante>0){//si hay espacio en el disco para agregar
        for (size_t i = 0; i < 4; i++){
            if(mbr.particiones[i].part_name==name){//la particion a la cual hay que aumentar
                if ((mbr.particiones[i].part_size+nsize)>0){ //se verifica que si se resta su tamaño sea mayor
                    mbr.particiones[i].part_size+=nsize;//le agrego a su tamaño el add
                    for (size_t j = i+1; j < 4; j++){
                        mbr.particiones[j].part_start+=nsize; //el inicio de las siguientes particiones aunmenta
                    }
                    archivo=fopen(path.c_str(),"r+"); //se abre el archivo para escribir y se guarda 
                    fseek(archivo,0, SEEK_SET);
                    fwrite(&mbr, sizeof(MBR), 1, archivo); 
                    fclose(archivo);
                    break;
                }
                else{
                    cout<<"Error lo maximo que se le puede quitar es: "+to_string(mbr.particiones[i].part_size-1)+" bytes y esta intentando quitar: "+to_string(nsize*-1)+" bytes";
                }
            }
        }
    }else{
        cout<<"Error lo maximo que se puede agregar son: "+ to_string(restante*-1)+" bytes y esta intentando agregar: "+to_string(nsize)+" bytes";
    }
    
}

//crear particiones logicas
void fdisk::logica(int inicio, int tamanio,string path,int size,string fit,string name){
    FILE *archivo;
    archivo=fopen((path).c_str(),"r");
    EBR ebr;
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
            fseek(archivo,inicio, SEEK_SET);
            fwrite(&newebr, sizeof(EBR), 1, archivo); // Guarda el mbr del archivo
            fclose(archivo);
        }
        else
            cout<<"ERROR: no hay suficiente espacio disponible"<<endl;
    }
    else{ // Ya hay un ebr inicial
        
        list<int>inicios;
        list<int>fin;
        list<int>inter;
        int siguiente = 0;
        int ii =0 ;  
        FILE *archivo;
        archivo=fopen(path.c_str(),"r+");
        while(siguiente == 0){
            inicios.push_back(ebr.part_start); // Inicio
            fin.push_back(ebr.part_start + ebr.part_size);// Fin
            ii++;
            if (ebr.part_next != -1){ // si hay mas particiones
                siguiente = fseek(archivo,ebr.part_next,SEEK_SET);// voy al inicio del siguiente ebr
                fread(&ebr, sizeof(ebr), 1, archivo); // leo lo que hay en el espacio
                
            }else{siguiente = -1;}
        }
        
        fclose(archivo); // Se cierra el archivo
        inicios.push_back(tamanio); // Inicio
        fin.push_back(tamanio);// Fin
        list<int>::iterator it = inicios.begin();
        list<int>::iterator ti = fin.begin();
        *it++;
        for(int i= 0; i<ii; i++){
            inter.push_back((*it++) - (*ti++)); // inicio - fin
        }
        list<int>::iterator iti = inter.begin();
        it = inicios.begin();
        ti = fin.begin();
        for(int i= 0; i<ii; i++){
            int in = *it++;
            int fi = *ti++;
            if ((*iti++)>size){
                inicio = fi + 1;
                archivo=fopen(path.c_str(),"r");
                EBR rbe;

                fseek(archivo,in,SEEK_SET);
                fread(&rbe, sizeof(rbe), 1, archivo); // Guarda el ebr del archivo en "rbe"
                rbe.part_next = inicio;
                fclose(archivo); // Se cierra el archivo

                archivo=fopen(path.c_str(),"r+");
                fseek(archivo,in, SEEK_SET);
                fwrite(&ebr, sizeof(EBR), 1, archivo); // Guarda el ebr del archivo
                fclose(archivo);

                EBR nuevo;
                nuevo.part_fit = fit[0];
                strcpy(nuevo.part_name, name.c_str());
                nuevo.part_next = -1;
                nuevo.part_size = size;
                nuevo.part_start = inicio;

                FILE *arch;
                arch=fopen(path.c_str(),"r+");
                fseek(arch,inicio, SEEK_SET);
                fwrite(&nuevo, sizeof(EBR), 1, arch); // Guarda el ebr del archivo
                fclose(arch);
                break;
            }
        }
        
        EBR n;
        FILE *arcs;
        arcs=fopen(path.c_str(),"rb+");
        
        fseek(arcs,inicio, SEEK_SET);
        fread(&n, sizeof(EBR), 1, arcs); 
        fclose(arcs);
        
        //cout << n.part_next <<endl;
        //cout << n.part_start <<endl;
    }
    

}

// crear particiones extendidas y primarias
void fdisk::crear(int size, char unit, string path,char type, string fit, string dilit, string name,int add, string mov){
    if(size>0){
        FILE *archivo;  // Se abre el archivo
        archivo=fopen(path.c_str(),"r");
        MBR mbr;
        fseek(archivo,0, SEEK_SET);
        fread(&mbr, sizeof(mbr), 1, archivo); // Guarda el mbr del archivo en "rbm"
        fclose(archivo); // Se cierra el archivo
        
        int nsize;
        if (unit=='b')//nuevo tamaño en bytes
            nsize=size;
        else if(unit=='k')//kilobyte a bytes
            nsize=size*1024;
        else if(unit=='m')//megabyte a bytes
            nsize=size*1024*1024; 
        
        for(size_t i=0; i <4;i++){ //busco particion disponible
            if (type=='p'){//Es una particion primaria
                if (mbr.particiones[i].part_status=='l'){//Encontro una particion disponible - ingresa los datos
                    mbr.particiones[i].part_status='o'; //l=libre , o=ocupada, m=montada
                    mbr.particiones[i].part_fit=fit[0];
                    strcpy(mbr.particiones[i].part_name , name.c_str());//convirtiendo una cadena a un vector char
                    mbr.particiones[i].part_type=type;
                    mbr.particiones[i].part_size=nsize;
                    if(i==0)//si es la primera particion empieza en 0
                        mbr.particiones[i].part_start=0;
                    else
                        mbr.particiones[i].part_start=mbr.particiones[i-1].part_start+mbr.particiones[i-1].part_size;

                    // Guarda el mbr del archivo
                    archivo=fopen(path.c_str(),"r+");
                    fseek(archivo,0, SEEK_SET);
                    fwrite(&mbr, sizeof(MBR), 1, archivo); 
                    fclose(archivo);
                    break;
                }
            }
            else if(type=='e'){ //Es una extendida
                bool sepuede=true;
                for (size_t j = 0; j < 4; j++){// hay una extendida?
                    if (mbr.particiones[j].part_type=='e'){
                        cout<<"ERROR no se puede tener dos particiones extendidas"<<endl;
                        sepuede=false;
                    }
                }
                if(sepuede){ 
                    for (size_t k = 0; k < 4; k++){// hay espacio
                        if (mbr.particiones[k].part_status=='l'){//Encontro una particion disponible - ingresa los datos
                            mbr.particiones[k].part_status='o'; //l=libre , o=ocupada, m=montada
                            mbr.particiones[k].part_fit=fit[0];
                            strcpy(mbr.particiones[k].part_name , name.c_str());//convirtiendo una cadena a un vector char
                            mbr.particiones[k].part_type=type;
                            mbr.particiones[k].part_size=nsize;
                            if(k==0)//si es la primera particion empieza en 0
                                mbr.particiones[k].part_start=0;
                            else
                                mbr.particiones[k].part_start=mbr.particiones[k-1].part_start+mbr.particiones[k-1].part_size;

                            // Guarda el mbr del archivo
                            archivo=fopen(path.c_str(),"r+");
                            fseek(archivo,0, SEEK_SET);
                            fwrite(&mbr, sizeof(MBR), 1, archivo); 
                            fclose(archivo);
                            break;
                        }
                    }
                }

                break;
            }
            else{
                if(mbr.particiones[i].part_type=='e'){//si hay particion extendida
                    logica(mbr.particiones[i].part_start,mbr.particiones[i].part_size,path,nsize,fit,name);//Crear logica
                }
            }
        }
    }
    else if(add!=0){
        agregar(add,unit,path,name);
    }
    else   
        cout<<"ERRROR"<<endl;

    /*
    //ver las particiones
    FILE *arch;
    arch=fopen((path).c_str(),"r");
    MBR mbr;
    fseek(arch,0, SEEK_SET);
    fread(&mbr, sizeof(mbr), 1, arch);
    fclose(arch);
    
    for(size_t i=0; i <4;i++){
        cout<<"--------------------------------------------------------"<<endl;
        cout<<mbr.disk_signature<<endl;
        cout<<mbr.particiones[i].part_fit<<endl;
        cout<<mbr.particiones[i].part_name<<endl;
        cout<<mbr.particiones[i].part_size<<endl;
        cout<<mbr.particiones[i].part_start<<endl;
        cout<<mbr.particiones[i].part_status<<endl;
        cout<<mbr.particiones[i].part_type<<endl;
        cout<<"--------------------------------------------------------"<<endl;
    }      
    */
}


fdisk::~fdisk(){}
