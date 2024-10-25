#ifndef __ECRAN_H__
#define __ECRAN_H__

//************** IMPORT LIBRARY **************
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h> // for uintx_t


// ************** CONSTANT DEFINITION **************

#define LIG_MAX 25 // Nombre de ligne maximale
#define COL_MAX 80 // Nombre de colonne maximale
#define MEMOIRE_VIDEO_BASE 0xB8000 //adresse de base de la memoire video CGA

#define COMMAND_PORT 0x3D4
#define DATA_PORT 0x3D5


// ************** DATA STRUCTURES DEFINITION **************
enum {
    NOIR,
    BLEU,
    VERT,
    CYAN,
    ROUGE,
    MAGENTA,
    MARRON,
    GRIS,
    GRIS_FONCE,
    BLEU_CLAIR,
    VERT_CLAIR,
    CYAN_CLAIR,
    ROUGE_CLAIR,
    MAGENTA_CLAIR,
    JAUNE,
    BLANC
};


//************** Prototype of our functions **************

uint16_t *ptr_mem(uint32_t lig, uint32_t col);

void ecrit_car(uint32_t lig, uint32_t col, char c,  uint32_t couleur_caractere, uint32_t couleur_fond, uint32_t clignotement);

void efface_ecran(void);

void place_curseur(uint32_t lig, uint32_t col);

void traite_car(char c);

void defilement(void);

void console_putbytes(const char *s, int len);

void ecrit_temps(const char* temps, int taille);

#endif