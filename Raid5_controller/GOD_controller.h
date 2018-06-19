//
// Created by kenneth on 6/14/18.
//

#ifndef DATOS_RAID_C_GOD_CONTROLLER_H
#define DATOS_RAID_C_GOD_CONTROLLER_H

#include <string>

using namespace std;
class GOD_controller {
public:

    static long size;
    /**
     * Antes de hacer cualquier funcion se llama a check, esto lo que hace es analizar el estado de los discos
     * al mismo tiempo si alguno fue borrado lo reconstruye
     */
static void check();
/**
 * Este no tiene que ser llamado por ustedes, se llama automaticamente en el check
 * lo que hace es reparar un disco
 * @param failure
 */
static void reconstruct_disk(int failure);
/**
 * pasan los parametros y el raid los divide y calcula el tercero
 * @param file los chars del file
 * @param filename Nombre del file
 * @param size Tamano exacto del array file
 */
static void saveFile(char *file, char *filename, long size);
/**
 * Elimina el file de los 3 discos
 * @param filename  nombre del archivo
 */
static void deletefile(char* filename);
/**
 * Edita los nombres
 * @param file_anterior
 * @param filename_nuevo
 */
static void editfilename(char* file_anterior,char* filename_nuevo);
/**
 * da el archivo buscado,OJO con hacer delete[] despues de usarlo
 * @param filename
 * @return
 */
static char* get_file(string filename);

};


#endif //DATOS_RAID_C_GOD_CONTROLLER_H
