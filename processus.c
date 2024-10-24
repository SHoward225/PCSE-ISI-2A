/**
 * \file processus.c
 * \brief Gère les structures des processus, leur création et l'ordonnancement.
 * \author konan-junior.kouadio@grenoble-inp.org
 * \date 11/10/2024
 */

#include <stdio.h>
#include "processus.h"
#include <string.h>  // Pour `strcpy`

// Table des processus (statiquement définie)
processus_t processus_table[2];

// Pointeur vers le processus actuellement élu
static processus_t* processus_elu = &processus_table[0];  // idle est élu au départ


/***********************************************************************************
 * 
 *                  Fonction pour initialiser les processus
 * 
 * *********************************************************************************
**/ 

void init_processus(void) {

    // Initialisation du processus idle (pid 0)
    processus_table[0].pid = 0;
    strcpy(processus_table[0].nom, "idle");
    processus_table[0].etat = ELU;  // Le processus idle est élu au démarrage

    // Initialisation du processus proc1 (pid 1)
    processus_table[1].pid = 1;
    strcpy(processus_table[1].nom, "proc1");
    processus_table[1].etat = ACTIVABLE;  // Proc1 est activable mais pas élu

}


/***********************************************************************************
 * 
 *                       Fonction d'ordonnancement
 * 
 * *********************************************************************************
**/ 

void ordonnance(void) {
    processus_t* processus_suivant;

    // Passage de idle à proc1 et vice-versa
    if (processus_elu->pid == 0) {
        processus_suivant = &processus_table[1];  // Passer de idle à proc1
    } else {
        processus_suivant = &processus_table[0];  // Passer de proc1 à idle
    }

    processus_suivant->etat = ELU;
    processus_elu->etat = ACTIVABLE;
    
    ctx_sw(processus_elu->registre, processus_suivant->registre);
    
    processus_elu = processus_suivant;  // Mise à jour du processus élu
}

/***********************************************************************************
 * 
 *                      Fonction du processus idle
 * 
 * *********************************************************************************
**/ 

void idle(void) {
    while (1) {
        printf("[idle] Je passe la main à proc1...\n");
        ordonnance();
    }
}

/***********************************************************************************
 * 
 *                        Fonction du processus proc1
 * 
 * *********************************************************************************
**/ 

void proc1(void) {
    while (1) {
        printf("[proc1] Idle m'a donné la main...\n");
        ordonnance();  // Passe la main à idle
    }
}
