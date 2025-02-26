/*
 * ============================================================================
 * Nome        : Gestire_Interfaccia_Utente.h
 * Autore      : Gruppo 3
 * Descrizione : Modulo per la gestione dell'interfaccia utente.
 * ============================================================================
 */
#ifndef GESTIRE_INTERFACCIA_UTENTE_H_
#define GESTIRE_INTERFACCIA_UTENTE_H_

#include "Gestire_Rubrica.h"
#include "Gestire_Archivio.h"
#include "Impostazioni.h"
// ----------------------- COSTANTI PER LA GESTIONE DELLO SCHERMO ----------------------
#define ORIGINE_SCHERMO 0						//Coordinate di origine dello schermo (0,0).
#define RIGHE_MASSIME_SCHERMO 25				//Ordinata massima raggiungibile dal cursore.
#define COLONNE_MASSIME_SCHERMO 80				//Ascissa massima raggiungibile dal cursore.
#define RIGA_INPUT_UTENTE 23					//Ascissa su cui richiedere l'input utente.
#define COLONNA_INPUT_UTENTE 49					//Ordinata su cui richiedere l'input utente.
#define RIGA_TESTO 9							//Ascissa su cui stampare il messaggio utente.
#define COLONNA_TESTO 2							//Ordinata su cui stampare il messaggio utente.
#define RIGA_NOMINATIVO_INSERIMENTO 10			//Ascissa di base per la stampa di un nominativo di un contatto.
#define RIGA_N_TELEFONO_INSERIMENTO 12			//Ascissa di base per la stampa di un numero telefono di un contatto.
#define RIGA_STATO_INSERIMENTO 20				//Ascissa di base per la stampa dello stato di un contatto.
#define RIGA_VISUALIZZARE_CONTATTO 6			//Ascissa di base in cui stampare un contatto.
#define COLONNA_VISUALIZZARE_NOMINATIVO 2		//Ordinata di base per la stampa di un nominativo di un contatto.
#define COLONNA_VISUALIZZARE_N_TELEFONO 33		//Ordinata di base per la stampa di un numero telefono di un contatto.
#define COLONNA_VISUALIZZARE_STATO 60			//Ordinata di base per la stampa dello stato di un contatto.
#define COLONNA_FINE_NOMINATIVO 25				//Ordinata di base per la fine del campo di stampa di un nominativo di un contatto.
#define COLONNA_FINE_N_TELEFONO 51				//Ordinata di base per la fine del campo di stampa la stampa di un numero telefono di un contatto.
#define COLONNA_FINE_STATO 78					//Ordinata di base per la fine del campo di stampa la stampa dello stato di un contatto.
#define CARATTERE_PULIZIA_SCHERMO ' '			//Carattere per pulire lo schermo di output.

// -------------------- COSTANTI PER LA GESTIONE DELL'INPUT UTENTE --------------------
#define CARATTERE_USCITA 'e'					//Carattere di uscita dall'operazione.
#define CARATTERE_SALVATAGGIO_ED_USCITA 's'		//Carattere del salvataggio dall'operazione.
#define CARATTERE_CONTINUA 'c'					//Carattere per continuare operazione.
#define SCELTA_INSERIRE_CONTATTO '1'			//Scelta dell'utente di un operazione riguardante l'inserimento di un contatto.
#define SCELTA_ELIMINARE_CONTATTO '2'			//Scelta dell'utente di un operazione riguardante l'eliminazione di un contatto.
#define SCELTA_RICERCARE_CONTATTO '3'			//Scelta dell'utente di un operazione riguardante la ricerca di un contatto.
#define SCELTA_ORDINARE_RUBRICA '4'				//Scelta dell'utente di un operazione riguardante l'ordinamento della rubrica.
#define SCELTA_VISUALIZZARE_RUBRICA '5'			//Scelta dell'utente di un operazione riguardante la visualizzazione della rubrica.
#define SCELTA_ESPORTARE_RUBRICA '6'			//Scelta dell'utente di un operazione riguardante l'esportazione della rubrica.
#define SCELTA_IMPORTARE_RUBRICA '7'			//Scelta dell'utente di un operazione riguardante l'importazione della rubrica.
#define SCELTA_MODIFICARE_CONTATTO '8'			//Scelta dell'utente di un operazione riguardante la modifica di un contatto.
#define SCELTA_VISUALIZZARE_MANUALE_UTENTE '9'	//Scelta dell'utente di un operazione riguardante la visualizzazione del manuale utente.
#define SCELTA_INSERIRE_NOMINATIVO '1'			//Scelta dell'utente della modifica del nominativo del contatto.
#define SCELTA_INSERIRE_N_TELEFONO '2'			//Scelta dell'utente della modifica del numero di telefono del contatto.
#define SCELTA_INSERIRE_STATO '3'				//Scelta dell'utente della modifica dello stato di un contatto.

// -------------------- COSTANTI PER LA LOGICA DI VISUALIZZAZIONE RUBRICA --------------------
#define CONTATTI_PER_PAGINA 15					//Numero massi di contatti stampabili in una singola pagina del programma.
#define PAGINA_INIZIALE 1						//Prima pagina selezionabile dall'utente.
#define PAGINA_AVANTI 'a'  						//Carattere per scorrere in avanti le pagine.
#define PAGINA_INDIETRO 'i'						//Carattere per scorrere in indietro le pagine.
#define CONVERSIONE_CODICE_MESSAGGIO -1			//Paramentro di conversione del codice del messaggio nella riga su file corrispondente.

// -------------------- COSTANTI PER I MESSAGGI UTENTI, RIFERITE ALLA RIGA DEL FILE MESSAGGI  --------------------
#define MESSAGGIO_RUBRICA_ESPORTATA -13			//Messaggio riferito alla buona riuscita dell'operazione di esportazione della rubrica.
#define MESSAGGIO_RUBRICA_NON_ESPORTATA -14		//Messaggio errore riferito all'operazione di esportazione della rubrica.
#define MESSAGGIO_RUBRICA_IMPORTATA -15			//Messaggio riferito alla buona riuscita dell'operazione di importazione della rubrica.
#define MESSAGGIO_RUBRICA_NON_IMPORTATA -16		//Messaggio errore riferito all'operazione di importazione della rubrica.
#define MESSAGGIO_CONTATTO_ELIMINATO -17		//Messaggio riferito all'operazione di eliminazione di un contatto.
#define MESSAGGIO_ORDINAMENTO_EFFETTUATO -18	//Messaggio riferito all'operazione di ordinamento della rubrica.
#define MESSAGGIO_RUBRICA_VUOTA -19				//Messaggio di errore, l'operazione non è andata a buon fine poichè la rubrica è vuota.
#define MESSAGGIO_MODIFICA_CORRETTA -20			//Messaggio riferito all'operazione di modifica di un contatto andata a buon fine.
#define MESSAGGIO_ERRORE_GENERICO -21 			//Messaggio riferito a qualche errore generico avvenuto nella stampa.
#define MESSAGGIO_STATO_PREDEFINITO -22			//Messaggio relativo allo stato predefinito dell'utente.
#define MESSAGGIO_STATO_PREFERITO -23			//Messaggio relativo allo stato preferito dell'utente.
#define MESSAGGIO_STATO_BLOCCATO -24			//Messaggio relativo allo stato bloccato dell'utente.
#define MESSAGGIO_CONTINUA -25					//Messaggio per continuare l'esecuzione del programma.
#define MESSAGGIO_SALVA_CONTINUA_1	-26			//Messaggio che appare dopo la stampa di errore e consente
#define MESSAGGIO_SALVA_CONTINUA_2	-27			//all'utente di continuare con l'operazione o salvare e uscire.
#define MESSAGGIO_CONTINUA_ESCI -28				//Messaggio utente per uscire o continuare con l'operazione.
#define MESSAGGIO_AVANTI_INDIETRO -29			//Messaggio per scorrere la visualizzazione dei contatti a schermo.
#define MESSAGGIO_USCITA -30					//Messaggio per uscire dall'operazione che si sta effettuando.
#define MESSAGGIO_RISPOSTA -31					//Messaggio di attesa di una risposta da parte dell'utente.
#define MESSAGGIO_SCELTA_CRITERIO -32			//Messaggio per selezionare il criterio di visualizzazione.
#define MESSAGGIO_CONFERMA_ELIMINAZIONE -33		//Messaggio di richiesta onferma per eliminare un contatto.
#define MESSAGGIO_SCELTA_ORDINAMENTO -34		//Messaggio per selezionare il criterio di ordinamento.
#define MESSAGGIO_SCELTA_MODIFICA -35			//Messaggio di scelta campo contatto da modificare.
#define MESSAGGIO_SCELTA_NOMINATIVO -36 		//Messaggio di scelta del campo del nominativo da modificare.
#define MESSAGGIO_SCELTA_N_TELEFONO -37 		//Messaggio di scelta del campo del numero di telefono da modificare.
#define MESSAGGIO_SCELTA_STATO -38 				//Messaggio di scelta del campo dello stato da modificare.
#define MESSAGGIO_CONTATTO_SALVATO -39			//Messaggio di corretto salvataggio del contatto inserito.

// -------------------- COSTANTI PER LA GESTIONE DELL'OUTPUT UTENTE --------------------
#define CARATTERE_APERTURA_STAMPA '['			//Segnala l'inizio della stampa di un contatto a schermo.
#define CARATTERE_CHIUSURA_STAMPA ']'			//Segnala la fine della stampa di un contatto a schermo.

// Funzioni gestione interfaccia
void mostrare_menu();
void impostare_dimensione_schermo();

#endif /* GESTIRE_INTERFACCIA_UTENTE_H_ */
