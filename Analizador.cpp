
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <bits/stdc++.h>


#include "mkfile.cpp"
#include "mkdisk.cpp"
#include "rmdisk.cpp"
#include "fdisk.cpp"
#include "mount.cpp"
#include "unmount.cpp"
#include "estructuras.h"

#include <stdio.h>

using namespace std;

class analizar
{
public:
    
    vector<Discos> misdiscos;

    analizar();
    void SE_linea(string linea);
    void Comandos(string comand,string para[]);
    void leer();
};



analizar::analizar(){
    leer();
}

void analizar::Comandos(string comand,string para[]){
    
    //OPCIONES
    
    if(comand!="")
    {    
        //cout<<"comando: "+comand<<endl;
        if (comand=="mkdisk"){ //mkdisk
            int size;
            string path,name;
            for(size_t i=0; i <20;i++){      
                if(para[i]=="")
                    break;
                int pos=para[i].find("=>"); 
                string parametro=para[i].substr(0,pos);
                string valor=para[i].substr(pos+2,para[i].length());

                if (parametro=="") //se sale si ya no viene mas atributos u.u
                    break;
                else if (parametro=="$size"){
                    size=stoi(valor);    
                }
                else if (parametro=="$path"){
                    path=valor.substr(1,valor.length()-2);
                }
                else if (parametro=="$name"){
                    name=valor;
                }
                else
                    cout<<"PARAMETRO NO RECONOCIDO"<<endl;
                //cout<<"parametro: "+parametro<<endl;
                //cout<<"valor: "+valor<<endl;
            }
            mkdisk *mkd=new mkdisk();
            mkd->crear(size,path,name);
            mkd->~mkdisk();
        }else if(comand=="rmdisk"){ //rmdisk
            string path;
            
            for(size_t i=0; i<20;i++){     
                int pos=para[i].find("=>"); 
                string parametro=para[i].substr(0,pos);
                string valor=para[i].substr(pos+2,para[i].length());
                if (parametro=="") //se sale si ya no viene mas atributos u.u
                    break;
                else if (parametro=="$path"){
                    path=valor.substr(1,valor.length()-2);
                    break;
                }
                else
                    cout<<"PARAMETRO NO RECONOCIDO"<<endl;
                //cout<<"parametro: "+parametro<<endl;
                //cout<<"valor: "+valor<<endl;
            } 
            rmdisk *rmd=new rmdisk(path);
            rmd->~rmdisk();
        }else if (comand=="fdisk"){ //fdisk
            int size,add;
            char unit='k',type='p';
            string path,fit="wf",dilit,name,mov;
            for(size_t i=0; i<20 ;i++){  
                if(para[i]=="")
                    break;
                int pos=para[i].find("=>"); 
                string parametro=para[i].substr(0,pos);
                string valor=para[i].substr(pos+2,para[i].length());   
                if (parametro=="$size"){
                    if(stoi(valor)>0)
                        size=stoi(valor);
                    else
                        cout<<"ERROR: El valor de size no cumple los requerimientos";
                }
                else if (parametro=="@unit"){
                    if(valor=="k" || valor=="b" || valor=="m")
                        unit=valor[0];
                    else
                        cout<<"ERROR: El valor de unit no cumple los requerimientos";
                }
                else if (parametro=="$path"){
                    path=valor.substr(1,valor.length()-2);
                }
                else if (parametro=="@type"){
                    if(valor=="p" || valor=="e" || valor=="l")
                        type=valor[0];
                    else
                        cout<<"ERROR: El valor de type no cumple los requerimientos";
                }
                else if (parametro=="@fit"){
                    if(valor=="bf" || valor=="ff" || valor=="wf")
                        fit=valor;
                    else
                        cout<<"ERROR: El valor de fit no cumple los requerimientos";
                }
                else if (parametro=="@delete"){
                    if(valor=="fast" || valor=="full" )
                        dilit=valor;
                    else
                        cout<<"ERROR: El valor de delete no cumple los requerimientos";
                }
                else if (parametro=="$name"){
                    name=valor;
                }
                else if (parametro=="@add"){
                    add=stoi(valor);
                }
                else if (parametro=="@mov"){
                    
                }
                else
                    cout<<"PARAMETRO NO RECONOCIDO"<<endl;
                //cout<<"parametro: "+parametro<<endl;
                //cout<<"valor: "+valor<<endl;
            }
            fdisk *fd=new fdisk(); //creo objeto fdisk
            fd->crear(size,unit,path,type,fit,dilit,name,add,mov);
            fd->~fdisk(); //destruyo objeto
            
        }else if(comand=="mount"){ //mount
            string path,name;
            for(size_t i=0; i <20;i++){    
                if (para[i]=="") //se sale si ya no viene mas atributos u.u
                    break;
                int pos=para[i].find("=>"); 
                string parametro=para[i].substr(0,pos);
                string valor=para[i].substr(pos+2,para[i].length());
                /* condition */
                if (parametro=="$path"){
                    path=valor.substr(1,valor.length()-2);                
                }
                else if (parametro=="$name"){
                    name=valor;
                }
                else
                    cout<<"PARAMETRO NO RECONOCIDO"<<endl;

                //cout<<"parametro: "+parametro<<endl;
                //cout<<"valor: "+valor<<endl;
            } 
            if(path=="" && name==""){ //mount sin  parametros muestra las particiones montadas
                cout<<""<<endl;
                cout<<"-----------------------------PARTICIONES MONTADAS------------------------------"<<endl;
                cout<<""<<endl;
                for (size_t i = 0; i < misdiscos.size(); i++){
                    cout<<"id=>"+misdiscos[i].id+" $path=>"+misdiscos[i].path+" $name=>"+misdiscos[i].name<<endl;
                }
                cout<<""<<endl;
                cout<<"-------------------------------------------------------------------------------"<<endl;
                cout<<""<<endl;
            }else{// mount con parametros
                mount *mou=new mount(); //creo el objeto mount
                Discos temp;
                temp=mou->montar(path,name,misdiscos);
                mou->~mount();//destruyo el objeto
                if (temp.id=="err")
                    cout<<"ERROR: particion ya montada";
                else if (temp.id=="err1")
                    cout<<"ERROR: disco no encontrado";
                else
                    misdiscos.push_back(temp);//lo agrego a mi lista de particiones montadas
            }
        }else if(comand=="unmount"){ //unmount
            for(size_t i=0; i <20;i++){      
                if (para[i]=="") //se sale si ya no viene mas atributos u.u
                    break;
                int pos=para[i].find("=>"); 
                string parametro=para[i].substr(0,pos);
                string valor=para[i].substr(pos+2,para[i].length());
                if (parametro=="$id"+to_string((i+1))){ //$id#
                    for (size_t i = 0; i < misdiscos.size(); i++){ //recorro la lista de las particiones montadas
                        if(misdiscos[i].id==valor){ //encuentro cual hay que desmontar
                            unmount *unm=new unmount();
                            unm->desmontar(misdiscos[i].path,misdiscos[i].name); //funcion para cambiar el status de la particion
                            unm->~unmount();//destruyo el objeto
                            misdiscos.erase(misdiscos.begin()+i); //lo elimino de la lista
                            break;
                        }
                    }
                }
                else
                    cout<<"PARAMETRO NO RECONOCIDO"<<endl;
                //cout<<"parametro: "+parametro<<endl;
                //cout<<"valor: "+valor<<endl;
            } 
        }else if(comand=="mkfs"){ //mkfs
            for(size_t i=0; i <20;i++){    

                int pos=para[i].find("=>"); 
                string parametro=para[i].substr(0,pos);
                string valor=para[i].substr(pos+2,para[i].length());

                if (parametro=="") //se sale si ya no viene mas atributos u.u
                    break;
                else if (parametro=="$id"){

                }
                else if (parametro=="@type"){

                }
                else if (parametro=="@add"){

                }
                else if (parametro=="@unit"){

                }
                else
                    cout<<"PARAMETRO NO RECONOCIDO"<<endl;
                //cout<<"parametro: "+parametro<<endl;
                //cout<<"valor: "+valor<<endl;
            } 
        }else if(comand=="mkfile"){ //mkfile
            string path;
            for(size_t i=0; i <20;i++){    

                int pos=para[i].find("=>"); 
                string parametro=para[i].substr(0,pos);
                string valor=para[i].substr(pos+2,para[i].length());

                if (parametro=="") //se sale si ya no viene mas atributos u.u
                    break;
                else if (parametro=="$id"){

                }
                else if (parametro=="$path"){
                    path=valor;
                }
                else if (parametro=="@p"){

                }
                else if (parametro=="@size"){

                }
                else if (parametro=="@cont"){

                }
                else if (parametro=="$fileid"){

                }
                else
                    cout<<"PARAMETRO NO RECONOCIDO"<<endl;
                //cout<<"parametro: "+parametro<<endl;
                //cout<<"valor: "+valor<<endl;
            } 
            mkfile *mkf= new mkfile();
            mkf->crear(path);
        }else if(comand=="exec"){ //exec
            for(size_t i=0; i <20;i++){     

                int pos=para[i].find("=>"); 
                string parametro=para[i].substr(0,pos);
                string valor=para[i].substr(pos+2,para[i].length());

                if (parametro=="") //se sale si ya no viene mas atributos u.u
                    break;
                else if (parametro=="$path"){

                }
                else
                    cout<<"PARAMETRO NO RECONOCIDO"<<endl;
                //cout<<"parametro: "+parametro<<endl;
                //cout<<"valor: "+valor<<endl;
            } 
        }else if(comand=="rm"){ //rm
            for(size_t i=0; i <20;i++){      

                int pos=para[i].find("=>"); 
                string parametro=para[i].substr(0,pos);
                string valor=para[i].substr(pos+2,para[i].length());
                
                if (parametro=="") //se sale si ya no viene mas atributos u.u
                    break;
                else if (parametro=="$id"){

                }
                else if (parametro=="$fileid"){

                }
                else
                    cout<<"PARAMETRO NO RECONOCIDO"<<endl;
                //cout<<"parametro: "+parametro<<endl;
                //cout<<"valor: "+valor<<endl;
            } 
        }else if(comand=="mkdir"){ //mkdir
            for(size_t i=0; i <20;i++){ 

                int pos=para[i].find("=>"); 
                string parametro=para[i].substr(0,pos);
                string valor=para[i].substr(pos+2,para[i].length());

                if (parametro=="") //se sale si ya no viene mas atributos u.u
                    break;
                else if (parametro=="$id"){

                }
                else if (parametro=="$path"){

                }
                else if (parametro=="@p"){

                }
                else
                    cout<<"PARAMETRO NO RECONOCIDO"<<endl;
                cout<<"parametro: "+parametro<<endl;
                cout<<"valor: "+valor<<endl;
            } 
        }else if(comand=="cp"){ //cp
            for(size_t i=0; i <20;i++){    

                int pos=para[i].find("=>"); 
                string parametro=para[i].substr(0,pos);
                string valor=para[i].substr(pos+2,para[i].length());

                if (parametro=="") //se sale si ya no viene mas atributos u.u
                    break;
                else if (parametro=="$id"){

                }
                else if (parametro=="$path"){

                }
                else if (parametro=="$dest"){

                }
                else if (parametro=="$iddest"){

                }
                else
                    cout<<"PARAMETRO NO RECONOCIDO"<<endl;
                //cout<<"parametro: "+parametro<<endl;
                //cout<<"valor: "+valor<<endl;
            } 
        }else if(comand=="ls"){ //ls
            for(size_t i=0; i <20;i++){      

                int pos=para[i].find("=>"); 
                string parametro=para[i].substr(0,pos);
                string valor=para[i].substr(pos+2,para[i].length());
                
                if (parametro=="") //se sale si ya no viene mas atributos u.u
                    break;
                else if (parametro=="$id"){

                }
                else if (parametro=="$path"){

                }
                else if (parametro=="$Order"){

                }
                else
                    cout<<"PARAMETRO NO RECONOCIDO"<<endl;
                //cout<<"parametro: "+parametro<<endl;
                //cout<<"valor: "+valor<<endl;
            }
        }
        else if(comand=="pause"){ //pause
            cin.get();
        }
        else if(comand=="loss"){ //loss
            for(size_t i=0; i <20;i++){      

                int pos=para[i].find("=>"); 
                string parametro=para[i].substr(0,pos);
                string valor=para[i].substr(pos+2,para[i].length());

                if (parametro=="") //se sale si ya no viene mas atributos u.u
                    break;
                else if (parametro=="$id"){

                }
                else
                    cout<<"PARAMETRO NO RECONOCIDO"<<endl;
                //cout<<"parametro: "+parametro<<endl;
                //cout<<"valor: "+valor<<endl;
            }
        }
        else if(comand=="rep"){ //rep
            for(size_t i=0; i <20;i++){     

                int pos=para[i].find("=>"); 
                string parametro=para[i].substr(0,pos);
                string valor=para[i].substr(pos+2,para[i].length());

                if (parametro=="") //se sale si ya no viene mas atributos u.u
                    break;
                else if (parametro=="$name"){

                }
                else if (parametro=="$path"){

                }
                else if (parametro=="$id"){

                }
                else
                    cout<<"PARAMETRO NO RECONOCIDO"<<endl;
                //cout<<"parametro: "+parametro<<endl;
                //cout<<"valor: "+valor<<endl;
            }
        }
        else
            cout<<"COMANDO NO RECONOCIDO"<<endl;
    }
    
    
    //cout<<"fin de una linea"<<endl;    
}

//separo las lineas por espacios
void analizar::SE_linea(string linea){
    string comand="",palabra,parametros[20];
    for (size_t l = 0; l < 20; l++){ parametros[l]="";}
    stringstream nline(linea);
    int cont=0;
    while (getline(nline, palabra,' ')){
        if (comand!=""){
            parametros[cont]=palabra;
            cont++;
        }
        else
            comand=palabra;
    }
    
    Comandos(comand,parametros);
}

//separo el archivo en lineas
void analizar::leer(){
    ifstream archivo_entrada("entrada.sh");
    string linea;
    while(getline(archivo_entrada, linea)) {
        //lo comvierte todo a minuscula
        transform(linea.begin(), linea.end(), linea.begin(), ::tolower);
        //cout << linea << endl; //separadas por linea
        if(linea.substr(0,2)!="//")
            SE_linea(linea);
        
        
    }

}
