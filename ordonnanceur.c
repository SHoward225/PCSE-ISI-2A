#include "ordonnanceur.h"
#include "processus.h"
#include "ctx_sw.h"
#include <stddef.h>


processus_t* table_processus[2];

processus_t* processus_actuel;
processus_t* idle_process;
processus_t* proc1_process;


//--------------- Ajouter un processus dans la table des processus activables
void ajouter_processus(processus_t* proc) {
    for (int i = 0; i < 2; i++) {
        if (table_processus[i] == NULL) {
            table_processus[i] = proc;
            return;
        }
    };  
}


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


//--------------- Ordonnancement selon l´algorithme du Tourniquet

void ordonnance(void) {
    //Sauvegarder lr processus actuel
    processus_t* ancien_processus=processus_actuel;

    // Alterner entre idle et proc1
    if (processus_actuel == idle_process) {
        processus_actuel = proc1_process;  // Passer à proc1
    } else {
        processus_actuel = idle_process;  // Passer à idle
    }

    ancien_processus->etat = ACTIVABLE;
    processus_actuel->etat = ELU;

    // Changement de contexte vers le nouveau processus
    ctx_sw((uint32_t*)&(ancien_processus->regs), (uint32_t*)&(processus_actuel->regs));
}


