#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <bits/stdc++.h>

#include <stdio.h>

using namespace std;

typedef struct {
    char part_status='l'; //l=libre , o=ocupada, m=montada
    char part_type='0';
    char part_fit='0';
    int part_start=-1;
    int part_size=-1;
    char part_name[16];
}PARTITION; //Estructura de las particiones

typedef struct {
    int tamanio;
    time_t fecha_creacion;
    int disk_signature;
    PARTITION particiones[4];
}MBR; //Estructura de los mbr

typedef struct {
    char part_fit;
    int part_start;
    int part_size=0;
    int part_next=-1;
    char part_name[16];
}EBR; //Estructura de los ebr

typedef struct {
    string id;
    string path="";
    string name="";
    int no_letra=0;
    PARTITION particion;
}Discos; //Estructura de las particiones montadas

#endif // ESTRUCTURAS_H