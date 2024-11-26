
#include <stdio.h>
#include <tinyalloc.h>

#include "ordonnanceur.h"
#include "processus.h"
#include "cpu.h"
#include "ctx_sw.h"

#define TAILLE_PILE 512  // Taille de la pile pour chaque processus
#define N_PROCESSUS 8

extern processus_t* processus_actuel;  // Déclaration, pas de définition

// ================================ EXEMPLE A DEUX PROCESSUS =========================================

// // Fonction pour initialiser un processus avec les informations fournies
// void init_processus(processus_t* proc, uint32_t pid, char* nom, void (*fonction)(void)) {
//     proc->pid = pid;
//     proc->nom = nom;
//     proc->etat = ACTIVABLE;

//     // Allouer la pile pour le processus
//     proc->pile = (uint32_t*) malloc(TAILLE_PILE * sizeof(uint32_t));
//     if (proc->pile == NULL) {
//         printf("Erreur d'allocation de la pile pour le processus %s\n", nom);
//         return;
//     }
//     proc->pile_base = proc->pile;

//     // Préparer la pile pour la première exécution
//     proc->pile[TAILLE_PILE - 1] = (uint32_t) fonction;  // Adresse de la fonction
//     proc->regs.esp = (uint32_t) &proc->pile[TAILLE_PILE - 1];  // ESP pointe vers cette adresse
//     proc->regs.ebx = 0;
//     proc->regs.ebp = 0;
//     proc->regs.esi = 0;
//     proc->regs.edi = 0;

//     printf("Processus %s (PID=%u) initialise avec succes.\n", nom, pid);
    
// }


// // Initialiser les processus idle et proc1
// void init_processus_idle_proc1(void) {
//     idle_process = (processus_t*) malloc(sizeof(processus_t));
//     proc1_process = (processus_t*) malloc(sizeof(processus_t));

//     if (idle_process == NULL || proc1_process == NULL) {
//         printf("Erreur d'allocation de mémoire pour les processus.\n");
//         return;
//     }
    
//     // Initialiser le processus idle (PID 0)
//     init_processus(idle_process, 0, "idle", idle);

//     // Initialiser le processus proc1 (PID 1)
//     init_processus(proc1_process, 1, "proc1", proc1);

//     // Ajouter les processus dans la table des processus
//     table_processus[0] = idle_process;
//     table_processus[1] = proc1_process;

//     // Définir idle comme processus initial
//     processus_actuel = idle_process;
// }



// ----------------------------- Passage dún processus à l´autre ---------------------------------------
// void idle(void) {
//     printf("[idle] je tente de passer la main a proc1...\n");
//             ctx_sw((uint32_t*)&(idle_process->regs), (uint32_t*)&(proc1_process->regs));  // Passage de idle à proc1
// }


// void proc1(void) {
//     printf("[proc1] idle m’a donne la main\n");
//     printf("[proc1] j’arrete le système\n");
//     hlt();  // Arrête le système
// }

// ============================= Aller et retour entre processus ==============================================

// void idle(void) {
//     for (int i = 0; i < 3; i++) {
//         printf("[idle] je tente de passer la main a proc1...\n");
//          ctx_sw((uint32_t*)&(idle_process->regs), (uint32_t*)&(proc1_process->regs));;
//         printf("[idle] proc1 m’a redonne la main\n");
//     }
//     printf("[idle] je bloque le systeme\n");
//     hlt();
// }

// void proc1(void) {
//     for (;;) {
//         printf("[proc1] idle m’a donne la main\n");
//         printf("[proc1] je tente de lui la redonner...\n");
//          ctx_sw((uint32_t*)&(proc1_process->regs), (uint32_t*)&(idle_process->regs));;
//     }
// }


// ----------------------------- Ordonnancement selon l´algorithme du Tourniquet -----------------------------

// void idle(void){
//     for (;;) {
//         printf("[%s] pid = %i\n", mon_nom(), mon_pid());
//         ordonnance();
//         }
// }

// void proc1(void) {
//     for (;;) {
//         printf("[%s] pid = %i\n", mon_nom(), mon_pid());
//         ordonnance();
//     }
// }


// // Prototypes pour récupérer le PID et le nom du processus en cours
// int32_t mon_pid(void){
//     if (processus_actuel != NULL) {
//         return processus_actuel->pid;
//     } else {
//         printf("Erreur : processus_actuel est NULL\n");
//         return -1; // Valeur de retour d'erreur
//     }
// }

// char *mon_nom(void){
//     if (processus_actuel != NULL) {
//         return processus_actuel->nom;
//     } else {
//         printf("Erreur : processus_actuel est NULL\n");
//         return "Inconnu"; // Valeur de retour par défaut
//     }
// }


// ================================ Generalisation a N processus ======================


// // Fonction pour initialiser un processus avec les informations fournies
// void init_processus(processus_t* proc, uint32_t pid, char* nom, void (*fonction)(void)) {
//     proc->pid = pid;
//     proc->nom = nom;
//     proc->etat = ACTIVABLE;

//     // Allouer la pile pour le processus
//     proc->pile = (uint32_t*) malloc(TAILLE_PILE * sizeof(uint32_t));
//     if (proc->pile == NULL) {
//         printf("Erreur d'allocation de la pile pour le processus %s\n", nom);
//         return;
//     }
//     proc->pile_base = proc->pile;

//     // Préparer la pile pour la première exécution
//     proc->pile[TAILLE_PILE - 1] = (uint32_t) fonction;  // Adresse de la fonction
//     proc->regs.esp = (uint32_t) &proc->pile[TAILLE_PILE - 1];  // ESP pointe vers cette adresse
//     proc->regs.ebx = 0;
//     proc->regs.ebp = 0;
//     proc->regs.esi = 0;
//     proc->regs.edi = 0;
// }


// // Fonction générique pour créer un processus
// uint32_t creer_processus(void (*code)(void), char* nom) {
//     for (int i = 0; i < N; i++) {
//         if (table_processus[i] == NULL) {
//             processus_t* nouveau_proc = (processus_t*) malloc(sizeof(processus_t));
//             if (nouveau_proc == NULL) {
//                 printf("Erreur : impossible d'allouer la mémoire pour le processus %s\n", nom);
//                 return -1; // Code d'erreur
//             }
//             init_processus(nouveau_proc, i, nom, code);
//             table_processus[i] = nouveau_proc;
//             return i; // Retourner le PID
//         }
//     }
//     printf("Erreur : table des processus pleine\n");
//     return -1; // Code d'erreur
// }


// void idle(void){
//     for (;;) {
//         printf("[%s] pid = %i\n", mon_nom(), mon_pid());
//         ordonnance(); // Passer au processus suivant
//     }
// }


// void proc1(void) {
//     for (;;) {
//         printf("[%s] pid = %i\n", mon_nom(), mon_pid());
//         ordonnance(); // Passer au processus suivant
//     }
// }

// void proc2(void) {
//     for (;;) {
//         printf("[%s] pid = %i\n", mon_nom(), mon_pid());
//         ordonnance(); // Passer au processus suivant
//     }
// }

// void proc3(void) {
//     for (;;) {
//         printf("[%s] pid = %i\n", mon_nom(), mon_pid());
//         ordonnance(); // Passer au processus suivant
//     }
// }

// void proc4(void) {
//     for (;;) {
//         printf("[%s] pid = %i\n", mon_nom(), mon_pid());
//         ordonnance(); // Passer au processus suivant
//     }
// }

// void proc5(void) {
//     for (;;) {
//         printf("[%s] pid = %i\n", mon_nom(), mon_pid());
//         ordonnance(); // Passer au processus suivant
//     }
// }

// void proc6(void) {
//     for (;;) {
//         printf("[%s] pid = %i\n", mon_nom(), mon_pid());
//         ordonnance(); // Passer au processus suivant
//     }
// }

// void proc7(void) {
//     for (;;) {
//         printf("[%s] pid = %i\n", mon_nom(), mon_pid());
//         ordonnance(); // Passer au processus suivant
//     }
// }

// // Prototypes pour récupérer le PID et le nom du processus en cours
// int32_t mon_pid(void){
//     if (processus_actuel != NULL) {
//         return processus_actuel->pid;
//     } else {
//         printf("Erreur : processus_actuel est NULL\n");
//         return -1; // Valeur de retour d'erreur
//     }
// }

// char *mon_nom(void){
//     if (processus_actuel != NULL) {
//         return processus_actuel->nom;
//     } else {
//         printf("Erreur : processus_actuel est NULL\n");
//         return "Inconnu"; // Valeur de retour par défaut
//     }
// }

// ======================== Utilisation de listes de processus ===========================

processus_t processus[N_PROCESSUS];
uint32_t pid_counter = 0;

// Initialiser un processus avec les informations fournies
void init_processus(processus_t* proc, uint32_t pid, char* nom, void (*fonction)(void)) {
    proc->pid = pid;
    proc->nom = nom;
    proc->etat = ACTIVABLE;

    // Allouer la pile pour le processus
    proc->pile = (uint32_t*) malloc(TAILLE_PILE * sizeof(uint32_t));
    if (proc->pile == NULL) {
        printf("Erreur d'allocation de la pile pour le processus %s\n", nom);
        return;
    }
    proc->pile_base = proc->pile;

    // Préparer la pile pour la première exécution
    proc->pile[TAILLE_PILE - 1] = (uint32_t) fonction;  // Adresse de la fonction
    proc->regs.esp = (uint32_t) &proc->pile[TAILLE_PILE - 1];  // ESP pointe vers cette adresse
    proc->regs.ebx = 0;
    proc->regs.ebp = 0;
    proc->regs.esi = 0;
    proc->regs.edi = 0;
}

int32_t creer_processus(void (*fonction)(void), char* nom) {

    if (pid_counter >= N_PROCESSUS) {
        printf("Erreur : nombre maximum de processus atteint.\n");
        return -1;
    }

    processus_t* proc = &processus[pid_counter];
    init_processus(proc, pid_counter, nom, fonction);

    // Ajouter le processus à la liste des activables
    ajouter_queue_activables(proc);

    pid_counter++;
    return proc->pid;
}


// Initialisation des processus
void init_processus_N(void) {
    char nom[20];

    // Initialiser les processus idle et les autres processus
    idle_process = (processus_t*) malloc(sizeof(processus_t));
    if (idle_process == NULL) {
        printf("Erreur d'allocation pour idle_process.\n");
        while (1);
    }

    init_processus(idle_process, 0, "idle", idle);

    for (uint32_t i = 1; i < N_PROCESSUS; i++) {
        processus_t* proc = (processus_t*) malloc(sizeof(processus_t));
        if (proc == NULL) {
            printf("Erreur d'allocation pour le processus %d.\n", i);
            while (1);
        }

        snprintf(nom, sizeof(nom), "proc%u", i);
        init_processus(proc, i, nom, processus_execution);

        // Ajouter le processus dans la liste des activables
        ajouter_queue_activables(proc);
    }

    // Définir idle_process comme processus actuel
    processus_actuel = idle_process;
    ajouter_queue_activables(idle_process);  // Ajout à la liste activable
}


// // Exécution des processus
// void processus_execution(void) {
//     for (;;) {
//         printf("[%s] pid = %i\n", mon_nom(), mon_pid());
//         ordonnance();
//     }
// }

// // Fonction idle
// void idle(void) {
//     for (;;) {
//         printf("[%s] pid = %i\n", mon_nom(), mon_pid());
//         ordonnance();
//     }
// }


int32_t mon_pid(void) {
    return (processus_actuel != NULL) ? processus_actuel->pid : -1;
}


char *mon_nom(void) {
    static char nom[16]; // Un buffer statique pour contenir le nom du processus
    if (processus_actuel != NULL) {
        if (processus_actuel->pid == 0) {
            return "idle";
        } else {
            snprintf(nom, sizeof(nom), "proc%d", processus_actuel->pid);
            return nom;
        }
    } else {
        printf("Erreur : processus_actuel est NULL\n");
        return "Inconnu";
    }
}

// ======================== ORDONNANCEMENT PREEMPTIF ===========================

//Fonction proc1,...,proc7
void processus_execution(void) {
    for (;;) {
        printf("[%s] pid = %i\n", mon_nom(), mon_pid());
        sti();
        hlt();
        cli();
    }
}

// Fonction idle
void idle(void){
    for (;;) {
        printf("[%s] pid = %i\n", mon_nom(), mon_pid());
        sti();
        hlt();
        cli();
    }
}

