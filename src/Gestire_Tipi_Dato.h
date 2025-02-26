/*
 * ============================================================================
 * Nome        : Gestire_Tipi_Dato.h
 * Autore      : Gruppo 3
 * Descrizione : Modulo per la gestione dei tipi di dato del programma.
 * ============================================================================
 */


#ifndef GESTIRE_TIPI_DATO_H_
#define GESTIRE_TIPI_DATO_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// -------------------- COSTANTI --------------------
#define NUMERO_MASSIMO_CONTATTI 50 				//Numero massimo di contatti che la rubrica supporta.
#define NUMERO_MINIMO_CONTATTI 0 				//Numero minimo di contatti affinchè la rubrica esista.
#define LUNGHEZZA_MASSIMA_STRINGA 20 			//Numero massimo di caratteri delle stringhe gestite (nominativo).
#define LUNGHEZZA_MINIMA_STRINGA 0				//Numero minimo di caratteri delle stringhe gestite (nominativo).
#define LUNGHEZZA_N_TELEFONO 10 				//Lunghezza costante del numero di telefono.
#define INIZIO_ALFABETO_ASCII 32 				//Carattere ' ', inizio dell'alfabeto consentito.
#define FINE_ALFABETO_ASCII 127 				//Carattere (?) fine dell'alfabeto consentito.
#define INIZIO_ALFABETO_NUMERI 48 				//Carattere '0', inizio dell'alfabeto utilizzato per i numeri telefonici.
#define FINE_ALFABETO_NUMERI 57 				//Carattere '9', fine dell'alfabeto utilizzato per i numeri telefonici.
#define STATO_PREFERITO 1 						//Indica lo stato del contatto salvato come preferito.
#define STATO_BLOCCATO 2 						//Indica lo stato del contatto salvato come bloccato.
#define STATO_PREDEFINITO 0 					//Indica lo stato predefinito di un contatto salvato.
#define CARATTERE_ERRATO_STRINGA '\n' 			//Codice di  per i caratteri di una stringa.
#define CODICE_ERRORE_LUNGHEZZA_STRINGA -1 		//Codice di errore: Lunghezza stringa non corretta.
#define CODICE_ERRORE_CONTATTI_RUBRICA -2 		//Codice di errore: Contatto non formattato propriamente.
#define CODICE_ERRORE_LUNGHEZZA_RUBRICA -3 		//Codice di errore: Numero di contatti presenti in rubrica fuori dai limiti.
#define CODICE_ERRORE_N_TELEFONO_CONTATTO -4 	//Codice di errore: Numero di telefono non formattato correttamente o lunghezza non rispettata.
#define CODICE_ERRORE_STATO_CONTATTO -5 		//Codice di errore: Lo stato del contatto non è fra uno di quelli previsti.
#define CODICE_ERRORE_NOMINATIVO_CONTATTO -6 	//Codice di errore: Il nominativo del contatto non rispetta il formato(alfabeto o lunghezza).
#define CODICE_ERRORE_DUPLICATO_RUBRICA -7 		//Codice di errore: Si sta tentando di inserire un contatto già esistente.
#define CODICE_ERRORE_CARATTERE_STRINGA -8 		//Codice di errore: Uno dei caratteri della stringa non è corretto.
#define CODICE_ERRORE_CONTATTO_NON_TROVATO -9 	//Codice di errore: Un contatto non è stato trovato in una fase di ricerca.
#define CODICE_ERRORE_ERRATO -10				//Codice di errore: E' stato impostato un valore errato al campo errore.
#define CODICE_ERRORE_FILE -11					//Codice di errore: Codice di errore nell’apertura del file.
#define CODICE_ERRORE_CRITERIO -12				//Codice di errore: Il criterio di ordinamento è errato.
#define CODICE_CORRETTO 0						//Indica uno stato in cui il programma sta funzionando correttamente.
#define ORDINAMENTO_CRESCENTE 1 				//Indica il criterio di ordinamento crescente dei contatti in rubrica.
#define ORDINAMENTO_DECRESCENTE 2 				//Indica il criterio di ordinamento decrescente dei contatti in rubrica.

// -------------------- RECORD STRINGA --------------------
typedef struct{
	int lunghezza_stringa; 								//Indica il numero di caratteri nella stringa.
	char caratteri_stringa[LUNGHEZZA_MASSIMA_STRINGA]; 	//Caratteri della stringa.
	int errore_stringa;									//Indica se la struttura dati presenta errori.
}Stringa;

// -------------------- RECORD CONTATTO --------------------
typedef struct{
	Stringa nominativo_contatto; 	//Nominativo del contatto in rubrica.
	Stringa n_telefono_contatto;	//Numero di telefono del contatto in rubrica.
	int stato_contatto; 			//Stato del contatto in rubrica.
	int errore_contatto;			//Indica se la struttura dati presenta errori.
}Contatto;

// -------------------- RECORD RUBRICA --------------------
typedef struct{
	Contatto contatti_rubrica[NUMERO_MASSIMO_CONTATTI]; //Contatti effettivi presenti in rubrica.
	int numero_contatti_rubrica; 						//Indica il numero di contatti nella rubrica.
	int errore_rubrica;									//Indica se la struttura dati presenta errori.
}Rubrica;

// -------------------- FUNZIONI PUBBLICHE DEL MODULO --------------------

//Funzioni Accesso Rubrica In quanto la struttura è condivisa con gli altri moduli.
int leggere_numero_contatti_rubrica( Rubrica rubrica );
void scrivere_numero_contatti_rubrica( Rubrica *rubrica, int numero_contatti );
void scrivere_contatto_rubrica( Rubrica *rubrica, int posizione, Contatto contatto );
int leggere_errore_rubrica ( Rubrica rubrica );
void scrivere_errore_rubrica ( Rubrica *rubrica, int errore );
void scrivere_contatto_rubrica( Rubrica *rubrica, int posizione, Contatto contatto );
Contatto leggere_contatto_rubrica( Rubrica rubrica, int posizione );

//Funzioni di accesso struttura dati Stringa.
int leggere_lunghezza_stringa( Stringa stringa );
void scrivere_lunghezza_stringa( Stringa *stringa, int lunghezza_stringa );
char leggere_carattere_stringa( Stringa stringa, int posizione );
void scrivere_carattere_stringa( Stringa *stringa, int posizione, char carattere_da_scrivere );
int leggere_errore_stringa ( Stringa stringa);
void scrivere_errore_stringa ( Stringa *stringa, int errore);

//Funzioni di accesso struttura dati Contatto.
int leggere_stato_contatto( Contatto contatto );
void scrivere_stato_contatto( Contatto *contatto, int stato );
Stringa leggere_nominativo_contatto( Contatto contatto );
void scrivere_nominativo_contatto( Contatto *contatto, Stringa nominativo );
Stringa leggere_n_telefono_contatto( Contatto contatto );
void scrivere_n_telefono_contatto( Contatto *contatto, Stringa n_telefono );
int leggere_errore_contatto ( Contatto contatto );
void scrivere_errore_contatto ( Contatto *contatto, int errore );

//Funzioni sulle strutture dati.
int controllare_correttezza_rubrica( Rubrica rubrica );
void copiare_contatto( Contatto *contatto_output, Contatto contatto_da_copiare );
int controllare_correttezza_contatto( Contatto contatto_da_controllare );
void inizializzare_contatto_rubrica( Contatto *contatto );
int controllare_correttezza_stringa( Stringa stringa );
Stringa convertire_stringa( char stringa[] );
int convertire_in_intero( char carattere );
bool verificare_uguaglianza_stringhe( Stringa stringa_uno, Stringa stringa_due);

#endif /* GESTIRE_TIPI_DATO_H_ */
