/*
 * ============================================================================
 * Nome        : Impostazioni.h
 * Autore      : Gruppo 3
 * Descrizione : Modulo per la gestione delle impostazioni del programma.
 * ============================================================================
 */

#ifndef IMPOSTAZIONI_H_
#define IMPOSTAZIONI_H_

#include <unistd.h>
#include <windows.h>
#include "Gestire_Tipi_Dato.h"

#define MODALITA_FILE_TESTO_LETTURA "r"
#define LUNGHEZZA_MASSIMA_PERCORSO 512

// -------------------- VARIABILI GLOBALI PERCORSI --------------------
//Contine il percorso base alla cartella del progetto.
char PERCORSO_BASE[LUNGHEZZA_MASSIMA_PERCORSO];

//Percorsi relativi alle schermate di interfaccia utilizzate dall'utente.
char PERCORSO_ESITO_OPERAZIONE[LUNGHEZZA_MASSIMA_PERCORSO];
char PERCORSO_INTERFACCIA_MENU[LUNGHEZZA_MASSIMA_PERCORSO];
char PERCORSO_INTERFACCIA_MODIFICARE_CONTATTO[LUNGHEZZA_MASSIMA_PERCORSO];
char PERCORSO_INTERFACCIA_VISUALIZZARE_RUBRICA[LUNGHEZZA_MASSIMA_PERCORSO];
char PERCORSO_INTERFACCIA_INSERIRE_CONTATTO[LUNGHEZZA_MASSIMA_PERCORSO];
char PERCORSO_INTERFACCIA_RICERCARE_CONTATTO[LUNGHEZZA_MASSIMA_PERCORSO];
char PERCORSO_FILE_MESSAGGI[LUNGHEZZA_MASSIMA_PERCORSO];

//Percorsi relativi all'interfaccia della guida dell'utente.
char PERCORSO_GUIDA[LUNGHEZZA_MASSIMA_PERCORSO];
char PERCORSO_GUIDA_INSERIMENTO[LUNGHEZZA_MASSIMA_PERCORSO];
char PERCORSO_GUIDA_ELIMINARE[LUNGHEZZA_MASSIMA_PERCORSO];
char PERCORSO_GUIDA_RICERCARE[LUNGHEZZA_MASSIMA_PERCORSO];
char PERCORSO_GUIDA_ORDINARE[LUNGHEZZA_MASSIMA_PERCORSO];
char PERCORSO_GUIDA_VISUALIZZARE[LUNGHEZZA_MASSIMA_PERCORSO];
char PERCORSO_GUIDA_ESPORTARE[LUNGHEZZA_MASSIMA_PERCORSO];
char PERCORSO_GUIDA_IMPORTARE[LUNGHEZZA_MASSIMA_PERCORSO];
char PERCORSO_GUIDA_MODIFICARE[LUNGHEZZA_MASSIMA_PERCORSO];

//Percorso relativo al file archivio in cui memorizzare/leggere la rubrica.
char PERCORSO_ARCHIVIO_RUBRICA[LUNGHEZZA_MASSIMA_PERCORSO];

// -------------------- FUNZIONI PUBBLICHE --------------------
int controllare_configurazione_programma();
void imposta_la_cartella_di_esecuzione();
int configurare_programma();

#endif /* IMPOSTAZIONI_H_ */
