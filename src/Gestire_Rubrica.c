/*
 * ============================================================================
 * Nome        : Gestire_Rurbica.c
 * Autore      : Gruppo 3
 * Descrizione : Modulo per la gestione della rubrica del programma.
 * ============================================================================
 */

#include "Gestire_Rubrica.h"

//Funzione di inserimento di un contatto in rubrica.
void inserire_contatto_rubrica( Rubrica *rubrica, Contatto contatto )
{
	int errore;		//Variabile ausiliaria per i controlli sulle strutture dati.
	int posizione; 	//Posizione in cui inserire il nuovo contatto all'interno della rubrica.
	//Controllo che la struttura rubrica ed il contatto da inserire non presentino errori nei campi che li compongono.
	errore = controllare_correttezza_rubrica( *rubrica );
	if( errore == CODICE_CORRETTO ){
		errore = controllare_correttezza_contatto( contatto );
	}
	if( errore != CODICE_CORRETTO){
		scrivere_errore_rubrica( rubrica, errore );
	} else{
		//Se la ricerca non genera un errore o CODICE_CONTATTO_NON_TROVATO, Inserisco il contatto nell'ultima posizione della rubrica.
		if( cercare_contatto_rubrica( *rubrica, contatto ) == CODICE_ERRORE_CONTATTO_NON_TROVATO ){
			posizione = leggere_numero_contatti_rubrica( *rubrica ) + 1 ;
			scrivere_contatto_rubrica( rubrica, posizione-1, contatto );
			scrivere_numero_contatti_rubrica( rubrica, posizione );
		} else{
			//Se il contatto già esiste o rilevo l'errore, segnalo tale avvenimento nell'apposito campo errore della struttura dati Rubrica.
			scrivere_errore_rubrica( rubrica, CODICE_ERRORE_DUPLICATO_RUBRICA );
		}
	}
	return;
}

//Funzione di eliminazione di un contatto in rubrica.
void eliminare_contatto_rubrica( Rubrica *rubrica, int posizione )
{
	int errore; //Variabile ausiliaria per i controlli sulle strutture dati.
	//Controllo che la struttura rubrica non presenti errori nei campi che di cui si compone.
	errore = controllare_correttezza_rubrica( *rubrica );
	if( errore != CODICE_CORRETTO ){
		scrivere_errore_rubrica( rubrica, errore );
	} else{
		//Controllo che la posizione di cui eleminare l'elemento sia coerente con la struttura dati, e con il numero di contatti presenti.
		if( posizione  >= CODICE_CORRETTO && posizione < leggere_numero_contatti_rubrica( *rubrica ) ){
			//Se tutto è corretto, sposto ogni contatto in posizione i, nella posizione precedente ad i, sovrascrivendo quello da eliminare.
			while( posizione < leggere_numero_contatti_rubrica( *rubrica ) - 1 ){
				scrivere_contatto_rubrica( rubrica, posizione, leggere_contatto_rubrica( *rubrica, posizione + 1 ) );
				posizione = posizione + 1;
			}
			//Ed in fine, diminiusco di 1 il numero di contatti in rubrica, in quanto ho eliminato correttamente il contatto in posizione.
			scrivere_numero_contatti_rubrica( rubrica, leggere_numero_contatti_rubrica( *rubrica ) - 1 );
		} else{
			//Segnalo l'errore in caso il controllo sulla posizione in input.
			scrivere_errore_rubrica( rubrica, CODICE_ERRORE_CONTATTO_NON_TROVATO );
		}
	}
	return;
}

//Funzione di modifica di un contatto in rubrica.
void modificare_contatto_rubrica( Rubrica *rubrica, Contatto contatto_precedente, Contatto contatto_modificato )
{
	int errore; 						//Variabile ausiliaria per i controlli sulle strutture dati.
	int posizione; 						//Posizione del contatto da modificare in rubrica.
	/*
	 * Variabile per il controllo di univocità del nominativo:
	 * Se la modifica del contatto riguarda il nominativo, devo verificare che il nuovo nominativo non esista già in rubrica.
	 * Questa variabile ha lo scopo di segnalare se la modifica riguarda il nominativo.
	 */
	bool esito_controllo_nominativi;

	//Controllo che la struttura rubrica non presenti errori nei campi che di cui si compone.
	errore = controllare_correttezza_rubrica( *rubrica );
	if( errore == CODICE_CORRETTO ){
		errore = controllare_correttezza_contatto( contatto_modificato );
	}
	if( errore != CODICE_CORRETTO ){
		scrivere_errore_rubrica( rubrica, errore );
	} else{
		//Se non vi sono errori, ricerco il contatto in rubrica.
		posizione = cercare_contatto_rubrica( *rubrica, contatto_precedente );
		/*
		 * Se la posizione trovata è un valore maggiore o uguale a 0, il contatto è stato trovato e procediamo nel sovrascriverlo con quello
		 * modificato. Altrimenti, è avvenuto un errore, o il valore di posizione è:CODICE_ERRORE_CONTATTO_NON_TROVATO, nel caso in cui
		 * il contatto da modificare non esista. In caso, segnaliamo l'errore nel campo errore di Rubrica.
		 */
		if( posizione >= CODICE_CORRETTO  ){
			//Controllo se il parametro da modificare è il nominativo.
			esito_controllo_nominativi = verificare_uguaglianza_stringhe(leggere_nominativo_contatto(contatto_precedente), leggere_nominativo_contatto(contatto_modificato));
			/*
			 * Se tale variabile è vera, allora i nominativi dei due contatti sono uguali,
			 * quindi la modifica sarà di campi che non riguardano il nominativo.
			 * Per tanto mi limito a sovrascrivere il contatto con i nuovi dati.
			 */
			if (  esito_controllo_nominativi == true){
				scrivere_contatto_rubrica( rubrica, posizione, contatto_modificato );
			} else{
				//Altrimenti verifico che non vi sia un altro contatto con il nominativo che si intende modificare.
				if(cercare_contatto_rubrica(*rubrica, contatto_modificato) >= CODICE_CORRETTO){
					//Se esiste, allora la modifica non può essere compiuta, comunico l'errore.
					scrivere_errore_rubrica( rubrica, CODICE_ERRORE_DUPLICATO_RUBRICA );
				}else{
					//Altrimenti, procedo modificando il contatto.
					scrivere_contatto_rubrica( rubrica, posizione, contatto_modificato );
				}
			}
		} else{
			//Segnalo l'errore avvenuto nel corrispondente campo errore della struttura dati Rubrica, se esso è stato rilevato.
			scrivere_errore_rubrica( rubrica, CODICE_ERRORE_CONTATTO_NON_TROVATO );
		}
	}
	return;
}

/*
 * Funzione di confronto lessicografico di due contatti in rubrica.
 * Restituisce un intero indicante contatto con il nominativo lessicograficamente minore.
 * CODICE_CORRETTO: Non è avvenuto nessun errore ed i due contatti sono uguali.
 * ORDINAMENTO_CRESCENTE: Il secondo contatto è maggiore del primo.
 * ORDINAMENTO_DECRESCENTE: Il primo contatto è maggiore del secondo.
 */
int confrontare_contatti(Contatto contatto_uno, Contatto contatto_due)
{
    int errore;  			//Variabile ausiliaria per i controlli sulle strutture dati.
    int lunghezza_stringa;  //Variabile per determinare il contatto con la lunghezza del nominativo minore dei due.
    bool trovato_maggiore;  //Indica se ho trovato il contatto maggiore fra i due.
    /*
     * Indica quale dei due è maggiore:
     * ORDINAMENTO_CRESCENTE: Il primo è il minore, ovvero essi sono già disposti in maniera crescente.
     * ORDINAMENTO_DECRESCENTE: Il secondo è il minore, ovvero essi sono disposti in maniera decrescente.
     * Valore di errore se è stato rilevato un errore nei controlli.
     */
    int contatto_maggiore;
    int i;  							//Variabile ausiliaria per scorrere i caratteri della stringa.
    Stringa nominativo_contatto_uno;  	//Stringa ausiliaria per il nominativo del primo contatto.
    Stringa nominativo_contatto_due;  	//Stringa ausiliaria per il nominativo del secondo contatto.
    char carattere_uno; 				//Carattere letto dal primo nominativo.
    char carattere_due; 				//Carattere letto dal secondo nominativo.
    //Controllo che i due contatti non presentino errori nei campi.
    errore = controllare_correttezza_contatto(contatto_uno);
    if ( errore == CODICE_CORRETTO ) {
        errore = controllare_correttezza_contatto(contatto_due);
    }
    //Se non vi sono errori procedo trovando il contatto maggiore.
    if ( errore == CODICE_CORRETTO ) {
        //Leggo i nominativi dei due contatti da confrontare.
        nominativo_contatto_uno = leggere_nominativo_contatto(contatto_uno);
        nominativo_contatto_due = leggere_nominativo_contatto(contatto_due);
        //Ricavo quale dei due ha la lunghezza della stringa minore.
        if (leggere_lunghezza_stringa(nominativo_contatto_uno) > leggere_lunghezza_stringa(nominativo_contatto_due)) {
            lunghezza_stringa = leggere_lunghezza_stringa(nominativo_contatto_due);
        } else {
            lunghezza_stringa = leggere_lunghezza_stringa(nominativo_contatto_uno);
        }

        i = 0;
        //Suppongo che nessuno dei due sia maggiore, poichè ho il caso di due contatti uguali.
        trovato_maggiore = false;
        //Suppongo che i due contatti siano uguali.
        contatto_maggiore = CODICE_CORRETTO;
        while (i < lunghezza_stringa && trovato_maggiore == false) {
            /*
             * Confronto carattere per carattere della stringa, alla ricerca del primo carattere diverso fra le due stringhe.
             * Nel farlo, ignoro (scelta implementativa) il fattore CASE SENSITIVE dei caratteri.
             */
            carattere_uno = tolower(leggere_carattere_stringa(nominativo_contatto_uno, i));
            carattere_due = tolower(leggere_carattere_stringa(nominativo_contatto_due, i));

            if (carattere_uno < carattere_due) {
                /*
                 * Se il primo carattere diverso è del nominativo_uno, ed esso risulta minore.
                 * Allora ho trovato che il nominativo del contatto_uno minore.
                 * Quindi segnalo con: trovato_maggiore, che ho trovato chi dei due contatti è il maggiore.
                 * e con contatto_maggiore, chi due due lo è; con precisione:
                 * contatto_maggiore = ORDINAMENTO_CRESCENTE, Allora i contatti sono in ordine crescente già, quindi il primo è già il più piccolo.
                 * contatto_maggiore = ORDINAMENTO_DECRESCENTE Allora i contatti sono in ordine decrescente, il secondo è minore del primo.
                 */
                trovato_maggiore = true;
                contatto_maggiore = ORDINAMENTO_CRESCENTE;
            } else if (carattere_uno > carattere_due) {
            	//Se è vero il confronto inverso (Escludendo l'uguaglianza), allora segnalo il contrario di quanto appena espresso.
                trovato_maggiore = true;
                contatto_maggiore = ORDINAMENTO_DECRESCENTE;
            }
            i = i + 1;
        }
        /*
         * Se a seguito dei controlli, contatto_maggiore è ancora pari a CODICE_CORRETTO, uno dei due contatti è prefisso dell'altro.
         * o sono uguali, Per tanto, il contatto minore sarà quello con lunghezza più piccola!
         * Se la lunghezza risulta la stessa, allora contatto_maggiore varrà CODICE_CORRETTO ovvero i due contatti sono uguali.
         */
        if (contatto_maggiore == CODICE_CORRETTO) {
            if (leggere_lunghezza_stringa(nominativo_contatto_uno) < leggere_lunghezza_stringa(nominativo_contatto_due)) {
                contatto_maggiore = ORDINAMENTO_CRESCENTE;
            } else if (leggere_lunghezza_stringa(nominativo_contatto_uno) > leggere_lunghezza_stringa(nominativo_contatto_due)) {
                contatto_maggiore = ORDINAMENTO_DECRESCENTE;
            }
        }
    } else {
        //Nel caso in cui i contatti presentassero errori nei campi, il parametro contatto_maggiore varrà l'errore trovato nel contatto.
        contatto_maggiore = errore;
    }
    return contatto_maggiore;
}

/*
 * Funzione di ordinamento della rubrica secondo il criterio fornito in input.
 * criterio può assumere i valori:
 * ORDINAMENTO_CRESCENTE Indica che la rubrica verrà ordinate con i nominativi dei contatti
 * disposti in ordine crescente.
 * ORDINAMENTO_DECRESCENTE Ordinamento inverso al precedente.
 */
void ordinare_contatti_rubrica( Rubrica *rubrica, int criterio )
{

	int errore; 				//Indica l'errore nella struttura della rubrica.
	int i; 						//Variabile di supporto per lo scorrimento dei contatti nella rubrica.
	int j; 						//Variabile di supporto per lo scorrimento dei contatti nella rubrica.
	int risultato_confronto; 	//Risultato del confronto dei due contatti scanditi.

	Contatto primo_contatto_confronto; 		//Primo contatto del per l'ordinamento.
	Contatto secondo_contatto_confronto; 	//Secondo contatto del confronto per l'ordinamento.
	Contatto contatto_temporaneo; 			//Contatto su supporto per lo scambio dei contatti in rubrica.

	//Controllo che la rubrica sia corretta prima di proseguire.
	errore = controllare_correttezza_rubrica(*rubrica);

	if( errore != CODICE_CORRETTO ){
		scrivere_errore_rubrica( rubrica, errore );
	} else if( (criterio != ORDINAMENTO_CRESCENTE) && (criterio != ORDINAMENTO_DECRESCENTE ) ){
		scrivere_errore_rubrica( rubrica, CODICE_ERRORE_CRITERIO );
	} else{
		//Se non vi son errori, proseguo con l'ordinamento.
		i = 0;
		//Applichiamo l'algoritmo di ordinamento Bubble Sort.
		while( i < leggere_numero_contatti_rubrica( *rubrica ) ){
			j = 0;
			while( j < ( leggere_numero_contatti_rubrica( *rubrica ) - 1) ){
				//Per ogni passo, acquisiamo la coppia di contatti successivi in posizione j e j+1
				copiare_contatto( &primo_contatto_confronto, leggere_contatto_rubrica( *rubrica, j ));
				copiare_contatto( &secondo_contatto_confronto, leggere_contatto_rubrica( *rubrica, j + 1 ));
				//Confrontiamo tali contatti, e capiamo quale dei due è il minore, salvando il risultato in risultato_confronto
				risultato_confronto = confrontare_contatti( primo_contatto_confronto, secondo_contatto_confronto );
				/*
				 * Se il parametro di confronto risulta minore del codice corretto, allora si è verificato un errore e questo
				 * verrà segnalato nel campo errore della rubrica.
				 */
				if( risultato_confronto < CODICE_CORRETTO  ){
					scrivere_errore_rubrica(rubrica, risultato_confronto );
					/*
					 * Se non vi è un errore, allora controllo il criterio scelto in input:
					 * Se il criterio è ORDINAMENTO_CRESCENTE e il risultato del confronto è ORDINAMENTO_DECRESCENTE, allora i due contatti
					 * NON SONO in ordine, quindi vanno ordinati.
					 * Ragionamento analogo avviene con ORDINAMENTO_DECRESCENTE e risultato confronto pari a ORDINAMENTO_CRESCENTE.
					 */
				} else if( (criterio == ORDINAMENTO_CRESCENTE && risultato_confronto == ORDINAMENTO_DECRESCENTE)
						|| (criterio == ORDINAMENTO_DECRESCENTE && risultato_confronto == ORDINAMENTO_CRESCENTE) ){
					/*
					 * Eseguo lo scambio dei contatti, salvando il primo in un contatto temporaneo, sovrascrivendo il primo dei due
					 * con il valore del secondo, e scrivendo nel secondo, il valore del primo (salvato nel contatto temporaneo).
					 */
					copiare_contatto(&contatto_temporaneo, primo_contatto_confronto );
					scrivere_contatto_rubrica(rubrica, j, secondo_contatto_confronto );
					scrivere_contatto_rubrica(rubrica, j + 1, contatto_temporaneo );
				}
				j = j + 1;
			}
			i = i + 1;
		}
	}
}

//Funzione di ricerca di un contatto in rubrica
int cercare_contatto_rubrica( Rubrica rubrica, Contatto contatto )
{
	int i; 									//Posizione degli elementi della rubrica.
	int errore; 							//Errore derivante dai controlli.
	bool trovato; 							//Segnala se il contatto trovato è corrispondente a quello richiesto.
	int posizione_contatto_trovato; 		//Posizione del contatto trovato in rubrica.
	Contatto contatto_confronto_rubrica; 	//Contatto letto dalla rubrica, oggetto del confronto.

	//Verifico che la rubrica in cui si esegue la ricerca non presenti errori.
	errore = controllare_correttezza_rubrica( rubrica );
	if( errore == CODICE_CORRETTO ){
		/*
		 * Controllo che anche il contatto cercato non presenti errori, nel caso,
		 * segnalo l'errore trovato nel campo del contatto in output.
		 */
		errore = controllare_correttezza_contatto(contatto);
	}
	if( errore != CODICE_CORRETTO ){
		posizione_contatto_trovato = errore;
	} else{
		i = 0;
		trovato = false;
		//Ricerco per ogni contatto in rubrica (scanditi dalla variabile i).
		while( i < leggere_numero_contatti_rubrica(rubrica) && trovato == false ){
			/*
			 * Per ogni contatto, controllo che abbia senso fare il controllo dell'uguaglianza,
			 * confrontando la lunghezza dei nominativi del contatto letto dalla rubrica nella posizione scandita
			 * ed il contatto fornito in input.
			 */
			copiare_contatto(&contatto_confronto_rubrica,leggere_contatto_rubrica(rubrica,i));
			trovato = verificare_uguaglianza_stringhe( leggere_nominativo_contatto(contatto), leggere_nominativo_contatto(contatto_confronto_rubrica) );
			i = i + 1;
		}
	}
	/*
	 * Se trovato è pari a vero, allora ho trovato il contatto durante la ricerca.
	 * Altrimenti, il contatto non è stato trovato, è la risposta in output sarà il codice errore del contatto non trovato.
	 */
	if( trovato == false ){
		posizione_contatto_trovato  = CODICE_ERRORE_CONTATTO_NON_TROVATO;
	}else{
		posizione_contatto_trovato = i - 1;
	}
	return posizione_contatto_trovato;
}
