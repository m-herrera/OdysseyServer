//
// Created by kenneth on 6/13/18.
//

#ifndef DATOS_RAID_C_EXISTENCE_CONTROLLER_H
#define DATOS_RAID_C_EXISTENCE_CONTROLLER_H

#include <zconf.h>
#include <pwd.h>
#include <sys/stat.h>
#include <iostream>
using namespace std;
class Existence_controller {
public:
static bool disk_oneok();
static bool disk_twook();
static bool disk_threeok();
static bool firsttime();

};


#endif //DATOS_RAID_C_EXISTENCE_CONTROLLER_H
