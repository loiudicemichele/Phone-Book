/*
 * ============================================================================
 * Nome        : Gestire_Archivio.c
 * Autore      : Gruppo 3
 * Descrizione : Modulo per la gestione dell'archivio.
 * ============================================================================
 */

#include "Gestire_Archivio.h"

//Funzione di esportazione dei contatti in rubrica.
int esportare_rubrica( Rubrica rubrica )
{
	FILE * file_archivio_rubrica; 	//File su cui esportare la rubrica.
	int errore; 					//Codice di controllo degli errori della rubrica.

	//Controllo che la rubrica da esportare sia corretta.
	errore = controllare_correttezza_rubrica( rubrica );
	if ( errore == CODICE_CORRETTO ){
		//Apertura del file.
		file_archivio_rubrica = fopen(PERCORSO_ARCHIVIO_RUBRICA, MODALITA_FILE_BINARIO_SCRITTURA);
		if ( file_archivio_rubrica == NULL ){
			//Se il file non dovesse esistere, allora segnaliamo l'errore tramite il valore di output della funzione.
			errore = CODICE_ERRORE_FILE;
		}else{
			//Se il file è corretto allora scrivo la rubrica sul file.
			fwrite( &rubrica, sizeof(Rubrica), 1, file_archivio_rubrica );
		}
		//Chiusura del file e salvataggio(nel caso del esista).
		fclose(file_archivio_rubrica);
	}
	return errore;
}

//Funzione di importazione dei contatti in rubrica.
void importare_rubrica( Rubrica *rubrica )
{
	FILE *file_archivio_rubrica; 	//File da cui importare la rubrica.
	int errore; 					//Codice di controllo degli errori della rubrica.
	//Apertura del file.
	file_archivio_rubrica = fopen(PERCORSO_ARCHIVIO_RUBRICA, MODALITA_FILE_BINARIO_LETTURA);
	//Controllo sull'esistenza del file.
	if( file_archivio_rubrica == NULL ){
		//Se il file non dovesse esistere, allora segnaliamo l'errore tramite il campo errore di rubrica.
		scrivere_errore_rubrica(rubrica, CODICE_ERRORE_FILE);
	}else{
		//Altrimenti leggiamo la rubrica e verifichiamo sia corretta.
	    fread(rubrica, sizeof(Rubrica), 1, file_archivio_rubrica );
	    errore = controllare_correttezza_rubrica( *rubrica );
	    //Se non lo fosse, essa avrebbe il campo errore, indicativo dell'errore nella rubrica.
	    scrivere_errore_rubrica( rubrica, errore );
	}
	//Chiudiamo il file dopo l'operazione.
	fclose(file_archivio_rubrica);
	return;
}
