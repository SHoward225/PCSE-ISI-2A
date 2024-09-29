//************** IMPORT LIBRARY **************

#include <stdio.h> 
#include "ecran.h"
#include "cpu.h"  // Cette bibliothèque inclut les fonctions inb et outb
#include <inttypes.h>
#include <string.h> // pour memmove


// ************** CONSTANT DEFINITION **************

static uint32_t position_colonne =0 ;
static uint32_t position_ligne =0 ;


// ************** CODE IMPLEMENTATION **************

/*
 * Cette fonction renvoie un pointeur sur la case memoire 
 * correspondante aux cordonnées fournies
 */

uint16_t *ptr_mem(uint32_t lig, uint32_t col ){
    return (uint16_t*) (MEMOIRE_VIDEO_BASE + 2 * (lig * COL_MAX + col));
}

/*
 * Ecrit le caractere c aux coordonnées specifiées 
 * Ajout : paramettre pour preciser couleur du caractere, celle de fond et bit de clignotement
 */

void ecrit_car(uint32_t lig, uint32_t col, char c,  uint32_t couleur_caractere, uint32_t couleur_fond, uint32_t clignotement){

    uint16_t *adresse_memoire = ptr_mem(lig, col); //adresse memoire du curseur
    uint16_t valeur = (uint16_t) c 
                    | couleur_caractere << 8 
                    | couleur_fond << 12
                    | clignotement  << 15; //valeur du caractère à afficher
    *adresse_memoire = valeur;
}



/*
 * Parcours les lignes er colonnes de l'ecran pour ecrire dans chaque case un espace blanc sur un fond noir
 * afin d'initialiser les formats dans la memoire
 */
void efface_ecran(void){
    for (uint32_t i = 0; i < LIG_MAX; i++)
    {
        for (uint32_t j = 0; j < COL_MAX; j++)
        {
            ecrit_car(i, j,' ', 0, 0, 0);
        }
    }
}

/*
 * Place le curseur a la position donnée 
 */

void place_curseur(uint32_t lig, uint32_t col) {
    uint16_t pos = lig * COL_MAX + col;
    outb(0x0F, COMMAND_PORT);  // Envoi de la commande pour la partie basse
    outb((uint8_t)(pos & 0xFF), DATA_PORT);
    outb(0x0E, COMMAND_PORT);  // Envoi de la commande pour la partie haute
    outb((uint8_t)((pos >> 8) & 0xFF), DATA_PORT);
}


/*
 * Traite un caractere donné (affiche si c'est un caractere normal ou 
 * implemante l'effet voulu si c'est un caractere de controle) 
 */
void traite_car(char c){
    switch (c)
    {
        //Recule curseur
        case '\b':  // Backspace
            if (position_colonne != 0) position_colonne--;
            break;

        //Avance a la prochaine tabulation
        case '\t':  // Tabulation
            position_colonne = (position_colonne + 8) & ~(8 - 1);
            break;

        case '\n':  // Nouvelle ligne
            position_ligne++;
            position_colonne = 0;  // Retour à la première colonne
            break;

        //Efface ecran et place curseur en (0;0)
        case '\f':
            efface_ecran();
            position_colonne = 0;
            position_ligne = 0;
            break;

        //Deplace curseur sur la ligne actuelle et col=0
        case '\r':
            position_colonne = 0;
            break;

        //Par defaut
        default:
            if (c >= 32 && c <= 126) {
                ecrit_car(position_ligne, position_colonne, c, BLANC, NOIR, 5);
                position_colonne++;
            }
            break;
    }

    if (position_ligne >= LIG_MAX) {
        defilement();
        position_ligne = LIG_MAX - 1;
    }

    place_curseur(position_ligne, position_colonne);


}

/*
 * Remonte d'une ligne l'affichage de l'ecran lorsque celui ci est rempli
 * (Judicieux d'tiliser memmove definie dans string.h)
 */
void defilement(void){
    memmove((void*)MEMOIRE_VIDEO_BASE, 
            (void*)(MEMOIRE_VIDEO_BASE + 2 * COL_MAX), 
            2 * COL_MAX * (LIG_MAX - 1)); // Utilisation de memmove pour déplacer tout le contenu de l'écran d'une ligne vers le haut

    for (int col = 0; col < COL_MAX; col++) {
        ecrit_car(LIG_MAX - 1, col, ' ', BLANC, NOIR, 0); // Efface la dernière ligne (ligne 24) en la remplissant d'espaces
    }
}



/*
 * Solution finale : Utilise les fonctions precedentes
 */
void console_putbytes(const char *s, int len){
    for (int i = 0; i < len; i++) {
        traite_car(s[i]);
    }
}

// Cette fonction pourrait être utilisée pour la mise en place initiale et les tests
void init_screen() {
    efface_ecran();
    place_curseur(0, 0);
}
