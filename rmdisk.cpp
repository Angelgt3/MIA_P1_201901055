#include<iostream>
#include<stdlib.h>

#include <stdio.h>

using namespace std;

class rmdisk
{
public:
    rmdisk(string path);
    ~rmdisk();
};

rmdisk::rmdisk(string path){
    cout<<"Esta seguro que desea eliminar "+path+" (S/N)"<<endl;
    string res;
    cin>>res;
    if (res=="s" || res=="S"){
        string comand="rm "+path;
        system(comand.c_str());
    }
}

rmdisk::~rmdisk(){
    
}