/*
 * ============================================================================
 * Nome        : Impostazioni.c
 * Autore      : Gruppo 3
 * Descrizione : Modulo per la gestione delle impostazioni del programma.
 * ============================================================================
 */

#include "Impostazioni.h"
//Percorso dei file interfaccia
/*
 * Imposta la cartella di lavoro forzatamente affinchè possano essere trovati i file di cui il programma ha bisogno.
 * Configura la variabile di ambiente del percorso PERCORSO_BASE.
 */
void imposta_la_cartella_di_esecuzione()
{
    //MAX_PATH Costante della libreria lib.h indica il percoso massimo che il file può avere.
	char percorso_letto[LUNGHEZZA_MASSIMA_PERCORSO];
	//Acquisisco il percorso del file in cui si trova l'eseguibile del programma.
    if (GetModuleFileName(NULL, percorso_letto, LUNGHEZZA_MASSIMA_PERCORSO) == 0) {
        perror("GetModuleFileName");
        return;
    }
    //Rimuovo il nome del file exe dal programma.
    char *nuovo_percorso = strrchr(percorso_letto, '\\');
	if (nuovo_percorso != NULL) {
		*nuovo_percorso = '\0';
	}
	//Rimuovo l'ultima directory dal programma./Debug
	nuovo_percorso = strrchr(percorso_letto, '\\');
	if (nuovo_percorso != NULL) {
		*nuovo_percorso = '\0';
	}
	//Configuro la cartella default ./files
	strcat(percorso_letto, "\\files\\");
	strcpy(PERCORSO_BASE,percorso_letto);
	//Imposto la directory del programma forzatamente a quella costruita precedentemente.
    if (!SetCurrentDirectory(percorso_letto)) {
        perror("SetCurrentDirectory");
    }
}

//Imposta tutti i percorsi dei file utilizzati nel programma.
void configura_percorsi_file()
{
	/*
	 * Imposto il percorso base per tutte le variabili di percorso, che corrisponderà a:
	 * C:/<percorso_computer>/Rubrica/files/
	 */
	strcpy(PERCORSO_ESITO_OPERAZIONE, PERCORSO_BASE);
	strcpy(PERCORSO_INTERFACCIA_MENU, PERCORSO_BASE);
	strcpy(PERCORSO_INTERFACCIA_MODIFICARE_CONTATTO, PERCORSO_BASE);
	strcpy(PERCORSO_INTERFACCIA_VISUALIZZARE_RUBRICA, PERCORSO_BASE);
	strcpy(PERCORSO_INTERFACCIA_INSERIRE_CONTATTO, PERCORSO_BASE);
	strcpy(PERCORSO_INTERFACCIA_RICERCARE_CONTATTO, PERCORSO_BASE);
	strcpy(PERCORSO_FILE_MESSAGGI, PERCORSO_BASE);

	strcpy(PERCORSO_GUIDA, PERCORSO_BASE);
	strcpy(PERCORSO_GUIDA_INSERIMENTO, PERCORSO_BASE);
	strcpy(PERCORSO_GUIDA_ELIMINARE, PERCORSO_BASE);
	strcpy(PERCORSO_GUIDA_RICERCARE, PERCORSO_BASE);
	strcpy(PERCORSO_GUIDA_ORDINARE, PERCORSO_BASE);
	strcpy(PERCORSO_GUIDA_VISUALIZZARE, PERCORSO_BASE);
	strcpy(PERCORSO_GUIDA_ESPORTARE, PERCORSO_BASE);
	strcpy(PERCORSO_GUIDA_IMPORTARE, PERCORSO_BASE);
	strcpy(PERCORSO_GUIDA_MODIFICARE, PERCORSO_BASE);

	strcpy(PERCORSO_ARCHIVIO_RUBRICA, PERCORSO_BASE);
	/*
	 * Aggiungo il file corrispondente al path configurato in precedenza, ottenendo:
	 * C:/<percorso_computer>/Rubrica/files/<nomefile>.txt
	 */
	strcat(PERCORSO_ESITO_OPERAZIONE, "\\layout_esito_operazione.txt");
	strcat(PERCORSO_INTERFACCIA_MENU, "\\layout_interfaccia_menu.txt");
	strcat(PERCORSO_INTERFACCIA_MODIFICARE_CONTATTO, "\\layout_interfaccia_modificare_contatto.txt");
	strcat(PERCORSO_INTERFACCIA_VISUALIZZARE_RUBRICA, "\\layout_interfaccia_visualizzare.txt");
	strcat(PERCORSO_INTERFACCIA_INSERIRE_CONTATTO, "\\layout_interfaccia_inserire_contatto.txt");
	strcat(PERCORSO_INTERFACCIA_RICERCARE_CONTATTO, "\\layout_interfaccia_ricercare_contatto.txt");
	strcat(PERCORSO_FILE_MESSAGGI, "\\messaggi_utente.txt");

	strcat(PERCORSO_GUIDA, "\\layout_manuale_utente\\guida.txt");
	strcat(PERCORSO_GUIDA_INSERIMENTO, "\\layout_manuale_utente\\1_guida_inserimento.txt");
	strcat(PERCORSO_GUIDA_ELIMINARE, "\\layout_manuale_utente\\2_guida_eliminare.txt");
	strcat(PERCORSO_GUIDA_RICERCARE, "\\layout_manuale_utente\\3_guida_ricercare.txt");
	strcat(PERCORSO_GUIDA_ORDINARE, "\\layout_manuale_utente\\4_guida_ordinare.txt");
	strcat(PERCORSO_GUIDA_VISUALIZZARE, "\\layout_manuale_utente\\5_guida_visualizzare.txt");
	strcat(PERCORSO_GUIDA_ESPORTARE, "\\layout_manuale_utente\\6_guida_esportare.txt");
	strcat(PERCORSO_GUIDA_IMPORTARE, "\\layout_manuale_utente\\7_guida_importare.txt");
	strcat(PERCORSO_GUIDA_MODIFICARE, "\\layout_manuale_utente\\8_guida_modificare.txt");
	strcat(PERCORSO_ARCHIVIO_RUBRICA, "archivio_rubrica.bin");
	return;
}

//Controlla che il programma possa aprire tutti i percorsi configurati e che nessun file risulti mancante.
int configurare_programma()
{
	int errore; //Variabile ausiliaria per individuare l'errore

	//Configuro i percorsi prima del controllo.
	configura_percorsi_file();
	errore = CODICE_CORRETTO;
	//Variabili di supporto per i file da controllare.
	FILE *file_layout_esito_operazione;
	FILE *file_layout_menu;
	FILE *file_layout_modificare_contatto;
	FILE *file_layout_visualizzare_rubrica;
	FILE *file_layout_inserire_contatto;
	FILE *file_layout_ricercare_contatto;
	FILE *file_messaggi;

	FILE *file_layout_guida;
	FILE *file_layout_guida_inserimento;
	FILE *file_layout_guida_eliminare;
	FILE *file_layout_guida_ricercare;
	FILE *file_layout_guida_ordinare;
	FILE *file_layout_guida_visualizzare;
	FILE *file_layout_guida_esportare;
	FILE *file_layout_guida_importare;
	FILE *file_layout_guida_modificare;

	//Apertura di tutti i file in modalità lettura.
	file_layout_esito_operazione = fopen(PERCORSO_ESITO_OPERAZIONE, MODALITA_FILE_TESTO_LETTURA);
	file_layout_menu = fopen(PERCORSO_INTERFACCIA_MENU, MODALITA_FILE_TESTO_LETTURA);
	file_layout_modificare_contatto = fopen(PERCORSO_INTERFACCIA_MODIFICARE_CONTATTO, MODALITA_FILE_TESTO_LETTURA);
	file_layout_visualizzare_rubrica = fopen(PERCORSO_INTERFACCIA_VISUALIZZARE_RUBRICA, MODALITA_FILE_TESTO_LETTURA);
	file_layout_inserire_contatto = fopen(PERCORSO_INTERFACCIA_INSERIRE_CONTATTO, MODALITA_FILE_TESTO_LETTURA);
	file_layout_ricercare_contatto = fopen(PERCORSO_INTERFACCIA_RICERCARE_CONTATTO, MODALITA_FILE_TESTO_LETTURA);
	file_messaggi = fopen(PERCORSO_FILE_MESSAGGI, MODALITA_FILE_TESTO_LETTURA);

	file_layout_guida = fopen(PERCORSO_GUIDA, MODALITA_FILE_TESTO_LETTURA);
	file_layout_guida_inserimento = fopen(PERCORSO_GUIDA_INSERIMENTO, MODALITA_FILE_TESTO_LETTURA);
	file_layout_guida_eliminare = fopen(PERCORSO_GUIDA_ELIMINARE, MODALITA_FILE_TESTO_LETTURA);
	file_layout_guida_ricercare = fopen(PERCORSO_GUIDA_RICERCARE, MODALITA_FILE_TESTO_LETTURA);
	file_layout_guida_ordinare = fopen(PERCORSO_GUIDA_ORDINARE, MODALITA_FILE_TESTO_LETTURA);
	file_layout_guida_visualizzare = fopen(PERCORSO_GUIDA_VISUALIZZARE, MODALITA_FILE_TESTO_LETTURA);
	file_layout_guida_esportare = fopen(PERCORSO_GUIDA_ESPORTARE, MODALITA_FILE_TESTO_LETTURA);
	file_layout_guida_importare = fopen(PERCORSO_GUIDA_IMPORTARE, MODALITA_FILE_TESTO_LETTURA);
	file_layout_guida_modificare = fopen(PERCORSO_GUIDA_MODIFICARE, MODALITA_FILE_TESTO_LETTURA);

	/*
	 * Controllo sull'apertura dei file:
	 * Se anche un solo file risulta mancante, o il programma non può accedere a tale file,
	 * questo controllo assegnerà alla variabile errore il codice di CODICE_ERRORE_FILE.
	 */
	if( file_layout_esito_operazione != NULL &&
		file_layout_menu != NULL &&
		file_layout_modificare_contatto != NULL &&
		file_layout_visualizzare_rubrica != NULL &&
		file_layout_inserire_contatto != NULL &&
		file_layout_ricercare_contatto != NULL &&
		file_messaggi != NULL &&
		file_layout_guida != NULL &&
		file_layout_guida_inserimento != NULL &&
		file_layout_guida_eliminare != NULL &&
		file_layout_guida_ricercare != NULL &&
		file_layout_guida_ordinare != NULL &&
		file_layout_guida_visualizzare != NULL &&
		file_layout_guida_esportare != NULL &&
		file_layout_guida_importare != NULL &&
		file_layout_guida_modificare != NULL ){
		errore = CODICE_CORRETTO;
	} else{
		errore = CODICE_ERRORE_FILE;
	}

	//Chiusura di tutti i file.
	fclose(file_layout_esito_operazione);
	fclose(file_layout_menu);
	fclose(file_layout_modificare_contatto);
	fclose(file_layout_visualizzare_rubrica);
	fclose(file_layout_inserire_contatto);
	fclose(file_layout_ricercare_contatto);
	fclose(file_messaggi);

	fclose(file_layout_guida);
	fclose(file_layout_guida_inserimento);
	fclose(file_layout_guida_eliminare);
	fclose(file_layout_guida_ricercare);
	fclose(file_layout_guida_ordinare);
	fclose(file_layout_guida_visualizzare);
	fclose(file_layout_guida_esportare);
	fclose(file_layout_guida_importare);
	fclose(file_layout_guida_modificare);
	return errore;
}

