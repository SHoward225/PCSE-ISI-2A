#include "ordonnanceur.h"
#include "processus.h"
#include "ctx_sw.h"
#include <stddef.h>
#include <stdio.h>


// // Table des processus contenant des pointeurs vers les structures de processus
// processus_t* table_processus[2];

// processus_t* processus_actuel;
// processus_t* idle_process;
// processus_t* proc1_process;


// //--------------- Ajouter un processus dans la table des processus activables
// void ajouter_processus(processus_t* proc) {
//     for (int i = 0; i < 2; i++) {
//         if (table_processus[i] == NULL) {
//             table_processus[i] = proc;
//             return;
//         }
//     };  
// }


// //--------------- Ordonnancement lors du passage d´un processus à l´autre

// void ordonnance(void) {
//     if (processus_actuel == idle_process) {
//         processus_actuel = proc1_process;
//     } else {
//         processus_actuel = idle_process;
//     }

//     // Changement de contexte
//     ctx_sw((uint32_t*)&(idle_process->regs), (uint32_t*)&(proc1_process->regs));
// }


//--------------- Ordonnancement selon l´algorithme du Tourniquet ----------

// void ordonnance(void) {
//     //Sauvegarder lr processus actuel
//     processus_t* ancien_processus=processus_actuel;

//     // Alterner entre idle et proc1
//     if (processus_actuel == idle_process) {
//         processus_actuel = proc1_process;  // Passer à proc1
//     } else {
//         processus_actuel = idle_process;  // Passer à idle
//     }

//     ancien_processus->etat = ACTIVABLE;
//     processus_actuel->etat = ELU;

//     // Changement de contexte vers le nouveau processus
//     ctx_sw((uint32_t*)&(ancien_processus->regs), (uint32_t*)&(processus_actuel->regs));
// }


// ======================== Generalisation a N processus ===========================

// processus_t* table_processus[N] = {NULL};
// processus_t* processus_actuel;

// void ordonnance(void) {
//     processus_t* ancien_processus = processus_actuel;

//     // Rechercher le prochain processus activable
//     int prochain_pid = (ancien_processus->pid + 1) % N;
//     for (int i = 0; i < N; i++) {
//         int index = (prochain_pid + i) % N;
//         if (table_processus[index] != NULL && table_processus[index]->etat == ACTIVABLE) {
//             processus_actuel = table_processus[index];
//             break;
//         }
//     }

//     ancien_processus->etat = ACTIVABLE;
//     processus_actuel->etat = ELU;

//     ctx_sw((uint32_t*)&(ancien_processus->regs), (uint32_t*)&(processus_actuel->regs));
// }

// ======================== Utilisation de listes de processus ===========================

processus_t* tete_activables = NULL;  // Pointeur vers le premier processus activable
processus_t* queue_activables = NULL; // Pointeur vers le dernier processus activable


processus_t* processus_actuel = NULL;
processus_t* idle_process = NULL;
processus_t* proc1_process = NULL;


// Ajouter un processus à la queue des activables
void ajouter_queue_activables(processus_t* proc) {
    proc->suiv = NULL;  // Assurez-vous que le champ `suiv` est nul

    if (queue_activables == NULL) {
        tete_activables = proc;
        queue_activables = proc;
    } else {
        queue_activables->suiv = proc;
        queue_activables = proc;
    }
}



// Extraire le processus en tête des activables
processus_t* retirer_tete_activables(void) {
    if (tete_activables == NULL) {
        printf("Erreur : aucun processus activable.\n");
        return NULL;  // La liste est vide
    }

    processus_t* processus = tete_activables;
    tete_activables = tete_activables->suiv;  // Avancer la tête
    return processus;
}


void ordonnance(void) {
    // Sauvegarder le contexte de l'ancien processus
    processus_t* ancien_processus = processus_actuel;

    // Retirer le processus élu de la liste des activables
    processus_actuel = retirer_tete_activables();

    // Si aucun processus n'est activable, réinsérer le processus idle
    if (processus_actuel == NULL) {
        printf("Erreur : aucun processus activable\n");
    }

    // Ajouter l'ancien processus en queue des activables
    ajouter_queue_activables(ancien_processus);

    // Changer l'état des processus
    ancien_processus->etat = ACTIVABLE;
    processus_actuel->etat = ELU;

    // Changement de contexte vers le nouveau processus
    ctx_sw((uint32_t*)&(ancien_processus->regs), (uint32_t*)&(processus_actuel->regs));
}


