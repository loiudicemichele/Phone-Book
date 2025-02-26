/*
 * ============================================================================
 * Nome        : Gestire_Interfaccia_Utente.c
 * Autore      : Gruppo 3
 * Descrizione : Modulo per la gestione dell'interfaccia utente.
 * ============================================================================
 */

#include "Gestire_Interfaccia_Utente.h"

//Sposta il cursore della console in una posizione fornita in input alla funzione.
void spostare_cursore(int y, int x)
{
	//Acquisisco le coordinate.
    COORD CursorPos = { x, y };
    //Richiamo il componente di gestione della console.
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    //Imposto le coordinate fornite in input alla funzione, in modo da spostare il cursore sullo schermo.
    SetConsoleCursorPosition(hConsole, CursorPos);
    return;
}

/*
 * Imposta la dimensione dello schermo con le costanti di schermo
 * definite in precedenza e non permette di modificare tale schermata.
 */
void impostare_dimensione_schermo()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // Imposta la dimensione della console.
    COORD dimensione; //Dimensione fissa della console.
    dimensione.X = COLONNE_MASSIME_SCHERMO;
    dimensione.Y = RIGHE_MASSIME_SCHERMO;
    SetConsoleScreenBufferSize(hConsole, dimensione);
    // Imposta la dimensione della finestra della console.
    SMALL_RECT margini_console;
    margini_console.Left = 0;
    margini_console.Top = 0;
    margini_console.Right = COLONNE_MASSIME_SCHERMO - 1;
    margini_console.Bottom = RIGHE_MASSIME_SCHERMO - 1;
    SetConsoleWindowInfo(hConsole, TRUE, &margini_console);
    // Disabilita la possibilità di ridimensionare la finestra.
    HWND hwnd = GetConsoleWindow();
    LONG style = GetWindowLong(hwnd, GWL_STYLE);
    style &= ~(WS_MAXIMIZEBOX | WS_SIZEBOX);
    SetWindowLong(hwnd, GWL_STYLE, style);
    //Imposta i parametri alla finestra.
    SetWindowPos( hwnd, NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED );
}

/*
 * Pulisce il buffer del sistema, cancellando tutti i caratteri rimasti,
 * evita il bug dell'acquisizione del carattere "\n" o " ".
 */
void pulire_buffer_input()
{
	char carattere;
	while ((carattere = getchar()) != '\n' && carattere != EOF);
}

//Pulisce la schermata della console; fornite le coordinate degli estremi della sezione di schermo da cancellare.
void pulire_schermata(int riga_inizio, int colonna_inizio, int riga_fine, int colonna_fine)
{
    int i; //Indice di riga.
    int j; //Indice di colonna.
	i = riga_inizio;
	/*
	 * Per ogni riga e per ogni colonna sposto il cursore sulla posizione scandita,
	 * e cancello l'elemento sovrascrivendolo con il "carattere vuoto".
	 */
    while (i <= riga_fine) {
        j = colonna_inizio;
        while (j <= colonna_fine) {
        	spostare_cursore(i, j);
            printf("%c" , CARATTERE_PULIZIA_SCHERMO);
            j = j + 1;
        }
        i = i + 1;
    }
    //Riporto il cursore nelal posizione originale.
    spostare_cursore(ORIGINE_SCHERMO, ORIGINE_SCHERMO);
    return;
}

//Stampa l'interfaccia recuperata dal percorso del file fornito in input.
void stampare_layout_interfaccia(char* percorso_file)
{
    /*
     * Cambiamo la codifica di interpretazione dei caratteri letti da file per migliorare l'estetica del programma,
     * utilizzando caratteri per il layout presenti nell'alfabeto ASCII esteso.
     */
	#ifdef _WIN32
    system("chcp 65001 > nul");
    #endif
    FILE *file;	//File da a cui accedere per recuperare il contenuto dell'interfaccia.
    //Puliamo l'intero schermata prima di proseguire.
    pulire_schermata(ORIGINE_SCHERMO, ORIGINE_SCHERMO, RIGHE_MASSIME_SCHERMO - 1, COLONNE_MASSIME_SCHERMO - 1);
    //Accediamo al file di interfaccia specificato.
    file = fopen(percorso_file, MODALITA_FILE_TESTO_LETTURA);
    //Ci assicuriamo che tale file esista.
    if (file == NULL) {
    	/*
    	 * Necessitiamo di una stampa diretta poichè non è stato trovato il file dal layout, e quindi tale errore non può
    	 * essere stampato tramite il file di messaggi utente (che potrebbe non essere stato trovato).
    	 */
    	printf("Nessun file di layout è stato trovato! Prova a cambiare il percorso!");
    } else {
        char riga_letta[LUNGHEZZA_MASSIMA_PERCORSO];  //Riga letta dal file.
        while (fgets(riga_letta, sizeof(riga_letta), file) != NULL) {
            printf("%s", riga_letta);
        }
        fclose(file);  //Chiudo il file.
    }
    //Riporto il cursore nella posizione originale.
    spostare_cursore(ORIGINE_SCHERMO,ORIGINE_SCHERMO);
    return;
}

//Funzione per stampare a schermo un messaggio preso da file, fornito in input il codice di tale messaggio.
void stampare_a_schermo_messaggio(int codice)
{
	FILE *file;										//File a cui accedere per la lettura del messaggio.
	int i;											//Per scandire la riga associata al codice in input.
	char stringa_letta[COLONNE_MASSIME_SCHERMO];	//Variabile contenente il messaggio letto.

	//Apro il file contenente i messaggi.
	file = fopen( PERCORSO_FILE_MESSAGGI, MODALITA_FILE_TESTO_LETTURA );
	i = 0;
	//Scandisco le righe fino ad arrivare a quella desiderata.
	while( i <= ( codice * CONVERSIONE_CODICE_MESSAGGIO ) ){
		fgets(stringa_letta, sizeof(stringa_letta), file);
		i = i + 1;
	}
	//Stampo la stringa corrispondente al codice in ingresso.
	printf("%s",stringa_letta);
	//Chiudo il file.
	fclose(file);
}

//Funzione per stampare una Stringa.
void stampare_stringa( Stringa stringa )
{
	int i;	//Scandisce le posizioni della stringa.
	//Verifico che la stringa sia corretta.
	if ( controllare_correttezza_stringa(stringa) == CODICE_CORRETTO ){
		i = 0;
		printf("%c", CARATTERE_APERTURA_STAMPA);
		//Scandisco ogni elemento della stringa, stampando carattere per carattere.
		while( i < leggere_lunghezza_stringa(stringa) ){
			printf("%c", leggere_carattere_stringa(stringa,i));
			i = i + 1;
		}
		printf( "%c" , CARATTERE_CHIUSURA_STAMPA );
	} else{
		//Se la stringa non dovesse essere corretta, stampo un messaggio di errore.
		stampare_a_schermo_messaggio( MESSAGGIO_ERRORE_GENERICO );
	}
	return;
}

/*
 * Funzione per stampare un Contatto a schermo.
 * Tale funzione acquisisce un contatto e la riga su cui stamparlo.
 */
void stampare_contatto( Contatto contatto, int riga )
{
	if ( controllare_correttezza_contatto(contatto) == CODICE_CORRETTO ){
		//Posiziono il cursore sulla riga fornita in input e sulla colonna per la stampa del nominativo.
		spostare_cursore(riga, COLONNA_VISUALIZZARE_NOMINATIVO);
		//Stampo la Stringa nominativo del contatto.
		stampare_stringa( leggere_nominativo_contatto(contatto) );
		//Posiziono il cursore sulla riga fornita in input e sulla colonna per la stampa del numero di telefono.
		spostare_cursore(riga, COLONNA_VISUALIZZARE_N_TELEFONO);
		//Stampo la Stringa  numero di telefono del contatto.
		stampare_stringa( leggere_n_telefono_contatto(contatto) );
		//Posiziono il cursore sulla riga fornita in input e sulla colonna per la stampa dello stato.
		spostare_cursore(riga, COLONNA_VISUALIZZARE_STATO);
		//Stampo la scritta corrispondente alla codifica del valore dello stato.
		if( leggere_stato_contatto(contatto) == STATO_PREDEFINITO ){
			stampare_a_schermo_messaggio(MESSAGGIO_STATO_PREDEFINITO);
		} else if( leggere_stato_contatto(contatto) == STATO_BLOCCATO ){
			stampare_a_schermo_messaggio(MESSAGGIO_STATO_BLOCCATO);
		} else if( leggere_stato_contatto(contatto) == STATO_PREFERITO ){
			stampare_a_schermo_messaggio(MESSAGGIO_STATO_PREFERITO);
		}
		//Se il contatto dovesse presentare errori, allora stampo stringhe di errore.
	} else{
		//Posiziono il cursore sulla riga fornita in input e sulla colonna per la stampa del nominativo.
		spostare_cursore(riga, COLONNA_VISUALIZZARE_NOMINATIVO);
		//Stampo l'errore del nominativo del contatto.
		stampare_a_schermo_messaggio(MESSAGGIO_ERRORE_GENERICO);
		//Posiziono il cursore sulla riga fornita in input e sulla colonna per la stampa del numero di telefono.
		spostare_cursore(riga, COLONNA_VISUALIZZARE_N_TELEFONO);
		//Stampo l'errore del numero di telefono del contatto.
		stampare_a_schermo_messaggio(MESSAGGIO_ERRORE_GENERICO);
		//Posiziono il cursore sulla riga fornita in input e sulla colonna per la stampa dello stato.
		spostare_cursore(riga, COLONNA_VISUALIZZARE_STATO);
		//Stampo l'errore dello stato del contatto.
		stampare_a_schermo_messaggio(MESSAGGIO_ERRORE_GENERICO);
	}
	return;
}

/*
 * Funzione per la stampa di un messaggio all'utente dato un codice corrispondente al messaggio.
 * tale funzione crea un interfaccio ulteriore per informare l'utente ed attendere la risposta.
 */
void gestire_messaggi_utente( int codice )
{
	char risposta_utente;	//Risposta dell'utente a seguito della visualizzazione del messaggio.

	//Stampo a video il layout corrispondente alla visualizzazione di un messaggio utente.
	stampare_layout_interfaccia(PERCORSO_ESITO_OPERAZIONE);
	//Mi posiziono sulla riga su cui stampare il messaggio letto.
	spostare_cursore(RIGA_TESTO, COLONNA_TESTO);
	//Stampo a video il messaggio.
	stampare_a_schermo_messaggio(codice);
	//Attendo una risposta da parte dell'utente per continuare con il funzionamento regolare del programma.
	do{
		pulire_schermata(RIGA_INPUT_UTENTE,COLONNA_INPUT_UTENTE, RIGA_INPUT_UTENTE, COLONNE_MASSIME_SCHERMO-2);
		spostare_cursore(RIGA_INPUT_UTENTE, COLONNA_INPUT_UTENTE);
		scanf( " %c",&risposta_utente );
		//Pulisco il buffer di sistema per evitare errori di acquisizione input utente.
		pulire_buffer_input();
	}while( risposta_utente != CARATTERE_CONTINUA );
}

/*
 * Funzione per la stampa di un messaggio di errore, stampa un messaggio
 * tale funzione informa l'utente dell'errore nella stessa interfaccia in cui è avvenuto l'errore,
 * tale funzione è necessaria per mostrare all'utente quali parametri risultano errati.
 */
void visualizzare_errore_utente( int errore )
{
	char risposta_utente;	//Risposta dell'utente a seguito della visualizzazione del messaggio.

	//Pulisco le righe dedicate all'input utente, che saranno quelle in cui stampare l'errore avvenuto.
	pulire_schermata( RIGA_INPUT_UTENTE-1,COLONNA_TESTO, RIGA_INPUT_UTENTE, COLONNE_MASSIME_SCHERMO-2 );
	spostare_cursore( RIGA_INPUT_UTENTE-1, COLONNA_TESTO );
	//Stampo a video il messaggio.
	stampare_a_schermo_messaggio(errore);
	//Mi posiziono sulla riga input utente e informo l'utente che il programma attende una risposta.
	spostare_cursore(RIGA_INPUT_UTENTE, COLONNA_TESTO);
	stampare_a_schermo_messaggio(MESSAGGIO_CONTINUA);
	//Attendo una risposta da parte dell'utente per continuare con il funzionamento regolare del programma.
	do{
		pulire_schermata(RIGA_INPUT_UTENTE,COLONNA_INPUT_UTENTE, RIGA_INPUT_UTENTE, COLONNE_MASSIME_SCHERMO-2);
		spostare_cursore(RIGA_INPUT_UTENTE, COLONNA_INPUT_UTENTE);
		scanf( " %c",&risposta_utente );
		pulire_buffer_input();
	}while( risposta_utente != CARATTERE_CONTINUA );

	//Reimposto il resto precedente alla stampa di errore, posizionandomi sulle righe interessate e stampando il testo.
	spostare_cursore(RIGA_INPUT_UTENTE-1, COLONNA_TESTO);
	stampare_a_schermo_messaggio(MESSAGGIO_SALVA_CONTINUA_1);
	spostare_cursore(RIGA_INPUT_UTENTE, COLONNA_TESTO);
	stampare_a_schermo_messaggio(MESSAGGIO_SALVA_CONTINUA_2);
	return;
}

//Funzione di acquisizione ed inserimento in rubrica di un contatto fornito dall'utente in input.
void acquisire_contatto_input(Rubrica *rubrica)
{
	char stringa_input[LUNGHEZZA_MASSIMA_STRINGA];	//Stinga acquisita in input (utilizzata per nominativo e numero telefono).
	char risposta_utente; 							//Risposta dell'utente a seguito della visualizzazione del messaggio.
	Contatto contatto_acquisito;					//Contatto acquisito con le informazioni fornite dall'utente.
	char stato;										//Stato acquisito in input.
	Stringa nominativo;								//Variabile ausiliaria poichè non accettiamo stringhe di lunghezza 0.
	do{
		//Stampo a video il layout per l'acquisizione di un contatto.
		stampare_layout_interfaccia(PERCORSO_INTERFACCIA_INSERIRE_CONTATTO);
		//Puliamo la schermata (tutti i campi) prima dell'inserimento di un contatto.
		pulire_schermata(RIGA_NOMINATIVO_INSERIMENTO,COLONNA_INPUT_UTENTE, RIGA_NOMINATIVO_INSERIMENTO, COLONNE_MASSIME_SCHERMO-2);
		pulire_schermata(RIGA_N_TELEFONO_INSERIMENTO,COLONNA_INPUT_UTENTE, RIGA_N_TELEFONO_INSERIMENTO, COLONNE_MASSIME_SCHERMO-2);
		pulire_schermata(RIGA_STATO_INSERIMENTO,COLONNA_INPUT_UTENTE, RIGA_STATO_INSERIMENTO, COLONNE_MASSIME_SCHERMO-2);
		pulire_schermata(RIGA_INPUT_UTENTE,COLONNA_INPUT_UTENTE, RIGA_INPUT_UTENTE, COLONNE_MASSIME_SCHERMO-2);
		//Inizializziamo il contatto da acquisire.
		scrivere_errore_contatto(&contatto_acquisito, CODICE_CORRETTO);
		//Posizionamento sullo schermo alla riga di acquisizione nominativo del contatto.
		spostare_cursore(RIGA_NOMINATIVO_INSERIMENTO, COLONNA_INPUT_UTENTE);
		//Acquisizione dei dati dell'utente.
		scanf(" %[^\n]s", stringa_input);
		//Richiamo la funzione di pulizia del buffer di sistema, per evitare errori di acquisizione input.
		pulire_buffer_input();
		//Scrittura del nominativo acquisito in input.
		scrivere_nominativo_contatto(&contatto_acquisito, convertire_stringa(stringa_input));
		//Posizionamento sullo schermo alla riga di acquisizione numero di telefono del contatto.
		spostare_cursore(RIGA_N_TELEFONO_INSERIMENTO, COLONNA_INPUT_UTENTE);
		//Acquisizione dei dati dell'utente.
		scanf(" %s", stringa_input);
		//Scrittura del numero di telefono acquisito in input.
		scrivere_n_telefono_contatto(&contatto_acquisito, convertire_stringa(stringa_input));
		//Posizionamento sullo schermo alla riga di acquisizione stato del contatto.
		spostare_cursore(RIGA_STATO_INSERIMENTO, COLONNA_INPUT_UTENTE);
		//Acquisizione del dato dell'utente.
		scanf(" %c", &stato);
		//Scrittura dello stato acquisito in input.
		scrivere_stato_contatto( &contatto_acquisito, convertire_in_intero(stato));
		/*
		 * Acquisizione scelta utente:
		 * e - Uscire senza salvare.
		 * c - Salvare ed inserire un altro contatto.
		 * s - Salvare ed uscire.
		 */
		do{
			pulire_schermata(RIGA_INPUT_UTENTE,COLONNA_INPUT_UTENTE, RIGA_INPUT_UTENTE, COLONNE_MASSIME_SCHERMO-2);
			spostare_cursore(RIGA_INPUT_UTENTE, COLONNA_INPUT_UTENTE);
			scanf(" %c", &risposta_utente);
			pulire_buffer_input();
		}while ( risposta_utente != CARATTERE_USCITA && risposta_utente != CARATTERE_SALVATAGGIO_ED_USCITA
				&& risposta_utente != CARATTERE_CONTINUA );

		//Controllo sulla correttezza del contatto nel caso l'utente voglia salvarlo.
		if ( risposta_utente == CARATTERE_CONTINUA || risposta_utente == CARATTERE_SALVATAGGIO_ED_USCITA ){
			nominativo = leggere_nominativo_contatto(contatto_acquisito);
			if ( controllare_correttezza_contatto(contatto_acquisito) != CODICE_CORRETTO || leggere_lunghezza_stringa(nominativo) <= LUNGHEZZA_MINIMA_STRINGA ){
				//Visualizzo il messaggio di errore nel caso, vi siano errori nei parametri input acquisiti.
				if ( leggere_lunghezza_stringa(nominativo) <= 0 ){
					scrivere_errore_contatto(&contatto_acquisito, CODICE_ERRORE_CARATTERE_STRINGA);
				}
				visualizzare_errore_utente(controllare_correttezza_contatto(contatto_acquisito) );
			} else{
				//Verifico che la rubrica non sia piena.
				if( leggere_numero_contatti_rubrica(*rubrica) < NUMERO_MASSIMO_CONTATTI ){
					//Inserisco il contatto nel caso in cui tale condizione sia verificata.
					inserire_contatto_rubrica(rubrica, contatto_acquisito);
					if(leggere_errore_rubrica(*rubrica) != CODICE_CORRETTO ){
						//Mostro un messaggio di errore altrimenti, e riporto la rubrica allo stato precedente all'errore.
						visualizzare_errore_utente( leggere_errore_rubrica(*rubrica) );
						scrivere_errore_rubrica(rubrica, CODICE_CORRETTO);
					}else{
						gestire_messaggi_utente(MESSAGGIO_CONTATTO_SALVATO);
					}
				}else{
					visualizzare_errore_utente(CODICE_ERRORE_LUNGHEZZA_RUBRICA);
				}
			}
		}
		//Continuo fino a quando l'utente non sceglie l'opzione "Salva ed esce" o "Esci".
	}while( risposta_utente != CARATTERE_USCITA && risposta_utente != CARATTERE_SALVATAGGIO_ED_USCITA );
	return;
}

//Funzione di ricerca di un contatto fornito il nominativo in input.
void ricercare_contatto_input( Rubrica rubrica )
{
	char stringa_input[LUNGHEZZA_MASSIMA_STRINGA];	//Stinga acquisita in input (utilizzata per nominativo e numero telefono.
	char risposta_utente; 							//Risposta dell'utente a seguito della visualizzazione del messaggio.
	Contatto contatto_acquisito;					//Contatto acquisito con le informazioni fornite dall'utente.
	int posizione;									//Posizione del contatto acquisito all'interno della rubrica.

	do{
		//Stampo a video il layout per la ricerca di un contatto.
		stampare_layout_interfaccia(PERCORSO_INTERFACCIA_RICERCARE_CONTATTO);
		//Puliamo la schermata (tutti i campi) prima della ricerca di un contatto.
		pulire_schermata(RIGA_VISUALIZZARE_CONTATTO,COLONNA_VISUALIZZARE_NOMINATIVO, RIGA_VISUALIZZARE_CONTATTO, COLONNA_FINE_NOMINATIVO);
		pulire_schermata(RIGA_VISUALIZZARE_CONTATTO,COLONNA_VISUALIZZARE_N_TELEFONO, RIGA_VISUALIZZARE_CONTATTO, COLONNA_FINE_N_TELEFONO);
		pulire_schermata(RIGA_VISUALIZZARE_CONTATTO,COLONNA_VISUALIZZARE_STATO, RIGA_VISUALIZZARE_CONTATTO, COLONNA_FINE_STATO);
		//Puliamo la il campo di acquisizione del nominativo e della scelta utente.
		pulire_schermata(RIGA_NOMINATIVO_INSERIMENTO,COLONNA_INPUT_UTENTE, RIGA_NOMINATIVO_INSERIMENTO, COLONNE_MASSIME_SCHERMO-2);
		pulire_schermata(RIGA_INPUT_UTENTE,COLONNA_INPUT_UTENTE, RIGA_INPUT_UTENTE, COLONNE_MASSIME_SCHERMO-2);

		//Inizializziamo il contatto da acquisire.
		inizializzare_contatto_rubrica(&contatto_acquisito);

		//Posizionamento sullo schermo alla riga di acquisizione nominativo del contatto.
		spostare_cursore(RIGA_NOMINATIVO_INSERIMENTO, COLONNA_INPUT_UTENTE);
		//Acquisizione dei dati dell'utente.
		scanf(" %[^\n]s", stringa_input);
		// Richiamo la funzione di pulizia del buffer di sistema, per evitare errori di acquisizione input.
		pulire_buffer_input();
		//Scrittura del nominativo acquisito in input.
		scrivere_nominativo_contatto(&contatto_acquisito, convertire_stringa(stringa_input) );
		//Ricerco il contatto inserito dall'utente.
		posizione = cercare_contatto_rubrica( rubrica, contatto_acquisito );
		//Verifio che sia stato trovato, o che sia avvenuto un errore.
		if ( posizione >= CODICE_CORRETTO ){
			//In caso sia stato trovato, allora recupero il contatto dalla rubrica.
			copiare_contatto( &contatto_acquisito, leggere_contatto_rubrica(rubrica, posizione) );
			//E richiamo la funzione di stampa del contatto, passandogli la riga su cui stamparlo.
			stampare_contatto( contatto_acquisito, RIGA_VISUALIZZARE_CONTATTO );
		}else{
			//Se il contatto non dovesse essere stato trovato, o in caso di errore, visualizzo il messaggio.
			visualizzare_errore_utente(posizione);
			pulire_schermata(RIGA_INPUT_UTENTE-1,COLONNA_TESTO, RIGA_INPUT_UTENTE, COLONNE_MASSIME_SCHERMO-2);
			//E reimposto il testo predefinito della schermata.
			spostare_cursore(RIGA_INPUT_UTENTE, COLONNA_TESTO);
			stampare_a_schermo_messaggio(MESSAGGIO_CONTINUA_ESCI);
		}
		do{
			//Attendo che l'utente visualizzi il messaggio e decida come continuare.
			pulire_schermata(RIGA_INPUT_UTENTE,COLONNA_INPUT_UTENTE, RIGA_INPUT_UTENTE, COLONNE_MASSIME_SCHERMO-2);
			spostare_cursore(RIGA_INPUT_UTENTE, COLONNA_INPUT_UTENTE);
			scanf(" %c", &risposta_utente);
			pulire_buffer_input();
		}while ( risposta_utente != CARATTERE_USCITA && risposta_utente != CARATTERE_CONTINUA );
		//Resto nell'operazione di ricerca fino a quando l'utente non vuole uscire (Ditigando 'e').
	}while( risposta_utente != CARATTERE_USCITA );
	return;
}

//Funzione di importazione rubrica (Scelta dall'input utente).
void importare_rubrica_input( Rubrica *rubrica )
{
	//Richiamo la funzione di importazione rubrica definita nella logica del programma.
	importare_rubrica(rubrica);
	//Verifico che sia andata a buon fine l'operazione.
	if( leggere_errore_rubrica(*rubrica) != CODICE_CORRETTO ){
		//In caso contrario, stampo un messagio d'errore.
		gestire_messaggi_utente(MESSAGGIO_RUBRICA_NON_IMPORTATA);
		scrivere_errore_rubrica(rubrica, CODICE_CORRETTO);
	}else{
		//Altrimenti stampo un messaggio informando l'utente che l'importazione è avvenuta.
		gestire_messaggi_utente(MESSAGGIO_RUBRICA_IMPORTATA);
	}
	return;
}

//Funzione di esportazione rubrica (Scelta dall'input utente).
void esportare_rubrica_input( Rubrica rubrica )
{
	int errore; //Errore nell'esportazione della rubrica.
	//Controllo che la rubrica in input sia corretta e sia NON VUOTA.
	if( leggere_errore_rubrica(rubrica) != CODICE_CORRETTO
			|| leggere_numero_contatti_rubrica(rubrica) <= NUMERO_MINIMO_CONTATTI
			|| leggere_numero_contatti_rubrica(rubrica) > NUMERO_MASSIMO_CONTATTI ){
		/*
		 * Nel caso tali condizioni non siano rispettate, mostro il messaggio
		 * che non permette di far esportare la rubrica.
		 */
		gestire_messaggi_utente(MESSAGGIO_RUBRICA_NON_ESPORTATA);
	}else{
		//In caso rispetti le condizioni, esporto la rubrica verificando non avvengano errori nell'esportazione.
		errore = esportare_rubrica(rubrica);
		if ( errore == CODICE_CORRETTO ){
			gestire_messaggi_utente(MESSAGGIO_RUBRICA_ESPORTATA);
		} else{
			//Altrimenti stampo un messaggio informando l'utente che c'è stato un errore nell'esportazione.
			gestire_messaggi_utente(errore);
		}
	}
	return;
}

//Funzione di stampa dei contatti in base alla pagina ed allo stato del contatto.
void stampare_contatti_pagina( Rubrica rubrica, int stato_contatti )
{
		int i; 								//Contatore scorrimento contatti.
		char spostamento_pagina;			//Pagina da visualizzare.
	    int indice_base_pagina;				//Indice di partenza del contatto da stampare.
	    int indice_limite_pagina;			//Indice di fine del contatto da stampare.
	    /*
	     * Contatore per scandire quanti contatti sono stati stampati,
		 * al fine di essere certi che un intera pagina per tipo contatto
		 * scelto sia stata stampata.
		 */
	    int contatti_controllati;
	    int riga_stampa_contatto;			//Contatore per spostare la riga di stampa.
	    /*
	     * Contatore per contare quanti contatti totali del tipo richiesto
		 * dall’utente ci sono, al fine di avvisare l’utente e controllare
		 * che l’utente non possa superare la pagina limite.
		 */
	    int numero_contatti_da_stampare;
	    int pagina_corrente; 				//Pagina dei contatti corrente, varia in base alla scelta utente.

	    //Imposto il valore della pagina_corrente a zero.
	    pagina_corrente = 0;
	    //Calcolo il numero di contatti da stampare in base al criterio scelto.
	    numero_contatti_da_stampare = 0;
	    i=0;
	    while ( i < leggere_numero_contatti_rubrica(rubrica)){
			if (stato_contatti == STATO_PREDEFINITO || leggere_stato_contatto(leggere_contatto_rubrica(rubrica, i)) == stato_contatti) {
				numero_contatti_da_stampare = numero_contatti_da_stampare + 1;
			}
			i = i + 1 ;
		}

	    //Scorro tra le pagine finchè l'utente non decide di uscire.
	    do{
	    	indice_base_pagina = pagina_corrente * CONTATTI_PER_PAGINA;      	//Calcolo l'indice di partenza dei contatti.
	    	indice_limite_pagina = indice_base_pagina + CONTATTI_PER_PAGINA;	//Calcolo l'indice di fine dei contatti di una pagina.

		    //Puliamo la pagina precedente prima di proseguire.
			pulire_schermata(RIGA_VISUALIZZARE_CONTATTO,COLONNA_VISUALIZZARE_NOMINATIVO, RIGA_VISUALIZZARE_CONTATTO+CONTATTI_PER_PAGINA-1, COLONNA_FINE_NOMINATIVO);
			pulire_schermata(RIGA_VISUALIZZARE_CONTATTO,COLONNA_VISUALIZZARE_N_TELEFONO, RIGA_VISUALIZZARE_CONTATTO+CONTATTI_PER_PAGINA-1, COLONNA_FINE_N_TELEFONO);
			pulire_schermata(RIGA_VISUALIZZARE_CONTATTO,COLONNA_VISUALIZZARE_STATO, RIGA_VISUALIZZARE_CONTATTO+CONTATTI_PER_PAGINA-1, COLONNA_FINE_STATO);
			pulire_schermata(RIGA_INPUT_UTENTE,COLONNA_INPUT_UTENTE, RIGA_INPUT_UTENTE, COLONNE_MASSIME_SCHERMO-2);

			//Stampo solo i contatti che rispettano la condizione dello stato richiesto dall'utente.
			i = 0;
			contatti_controllati = 0;
			riga_stampa_contatto = 0;
			while ( i < leggere_numero_contatti_rubrica(rubrica)){
				if (stato_contatti == STATO_PREDEFINITO || leggere_stato_contatto(leggere_contatto_rubrica(rubrica, i)) == stato_contatti) {
					if (contatti_controllati >= indice_base_pagina && contatti_controllati < indice_limite_pagina) {
						stampare_contatto(leggere_contatto_rubrica(rubrica, i), RIGA_VISUALIZZARE_CONTATTO+riga_stampa_contatto);
						riga_stampa_contatto = riga_stampa_contatto + 1;
					}
					contatti_controllati = contatti_controllati + 1;
				}
				i = i + 1 ;
			}

		    //Richiesta della pagina che si desidera visualizzare.
			pulire_schermata(RIGA_INPUT_UTENTE-1, COLONNA_TESTO, RIGA_INPUT_UTENTE, COLONNE_MASSIME_SCHERMO-2);
			spostare_cursore(RIGA_INPUT_UTENTE-1, COLONNA_TESTO);
			stampare_a_schermo_messaggio(MESSAGGIO_AVANTI_INDIETRO);
			spostare_cursore(RIGA_INPUT_UTENTE, COLONNA_TESTO);
			stampare_a_schermo_messaggio(MESSAGGIO_USCITA);
			do{
				//Attendiamo una risposta valida dall'utente.
				pulire_schermata(RIGA_INPUT_UTENTE,COLONNA_INPUT_UTENTE, RIGA_INPUT_UTENTE, COLONNE_MASSIME_SCHERMO-2);
				spostare_cursore(RIGA_INPUT_UTENTE, COLONNA_INPUT_UTENTE);
				scanf( " %c", &spostamento_pagina );
				pulire_buffer_input();
				/*
				 * La risposta valida deve essere limitata alle pagine disponibili,
				 * in base al numero totale di contatti da stampare, controlliamo che sia così.
				 */
			}while( spostamento_pagina != PAGINA_AVANTI && spostamento_pagina != PAGINA_INDIETRO && spostamento_pagina != CARATTERE_USCITA );
			//Se l'input è valido, allora stampo i contatti con lo stato, e della pagina corrispondenti.
			if( spostamento_pagina == PAGINA_AVANTI && indice_limite_pagina < numero_contatti_da_stampare){
				pagina_corrente = pagina_corrente + 1;
			}else if ( spostamento_pagina == PAGINA_INDIETRO && pagina_corrente >= PAGINA_INIZIALE){
				pagina_corrente = pagina_corrente - 1;
			}
	    }while( spostamento_pagina != CARATTERE_USCITA);	//Continuo finchè l'utente non decide di uscire.
}

//Funzione di visualizzazione contatti scelta dall'utente in input.
void visualizzare_rubrica_input( Rubrica rubrica )
{
	char risposta_utente;		//Risposta dell'utente a seguito della visualizzazione del messaggio.

	do{
		//Stampo a video il layout per la visualizzazione dei contatti in rubrica.
		stampare_layout_interfaccia(PERCORSO_INTERFACCIA_VISUALIZZARE_RUBRICA);
		//Puliamo la riga dell'input utente ed aspettiamo lo stato dei contatti che si desidera visualizzare.
		pulire_schermata( RIGA_INPUT_UTENTE-1, COLONNA_TESTO, RIGA_INPUT_UTENTE, COLONNE_MASSIME_SCHERMO-2 );
		spostare_cursore( RIGA_INPUT_UTENTE-1, COLONNA_TESTO);
		//Richiediamo all'utente quali tipi di contatti vuole visualizzare.
		stampare_a_schermo_messaggio(MESSAGGIO_SCELTA_CRITERIO);
		spostare_cursore( RIGA_INPUT_UTENTE, COLONNA_TESTO );
		stampare_a_schermo_messaggio(MESSAGGIO_USCITA);
		pulire_schermata(RIGA_INPUT_UTENTE,COLONNA_INPUT_UTENTE, RIGA_INPUT_UTENTE, COLONNE_MASSIME_SCHERMO-2);
		spostare_cursore(RIGA_INPUT_UTENTE, COLONNA_INPUT_UTENTE);
		//Attendiamo una risposta valida dell'utente.
		scanf(" %c", &risposta_utente);
		pulire_buffer_input();
		//Se la risposta è uno fra gli stati possibili di un contatto, allora proseguamo con l'operazione.
		if ( convertire_in_intero(risposta_utente) >= STATO_PREDEFINITO && convertire_in_intero(risposta_utente) <= STATO_BLOCCATO ){
			stampare_contatti_pagina( rubrica, convertire_in_intero(risposta_utente));
		}
		//Continuo con l'operazione fino a quando l'utente non desidera Uscire o sbaglia uno delle richieste input.
	}while( risposta_utente != CARATTERE_USCITA
			&& ( convertire_in_intero(risposta_utente) < STATO_PREDEFINITO
			|| convertire_in_intero(risposta_utente) > STATO_BLOCCATO) );
}

//Funzione eliminazione di un contatto di cui è fornito il nominativo dall'utente in input.
void eliminare_contatto_input( Rubrica *rubrica )
{
	char stringa_input[LUNGHEZZA_MASSIMA_STRINGA];	//Stinga acquisita in input (utilizzata per nominativo e numero telefono.
	char risposta_utente; 							//Risposta dell'utente a seguito della visualizzazione del messaggio.
	Contatto contatto_acquisito;					//Contatto acquisito con le informazioni fornite dall'utente.
	int posizione;									//Posizione del contatto acquisito all'interno della rubrica.

	do{
		//Stampo a video il layout per la ricerca di un contatto.
		stampare_layout_interfaccia(PERCORSO_INTERFACCIA_RICERCARE_CONTATTO);
		//Puliamo la schermata (tutti i campi) prima della ricerca di un contatto.
		pulire_schermata(RIGA_VISUALIZZARE_CONTATTO,COLONNA_VISUALIZZARE_NOMINATIVO, RIGA_VISUALIZZARE_CONTATTO, COLONNA_FINE_NOMINATIVO);
		pulire_schermata(RIGA_VISUALIZZARE_CONTATTO,COLONNA_VISUALIZZARE_N_TELEFONO, RIGA_VISUALIZZARE_CONTATTO, COLONNA_FINE_N_TELEFONO);
		pulire_schermata(RIGA_VISUALIZZARE_CONTATTO,COLONNA_VISUALIZZARE_STATO, RIGA_VISUALIZZARE_CONTATTO, COLONNA_FINE_STATO);
		//Puliamo la il campo di acquisizione del nominativo e della scelta utente.
		pulire_schermata(RIGA_NOMINATIVO_INSERIMENTO,COLONNA_INPUT_UTENTE, RIGA_NOMINATIVO_INSERIMENTO, COLONNE_MASSIME_SCHERMO-2);
		pulire_schermata(RIGA_INPUT_UTENTE,COLONNA_INPUT_UTENTE, RIGA_INPUT_UTENTE, COLONNE_MASSIME_SCHERMO-2);
		//Inizializziamo il contatto da acquisire
		inizializzare_contatto_rubrica(&contatto_acquisito);
		//Posizionamento sullo schermo, ed acquisizione dei dati dell'utente e scrittura nei relativi campi del contatto.
		spostare_cursore(RIGA_NOMINATIVO_INSERIMENTO, COLONNA_INPUT_UTENTE);
		//Acquisizione dei dati dell'utente.
		scanf(" %[^\n]s", stringa_input);
		//Richiamo la funzione di pulizia del buffer di sistema, per evitare errori di acquisizione input.
		pulire_buffer_input();
		//Scrittura del nominativo acquisito in input.
		scrivere_nominativo_contatto(&contatto_acquisito, convertire_stringa(stringa_input) );
		//Ricerco il contatto inserito dall'utente.
		posizione = cercare_contatto_rubrica( *rubrica, contatto_acquisito );
		//Verifio che sia stato trovato, o che sia avvenuto un errore.
		if ( posizione >= CODICE_CORRETTO ){
			//In caso sia stato trovato, allora recupero il contatto dalal rubrica.
			copiare_contatto( &contatto_acquisito, leggere_contatto_rubrica(*rubrica, posizione) );
			//E richiamo la funzione di stampa del contatto, passandogli la riga su cui stamparlo.
			stampare_contatto( contatto_acquisito, RIGA_VISUALIZZARE_CONTATTO );
			//Richiedo all'utente se intende veramente cancellare il contatto mostrato.
			pulire_schermata(RIGA_INPUT_UTENTE-1,COLONNA_TESTO, RIGA_INPUT_UTENTE, COLONNE_MASSIME_SCHERMO-2);
			spostare_cursore(RIGA_INPUT_UTENTE-1, COLONNA_TESTO);
			stampare_a_schermo_messaggio(MESSAGGIO_CONFERMA_ELIMINAZIONE);
			spostare_cursore(RIGA_INPUT_UTENTE, COLONNA_TESTO);
			stampare_a_schermo_messaggio(MESSAGGIO_RISPOSTA);
			do{
				//Attendo la risposta dell'utente.
				pulire_schermata(RIGA_INPUT_UTENTE,COLONNA_INPUT_UTENTE, RIGA_INPUT_UTENTE, COLONNE_MASSIME_SCHERMO-2);
				spostare_cursore(RIGA_INPUT_UTENTE, COLONNA_INPUT_UTENTE);
				scanf(" %c", &risposta_utente);
				pulire_buffer_input();
			}while ( risposta_utente != CARATTERE_USCITA && risposta_utente != CARATTERE_CONTINUA );
			//Se la risposta è affermativa 'c' allora richiamo la funzione di eliminazione
			if( risposta_utente == CARATTERE_CONTINUA ){
				//Elimino il contatto che so' esistere poichè verificato tramite ricerca.
				eliminare_contatto_rubrica( rubrica, posizione );
				//E stampo la buona riuscita dell'eliminazione.
				gestire_messaggi_utente( MESSAGGIO_CONTATTO_ELIMINATO );
			}
		//Se il contatto non fosse stato trovato, allora comunico l'errore all'utente.
		}else{
			visualizzare_errore_utente( posizione );
			pulire_schermata(RIGA_INPUT_UTENTE-1,COLONNA_TESTO, RIGA_INPUT_UTENTE, COLONNE_MASSIME_SCHERMO-2);
			//Reimposto il resto originale prima do continuare con l'operazione.
			spostare_cursore(RIGA_INPUT_UTENTE, COLONNA_TESTO);
			stampare_a_schermo_messaggio(MESSAGGIO_CONTINUA_ESCI);
		}
		stampare_layout_interfaccia(PERCORSO_INTERFACCIA_RICERCARE_CONTATTO);
		do{
			//Attendo che l'utente visualizzi l'esito dell'operazione, ed in seguito continui o esca dall'operazione.
			pulire_schermata(RIGA_INPUT_UTENTE,COLONNA_INPUT_UTENTE, RIGA_INPUT_UTENTE, COLONNE_MASSIME_SCHERMO-2);
			spostare_cursore(RIGA_INPUT_UTENTE, COLONNA_INPUT_UTENTE);
			scanf(" %c", &risposta_utente);
			pulire_buffer_input();
		}while ( risposta_utente != CARATTERE_USCITA && risposta_utente != CARATTERE_CONTINUA );
		//Resto nell'operazione di eliminazione fino a quando l'utente non vuole uscire dall'operazione (Ditigando 'e').
	}while( risposta_utente != CARATTERE_USCITA );
	return;
}

//Funzione di ordinamento della rubrica (Scelta in input dall'utente).
void ordinare_rubrica_input( Rubrica *rubrica )
{
	char risposta_utente;	//Risposta dell'utente a seguito della visualizzazione del messaggio.
	int errore;				//Errore nella rubrica in input.
	//Stampo a video il layout per la visualizzazione di un messaggio e pulisco il vecchio messaggio.
	stampare_layout_interfaccia(PERCORSO_ESITO_OPERAZIONE);
	pulire_schermata(RIGA_TESTO, COLONNA_TESTO, RIGA_TESTO, COLONNE_MASSIME_SCHERMO-2);
	//Mi posiziono sulla riga per stampare il messaggio.
	spostare_cursore(RIGA_TESTO, COLONNA_TESTO);
	//Verifico prima se la rubrica fornita in input è vuota o meno.
	if( leggere_numero_contatti_rubrica(*rubrica) == NUMERO_MINIMO_CONTATTI ){
		//Se fosse vuota, allora il messaggio stampato sarà relativo all'operazione fallita poichè la rubrica risulta vuota.
		gestire_messaggi_utente(MESSAGGIO_RUBRICA_VUOTA);
	}else{
		//Altrimenti visualizzo le scelte utente con i possibili criteri di ordinamento
		stampare_a_schermo_messaggio(MESSAGGIO_SCELTA_ORDINAMENTO);
		pulire_schermata(RIGA_INPUT_UTENTE, COLONNA_TESTO, RIGA_INPUT_UTENTE, COLONNE_MASSIME_SCHERMO-2);
		spostare_cursore(RIGA_INPUT_UTENTE, COLONNA_TESTO);
		stampare_a_schermo_messaggio(MESSAGGIO_RISPOSTA);
		do{
			//Attendo la risposta dell'utente
			pulire_schermata(RIGA_INPUT_UTENTE,COLONNA_INPUT_UTENTE, RIGA_INPUT_UTENTE, COLONNE_MASSIME_SCHERMO-2);
			spostare_cursore(RIGA_INPUT_UTENTE, COLONNA_INPUT_UTENTE);
			scanf(" %c", &risposta_utente);
			pulire_buffer_input();
		}while ( (convertire_in_intero(risposta_utente) != ORDINAMENTO_CRESCENTE) && (convertire_in_intero(risposta_utente)!= ORDINAMENTO_DECRESCENTE) );
		//Ordino la rubrica secondo il criterio scelto.

		ordinare_contatti_rubrica( rubrica, convertire_in_intero(risposta_utente) );
		//Verifico se l'ordinamento è andato a buon fine, oppure ha generato errore.
		errore = leggere_errore_rubrica(*rubrica);
		if ( errore == CODICE_CORRETTO ){
			//Nel caso sia andato a buon fine, comunico ciò all'utente.
			gestire_messaggi_utente(MESSAGGIO_ORDINAMENTO_EFFETTUATO);
		} else{
			//Altrimenti stampo l'errore relativo avvenuto.
			gestire_messaggi_utente(errore);
		}
	}
}

//Funzione di acquisizione informaizoni durante l'operazione di modifica.
void acquisire_informazioni_modifica( Rubrica *rubrica, Contatto contatto_acquisito, int posizione )
{
	char risposta_utente;			//Risposta dell'utente a seguito della visualizzazione del messaggio.
	char stringa_input[20];			//Stinga acquisita in input (utilizzata per nominativo e numero telefono.
	Contatto contatto_modificato;	//Contatto modificato dall'utente.
	char stato;						//Stato da modificare.
	int errore;						//Errore eventuale sui parametri in input dell'utente, o il contatto da modificare non esiste.
	Stringa nominativo;

	//Stampo a video il layout per la richiesta delle informazioni da modificare.
	stampare_layout_interfaccia( PERCORSO_ESITO_OPERAZIONE );
	pulire_schermata( RIGA_TESTO, COLONNA_TESTO, RIGA_TESTO, COLONNE_MASSIME_SCHERMO-2 );
	spostare_cursore( RIGA_TESTO, COLONNA_TESTO );
	//Stampo le scelte delle possibili informazioni modificabili.
	stampare_a_schermo_messaggio(MESSAGGIO_SCELTA_MODIFICA);
	spostare_cursore(RIGA_TESTO+1, COLONNA_TESTO);
	stampare_a_schermo_messaggio(MESSAGGIO_SCELTA_NOMINATIVO);
	spostare_cursore(RIGA_TESTO+2, COLONNA_TESTO);
	stampare_a_schermo_messaggio(MESSAGGIO_SCELTA_N_TELEFONO);
	spostare_cursore(RIGA_TESTO+3, COLONNA_TESTO);
	stampare_a_schermo_messaggio(MESSAGGIO_SCELTA_STATO);

	pulire_schermata( RIGA_INPUT_UTENTE, COLONNA_TESTO, RIGA_INPUT_UTENTE, COLONNE_MASSIME_SCHERMO-2 );
	spostare_cursore(RIGA_INPUT_UTENTE, COLONNA_TESTO);
	stampare_a_schermo_messaggio(MESSAGGIO_RISPOSTA);
	do{
		//Attendo che l'utente inserisca quale delle informazioni vuole inserire.
		pulire_schermata(RIGA_INPUT_UTENTE,COLONNA_INPUT_UTENTE, RIGA_INPUT_UTENTE, COLONNE_MASSIME_SCHERMO-2);
		spostare_cursore(RIGA_INPUT_UTENTE, COLONNA_INPUT_UTENTE);
		scanf(" %c", &risposta_utente);
		pulire_buffer_input();
	}while ( risposta_utente != CARATTERE_USCITA
			&& risposta_utente != SCELTA_INSERIRE_NOMINATIVO
			&& risposta_utente != SCELTA_INSERIRE_N_TELEFONO
			&& risposta_utente != SCELTA_INSERIRE_STATO);
	//Stampo il layout di modifica del contatto.
	stampare_layout_interfaccia(PERCORSO_INTERFACCIA_MODIFICARE_CONTATTO);
	//Riporto in alto, le informazioni del contatto che si sta modificando.
	stampare_contatto( contatto_acquisito, RIGA_VISUALIZZARE_CONTATTO );
	//Copio tali informazioni in una variabile ausiliaria
	copiare_contatto( &contatto_modificato, contatto_acquisito );
	/*
	 * In base all'input precedente dell'utente, posizioniamo il cursore sulla riga
	 * e sulla colonna corrispondenti alla scelta dell'informazione da modificare
	 * attendiamo che la inserisca e attuiamo la modifica all'interno del contatto.
	 */
	if( risposta_utente == SCELTA_INSERIRE_NOMINATIVO ){
		//Per la modifica del nominativo, verifichiamo che tale stringa non sia vuota.
		spostare_cursore(RIGA_NOMINATIVO_INSERIMENTO, COLONNA_INPUT_UTENTE);
		scanf(" %[^\n]s", stringa_input);
		nominativo = convertire_stringa(stringa_input);
		if( leggere_lunghezza_stringa( nominativo ) <= LUNGHEZZA_MINIMA_STRINGA ){
			scrivere_errore_contatto( &contatto_modificato, CODICE_ERRORE_NOMINATIVO_CONTATTO);
		}else{
			scrivere_nominativo_contatto(&contatto_modificato, nominativo );
			errore = CODICE_CORRETTO;
		}
	} else if( risposta_utente == SCELTA_INSERIRE_N_TELEFONO ){
		spostare_cursore(RIGA_N_TELEFONO_INSERIMENTO, COLONNA_INPUT_UTENTE);
		scanf(" %s", stringa_input);
		scrivere_n_telefono_contatto(&contatto_modificato, convertire_stringa(stringa_input));
	} else if( risposta_utente == SCELTA_INSERIRE_STATO ){
		spostare_cursore(RIGA_STATO_INSERIMENTO, COLONNA_INPUT_UTENTE);
		scanf(" %c", &stato);
		scrivere_stato_contatto( &contatto_modificato, convertire_in_intero(stato) );
	}
	//Modifico il contatto all'interno della rubrica.
	modificare_contatto_rubrica( rubrica, contatto_acquisito, contatto_modificato );
	//Se la precedente istruzione ha generato errore, allora devo informare l'utente.
	errore = leggere_errore_rubrica( *rubrica );
	if( errore == CODICE_CORRETTO ){
		//Se l'errore non è avvenuto, allora informo l'utente della buona riuscita della modifica.
		gestire_messaggi_utente(MESSAGGIO_MODIFICA_CORRETTA);
		pulire_schermata(RIGA_TESTO,COLONNA_TESTO, RIGA_TESTO, COLONNE_MASSIME_SCHERMO-2);
	}else{
		//Se l'errore è avvenuto, informo l'utente con il messaggio d'errore corrispondente.
		gestire_messaggi_utente( errore );
		scrivere_errore_rubrica( rubrica, CODICE_CORRETTO );
	}
}

//Funzione di modifica di un contatto in rubrica, fornito il nominativo e l'informazione da modificare in input.
void modificare_contatto_rubrica_input( Rubrica *rubrica )
{
	char stringa_input[20];			//Stinga acquisita in input (utilizzata per nominativo e numero telefono.
	char risposta_utente;			//Risposta dell'utente a seguito della visualizzazione del messaggio.
	Contatto contatto_acquisito;	//Contatto acquisito con le informazioni fornite dall'utente.
	int posizione;					//Posizione del contatto acquisito all'interno della rubrica.
	do{
		stampare_layout_interfaccia(PERCORSO_INTERFACCIA_RICERCARE_CONTATTO);
		//Puliamo la schermata prima della ricerca di un contatto
		pulire_schermata(RIGA_VISUALIZZARE_CONTATTO,COLONNA_VISUALIZZARE_NOMINATIVO, RIGA_VISUALIZZARE_CONTATTO, COLONNA_FINE_NOMINATIVO);
		pulire_schermata(RIGA_VISUALIZZARE_CONTATTO,COLONNA_VISUALIZZARE_N_TELEFONO, RIGA_VISUALIZZARE_CONTATTO, COLONNA_FINE_N_TELEFONO);
		pulire_schermata(RIGA_VISUALIZZARE_CONTATTO,COLONNA_VISUALIZZARE_STATO, RIGA_VISUALIZZARE_CONTATTO, COLONNA_FINE_STATO);
		pulire_schermata(RIGA_NOMINATIVO_INSERIMENTO,COLONNA_INPUT_UTENTE, RIGA_NOMINATIVO_INSERIMENTO, COLONNE_MASSIME_SCHERMO-2);
		pulire_schermata(RIGA_INPUT_UTENTE,COLONNA_INPUT_UTENTE, RIGA_INPUT_UTENTE, COLONNE_MASSIME_SCHERMO-2);

		//Inizializziamo il contatto da ricercare
		inizializzare_contatto_rubrica(&contatto_acquisito);
		//Posizionamento sullo schermo alla riga di acquisizione nominativo del contatto.
		spostare_cursore(RIGA_NOMINATIVO_INSERIMENTO, COLONNA_INPUT_UTENTE);
		//Acquisizione dei dati dell'utente.
		scanf(" %[^\n]s", stringa_input);
		//Scrittura del nominativo acquisito in input.
		scrivere_nominativo_contatto(&contatto_acquisito, convertire_stringa(stringa_input) );
		//Ricerco il contatto inserito dall'utente che si intende modificare.
		posizione = cercare_contatto_rubrica( *rubrica, contatto_acquisito );
		//Verifio che sia stato trovato, o che sia avvenuto un errore.
		if ( posizione >= CODICE_CORRETTO ){
			//In caso sia stato trovato, allora recupero il contatto dalla rubrica.
			copiare_contatto( &contatto_acquisito, leggere_contatto_rubrica(*rubrica, posizione) );
			//E richiamo la funzione di modifica di uno dei parametri del contatto.
			acquisire_informazioni_modifica( rubrica, contatto_acquisito, posizione );
		}else{
			//Se il contatto che si intende modificare non dovesse essere stato trovato, o in caso di errore, visualizzo il messaggio.
			visualizzare_errore_utente(posizione);
		}
		//A seguito dell'operazione, reimposto la scritta di uscita per l'utente.
		pulire_schermata(RIGA_INPUT_UTENTE-1,COLONNA_TESTO, RIGA_INPUT_UTENTE, COLONNE_MASSIME_SCHERMO-2);
		pulire_schermata(RIGA_TESTO,COLONNA_TESTO, RIGA_TESTO, COLONNE_MASSIME_SCHERMO-2);
		spostare_cursore(RIGA_INPUT_UTENTE, COLONNA_TESTO);
		stampare_a_schermo_messaggio(MESSAGGIO_CONTINUA_ESCI);
		do{
			//Attendo che l'utente visualizzi il messaggio e decida come continuare.
			pulire_schermata(RIGA_INPUT_UTENTE,COLONNA_INPUT_UTENTE, RIGA_INPUT_UTENTE, COLONNE_MASSIME_SCHERMO-2);
			spostare_cursore(RIGA_INPUT_UTENTE, COLONNA_INPUT_UTENTE);
			scanf(" %c", &risposta_utente);
			pulire_buffer_input();
		}while ( risposta_utente != CARATTERE_USCITA && risposta_utente != CARATTERE_CONTINUA );
		//Resto nell'operazione di modifica fino a quando l'utente non vuole uscire (Ditigando 'e').
	}while( risposta_utente != CARATTERE_USCITA );
	return;
}

//Funzione di visualizzazione del menù.
void visualizzare_guida()
{
	char risposta_utente;	//Risposta dell'utente a seguito della visualizzazione del messaggio.
	do{
		//Mostro il layout principale che permette la scelta della funzione di cui si vuole sapere di più di una funzionalità.
		stampare_layout_interfaccia(PERCORSO_GUIDA);
		//Puliamo la schermata della scelta utente.
		pulire_schermata(RIGA_INPUT_UTENTE,COLONNA_INPUT_UTENTE, RIGA_INPUT_UTENTE, COLONNE_MASSIME_SCHERMO-2);
		spostare_cursore(RIGA_INPUT_UTENTE, COLONNA_INPUT_UTENTE);
		//Attendiamo la rispsota dell'utente.
		scanf("%c", &risposta_utente);
		//Richiamo la funzione di pulizia del buffer di sistema, per evitare errori di acquisizione input.
		pulire_buffer_input();

		//Filtriamo la risposta dell'utente e visualizziamo la pagina corretta in base alla scelta dell'utente.
		if ( risposta_utente >= SCELTA_INSERIRE_CONTATTO && risposta_utente <= SCELTA_MODIFICARE_CONTATTO ){
			if( risposta_utente == SCELTA_INSERIRE_CONTATTO ){
				stampare_layout_interfaccia(PERCORSO_GUIDA_INSERIMENTO);
			} else if( risposta_utente == SCELTA_ELIMINARE_CONTATTO ){
				stampare_layout_interfaccia(PERCORSO_GUIDA_ELIMINARE);
			} else if( risposta_utente == SCELTA_RICERCARE_CONTATTO ){
				stampare_layout_interfaccia(PERCORSO_GUIDA_RICERCARE);
			} else if( risposta_utente == SCELTA_ORDINARE_RUBRICA ){
				stampare_layout_interfaccia(PERCORSO_GUIDA_ORDINARE);
			} else if( risposta_utente == SCELTA_VISUALIZZARE_RUBRICA ){
				stampare_layout_interfaccia(PERCORSO_GUIDA_VISUALIZZARE);
			} else if( risposta_utente == SCELTA_ESPORTARE_RUBRICA ){
				stampare_layout_interfaccia(PERCORSO_GUIDA_ESPORTARE);
			} else if( risposta_utente == SCELTA_IMPORTARE_RUBRICA ){
				stampare_layout_interfaccia(PERCORSO_GUIDA_IMPORTARE);
			} else if( risposta_utente == SCELTA_MODIFICARE_CONTATTO ){
				stampare_layout_interfaccia(PERCORSO_GUIDA_MODIFICARE);
			}
			do{
				//Attendo che l'utente visualizzi il testo e voglia tornare indietro.
				pulire_schermata(RIGA_INPUT_UTENTE,COLONNA_INPUT_UTENTE, RIGA_INPUT_UTENTE, COLONNE_MASSIME_SCHERMO-2);
				spostare_cursore(RIGA_INPUT_UTENTE, COLONNA_INPUT_UTENTE);
				//Attendo la rispsota di continua.
				scanf(" %c", &risposta_utente);
				pulire_buffer_input();
			}while ( risposta_utente != CARATTERE_CONTINUA );
		}
		//Torno al menù princiaple fino a quando non digita esci.
	} while ( risposta_utente != CARATTERE_USCITA );
}

//Funzione che mostra il menù con tutte le funzionalità del programma.
void mostrare_menu()
{
	char risposta_utente; 	//Risposta dell'utente a seguito della visualizzazione del messaggio.
	Rubrica rubrica;		//Rubrica sulla quale lavora il programma.

	//Impostiamo la rubrica con i parametri base affinchè possa essere utilizzata.
	scrivere_numero_contatti_rubrica(&rubrica,NUMERO_MINIMO_CONTATTI);
	scrivere_errore_rubrica(&rubrica,CODICE_CORRETTO);
	do{
		//Stiampiamo l'interfaccia principale del programma(Il Menù).
		stampare_layout_interfaccia(PERCORSO_INTERFACCIA_MENU);
		pulire_schermata(RIGA_INPUT_UTENTE,COLONNA_INPUT_UTENTE, RIGA_INPUT_UTENTE, COLONNE_MASSIME_SCHERMO-2);
		spostare_cursore(RIGA_INPUT_UTENTE, COLONNA_INPUT_UTENTE);
		//Attendiamo che l'utente scelta la funzionalità da richiamare, e richiamiamo la rispettiva funzione che la soddisfa.
		scanf("%c", &risposta_utente);
		//Richiamo la funzione di pulizia del buffer di sistema, per evitare errori di acquisizione input.
		pulire_buffer_input();
		if( risposta_utente == SCELTA_INSERIRE_CONTATTO ){
			//Funzione di acquisizione di un contatto da mettere in rubrica.
			acquisire_contatto_input(&rubrica);
		} else if( risposta_utente == SCELTA_ELIMINARE_CONTATTO ){
			//Funzione di eliminazione di un contatto in rubrica.
			eliminare_contatto_input(&rubrica);
		} else if( risposta_utente == SCELTA_RICERCARE_CONTATTO ){
			//Funzione di visualizzazione di un contatto cercato in rubrica.
			ricercare_contatto_input(rubrica);
		} else if( risposta_utente == SCELTA_ORDINARE_RUBRICA ){
			//Funzione di ordinamento della rubrica.
			ordinare_rubrica_input(&rubrica);
		} else if( risposta_utente == SCELTA_VISUALIZZARE_RUBRICA ){
			//Funzione visualizzazione contatti in rubrica.
			visualizzare_rubrica_input(rubrica);
		} else if( risposta_utente == SCELTA_ESPORTARE_RUBRICA ){
			//Funzione di esportazione della rubrica.
			esportare_rubrica_input(rubrica);
		} else if( risposta_utente == SCELTA_IMPORTARE_RUBRICA ){
			//Funzione importazione della rubrica.
			importare_rubrica_input(&rubrica);
		} else if( risposta_utente == SCELTA_MODIFICARE_CONTATTO ){
			//Funzione di modifica di un contatto in rubrica.
			modificare_contatto_rubrica_input(&rubrica);
		} else if( risposta_utente == SCELTA_VISUALIZZARE_MANUALE_UTENTE ){
			//Funzione di visualizzazione del manuale d'uso/guida del programma.
			visualizzare_guida();
		}
		//Resto nella funzione di ricerca fino a quando l'utente non vuole uscire (Ditigando 'e').
	} while ( risposta_utente != CARATTERE_USCITA );
	return;
}

