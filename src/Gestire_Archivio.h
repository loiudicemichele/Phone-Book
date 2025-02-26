/*
 * ============================================================================
 * Nome        : Gestire_Archivio.h
 * Autore      : Gruppo 3
 * Descrizione : Modulo per la gestione dell'archivio.
 * ============================================================================
 */

#ifndef GESTIRE_ARCHIVIO_C_
#define GESTIRE_ARCHIVIO_C_

#include "Impostazioni.h"
// -------------------- COSTANTI PER LA MODALITA' DI APERTURA DEL FILE --------------------
#define MODALITA_FILE_BINARIO_LETTURA "rb"		//Modalità di apertura di un file binario in scrittura.
#define MODALITA_FILE_BINARIO_SCRITTURA "wb"	//Modalità di apertura di un file binario in lettura.

// -------------------- FUNZIONI PUBBLICHE PER OPERARE SULL'ARCHIVIO --------------------
int esportare_rubrica( Rubrica rubrica );
void importare_rubrica( Rubrica *rubrica );

#endif /* GESTIRE_ARCHIVIO_C_ */
