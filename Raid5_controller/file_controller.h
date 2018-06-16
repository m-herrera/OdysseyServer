//
// Created by kenneth on 6/13/18.
//

#ifndef DATOS_RAID_C_FILE_CONTROLLER_H
#define DATOS_RAID_C_FILE_CONTROLLER_H

#include <sys/stat.h>
#include "iostream"
using namespace std;
class file_controller {
public:
    static void rename_file(char* oldname,char* newname);
     static void save_file(char* file,char* filename,long size);
     static void create_disks(){
             struct passwd *pw = getpwuid(getuid());
             const char *homedir = pw->pw_dir;
             string name = homedir;
             string da = name + "/Disk 1";
             mkdir(da.c_str(), 0777);
             da = name + "/Disk 2";
             mkdir(da.c_str(), 0777);
             da = name + "/Disk 3";
             mkdir(da.c_str(), 0777);
     }
     static void create_1_disk(int disk){
         struct passwd *pw = getpwuid(getuid());
         const char *homedir = pw->pw_dir;
         string name = homedir;
         string da;
         if(disk==1){
          da = name + "/Disk 1";
         mkdir(da.c_str(), 0777);
         }
         else if(disk==2){
         da = name + "/Disk 2";
         mkdir(da.c_str(), 0777);}
         else{
         da = name + "/Disk 3";
         mkdir(da.c_str(), 0777);}
     }
    static string* filepath(int disc);
     static void save_file1(char* file,char* filename,long size);
    static void save_file2(char* file,char* filename,long size);
    static void Recontruct_file(char*filename, int failure);
    static  void makefile(char* file1,char*file2,long size,int disc);
    static  char makecharacter(char char1,char char2);
    static char reconstruct_from3rd(char file1,char file3);
    static char* getfile(string filename);
    static void borrar(char* filename);
    static void createfile3(char*file1);
};


#endif //DATOS_RAID_C_FILE_CONTROLLER_H
