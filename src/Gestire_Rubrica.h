/*
 * ============================================================================
 * Nome        : Gestire_Rurbica.h
 * Autore      : Gruppo 3
 * Descrizione : Modulo per la gestione della rubrica del programma.
 * ============================================================================
 */

#ifndef GESTIRE_RUBRICA_H_
#define GESTIRE_RUBRICA_H_

#include "Gestire_Tipi_Dato.h"
#include <ctype.h>

// -------------------- FUNZIONI PUBBLICHE PER OPERARE SULLA RUBRICA ACCESSIBILI AL MODULO MENU' --------------------
void inserire_contatto_rubrica( Rubrica *rubrica, Contatto contatto );
void eliminare_contatto_rubrica( Rubrica *rubrica, int posizione );
void modificare_contatto_rubrica( Rubrica *rubrica, Contatto contatto_precedente, Contatto contatto_modificato );
void ordinare_contatti_rubrica( Rubrica *rubrica, int criterio );
int cercare_contatto_rubrica( Rubrica rubrica, Contatto contatto );

#endif /* GESTIRE_RUBRICA_H_ */
