#ifndef __ECRAN_H__
#define __ECRAN_H__

//************** IMPORT LIBRARY **************
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h> // for uintx_t



//************** Prototype of our functions **************

uint16_t *ptr_mem(uint32_t lig, uint32_t col);

// void ecrit_car(uint32_t lig, uint32_t col, char c);
void ecrit_car(uint32_t lig, uint32_t col, char c,  uint32_t couleur_caractere, uint32_t couleur_fond, uint32_t clignotement);

void efface_ecran(void);

void place_curseur(uint32_t lig, uint32_t col);

void traite_car(char c);

void defilement(void);

void console_putbytes(const char *s, int len);

#endif