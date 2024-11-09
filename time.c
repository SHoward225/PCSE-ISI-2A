#include "ecran.h"
#include "cpu.h"

// Variables globales pour stocker le temps écoulé
static uint32_t heures = 0;
static uint32_t minutes = 0;
static uint32_t secondes = 0;

// Fonction appelée à chaque interruption générée par le PIT
void tic_PIT(void) {

    // Envoyer un End Of Interrupt (EOI) au PIC pour signaler la fin de l'interruption
    outb(0x20, 0x20);

    static uint32_t compteur = 0;  // Compte le nombre d'interruptions

    // printf(" Appel tic PIT %i... \n", compteur);
    compteur++;  // Incrémente à chaque appel (chaque interruption)
    
    // Si le compteur atteint 50 (soit 50 interruptions à 50 Hz), on incrémente le temps
    if (compteur >= 50) {
        compteur = 0;  // Réinitialise le compteur
        secondes++;  // Incrémente les secondes

        // Gère le passage à la minute suivante
        if (secondes >= 60) {
            secondes = 0;
            minutes++;
            // Gère le passage à l'heure suivante
            if (minutes >= 60) {
                minutes = 0;
                heures++;
            }
        }

        // Formate le temps sous la forme HH:MM:SS
        char temps[9];  // "HH:MM:SS" = 8 caractères + 1 pour le '\0'
        snprintf(temps, 9, "%02u:%02u:%02u", heures, minutes, secondes);

        // Affiche le temps à une position fixe sur l'écran
        ecrit_temps(temps, 8);  // Appelle la fonction pour afficher le temps
    }
}

