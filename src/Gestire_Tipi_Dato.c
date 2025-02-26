/*
 * ============================================================================
 * Nome        : Gestire_Tipi_Dato.c
 * Autore      : Gruppo 3
 * Descrizione : Modulo per la gestione dei tipi di dato del programma.
 * ============================================================================
 */

#include "Gestire_Tipi_Dato.h"

// -------------------- FUNZIONI DI ACCESSO STRINGA --------------------
//Lettura del campo lunghezza_stringa di Stringa.
int leggere_lunghezza_stringa( Stringa stringa )
{
	int lunghezza_stringa; //Lunghezza stringa letta.
	lunghezza_stringa = stringa.lunghezza_stringa;
	//Controllo se la lunghezza_stringa si trova fuori dal range accettabile di valori.
	if( lunghezza_stringa < LUNGHEZZA_MINIMA_STRINGA || lunghezza_stringa > LUNGHEZZA_MASSIMA_STRINGA ){
		lunghezza_stringa = CODICE_ERRORE_LUNGHEZZA_STRINGA;
	}
	return lunghezza_stringa;
}

//Scrittura del campo lunghezza_stringa di Stringa.
void scrivere_lunghezza_stringa( Stringa *stringa, int lunghezza_stringa )
{
	//Controllo se la lunghezza_stringa si trova fuori dal range accettabile di valori.
	if ( lunghezza_stringa < LUNGHEZZA_MINIMA_STRINGA || lunghezza_stringa > LUNGHEZZA_MASSIMA_STRINGA ){
		scrivere_errore_stringa( stringa , CODICE_ERRORE_LUNGHEZZA_STRINGA);
	} else {
		stringa->lunghezza_stringa = lunghezza_stringa;
	}
	return;
}

//Lettura di uno dei caratatteri della stringa fornita la posizione.
char leggere_carattere_stringa( Stringa stringa, int posizione )
{
	char carattere_letto;
	/*
	 * Controllo se la posizione del carattere da leggere si trova fuori dal range accettabile di valori
	 * e se la lunghezza della stringa è fuori dal range accettabile.
	 */
	if( posizione < LUNGHEZZA_MINIMA_STRINGA || posizione >= leggere_lunghezza_stringa(stringa)
	|| leggere_lunghezza_stringa(stringa) < LUNGHEZZA_MINIMA_STRINGA || leggere_lunghezza_stringa(stringa) > LUNGHEZZA_MASSIMA_STRINGA){
		carattere_letto = CARATTERE_ERRATO_STRINGA;
	} else{
		carattere_letto = stringa.caratteri_stringa[posizione];
	}
	//Controllo se il carattere letto è fuori dal range di valori corretti dell'alfabeto.
	if( carattere_letto < INIZIO_ALFABETO_ASCII || carattere_letto > FINE_ALFABETO_ASCII ){
		carattere_letto = CARATTERE_ERRATO_STRINGA;
	}
	return carattere_letto;
}

//Scrittura del carattere di una Stringa data la posizione.
void scrivere_carattere_stringa( Stringa *stringa, int posizione, char carattere_da_scrivere )
{
	/*
	 * Controllo se il carattere da scrivere è fuori dal range di valori corretti.
	 * Controllo se la posizione del carattere da scrivere si trova fuori dal range accettabile di valori
	 * e se la lunghezza della stringa è fuori dal range accettabile. Al fine di intercettare eventuali errori.
	 */
	if( carattere_da_scrivere < INIZIO_ALFABETO_ASCII || carattere_da_scrivere > FINE_ALFABETO_ASCII ){
		scrivere_errore_stringa( stringa , CODICE_ERRORE_CARATTERE_STRINGA);
	}else if( posizione < LUNGHEZZA_MINIMA_STRINGA || posizione > leggere_lunghezza_stringa( *stringa )
	|| leggere_lunghezza_stringa(*stringa) <= LUNGHEZZA_MINIMA_STRINGA || leggere_lunghezza_stringa( *stringa ) > LUNGHEZZA_MASSIMA_STRINGA){
		scrivere_errore_stringa( stringa , CODICE_ERRORE_LUNGHEZZA_STRINGA);
	} else {
		//Se non vi sono errori, scrivo il carattere all'interno della stringa.
		stringa->caratteri_stringa[posizione] = carattere_da_scrivere;
	}
	return;
}

//Lettura del campo errore della struttura Stringa.
int leggere_errore_stringa ( Stringa stringa )
{
	int errore; //Parametro di errore letto dal campo errore.
	errore = stringa.errore_stringa;
	//Verifico sia un errore noto, all'interno del range di quelli definiti per il tipo di dato corrispondente.
	if( errore < CODICE_ERRORE_CRITERIO || errore > CODICE_CORRETTO ){
		errore = CODICE_ERRORE_ERRATO;
	}
	return errore;
}
//Scrittura del campo errore della struttura Stringa.
void scrivere_errore_stringa ( Stringa *stringa, int errore){
	//Verifico sia un errore noto, all'interno del range di quelli definiti per il tipo di dato corrispondente.
	if( errore < CODICE_ERRORE_CRITERIO || errore > CODICE_CORRETTO ){
		errore = CODICE_ERRORE_ERRATO;
	}else{
		stringa->errore_stringa = errore;
	}
	return;
}

// -------------------- FUNZIONI DI CONTROLLO STRINGA --------------------
//Controlla che la stringa sia corretta.
int controllare_correttezza_stringa( Stringa stringa )
{
	int errore;		//Errore rilevato durante i controlli.
	int i;			//Variabile ausiliaria per scorrere gli elementi della stringa.
	char carattere;	//Carattere letto dalla stringa durante lo scorrimento.

	//Verifico che il campo errore non sia errato.
	errore = leggere_errore_stringa(stringa);
	if ( errore == CODICE_CORRETTO ){
		//Controllo sulla lunghezza della stringa
		if( leggere_lunghezza_stringa(stringa) < LUNGHEZZA_MINIMA_STRINGA || leggere_lunghezza_stringa(stringa) > LUNGHEZZA_MASSIMA_STRINGA ){
			errore = CODICE_ERRORE_LUNGHEZZA_STRINGA;
		}else{
			i = 0;
			//Controllo sui caratteri che la stringa contiene.
			while( i < leggere_lunghezza_stringa(stringa) && errore == CODICE_CORRETTO ){
				carattere = leggere_carattere_stringa( stringa, i );
				if( carattere < INIZIO_ALFABETO_ASCII  || carattere > FINE_ALFABETO_ASCII ){
					errore = CODICE_ERRORE_CARATTERE_STRINGA;
				}
				i = i + 1;
			}
		}
	}
	return errore;
}

/*
 * Tale funzione converte una stringa acquisita in input, in una struttura Stringa
 * definita dalla logica del programma.
 */
Stringa convertire_stringa( char stringa[] )
{
	int i;						//Scandisce gli elementi della stringa acquisita, e sarà la dimensione della stringa convertita.
	char carattere;				//Acquisisce il carattere scandito dalla stringa acquisita.
	Stringa stringa_convertita; //Stringa in output, copia della stringa in input ma di tipo Stringa(struttura definita dal programma).

	//Imposto i parametri predefiniti della stringa da fornire in output.
	scrivere_lunghezza_stringa(&stringa_convertita, LUNGHEZZA_MASSIMA_STRINGA);
	scrivere_errore_stringa(&stringa_convertita, CODICE_CORRETTO);
	i = 0;
	//Scandisco gli elementi della stringa copiando ogni elemento nella nuova stringa.
	while ( (carattere = stringa[i]) != '\0' ){
		//In caso di errore, la funzione scrivere_carattere_stringa, valorizzerà il campo errore della stringa.
		scrivere_carattere_stringa(&stringa_convertita, i, carattere );
		i = i + 1;
	}
	//Imposto la lunghezza calcolata.
	scrivere_lunghezza_stringa(&stringa_convertita, i);
	return stringa_convertita;
}


// -------------------- FUNZIONI DI ACCESSO CONTATTO --------------------
//Lettura del campo stato della struttura Contatto.
int leggere_stato_contatto( Contatto contatto )
{
	int stato_letto;
	stato_letto  = contatto.stato_contatto;
	//Controllo se lo stato_letto è fuori dal range accettabile di valori.
	if ( stato_letto < STATO_PREDEFINITO || stato_letto > STATO_BLOCCATO ){
		stato_letto = CODICE_ERRORE_STATO_CONTATTO;
	}
	return stato_letto;
}
//Scrittura del campo stato della struttura Contatto.
void scrivere_stato_contatto( Contatto *contatto, int stato ){
	//Controllo se lo stato_letto è fuori dal range accettabile di valori.
	if ( stato < STATO_PREDEFINITO || stato > STATO_BLOCCATO ){
		scrivere_errore_contatto( contatto , CODICE_ERRORE_STATO_CONTATTO);
	} else{
		contatto->stato_contatto = stato;
	}
	return;
}

//Lettura del campo nominativo della struttura Contatto
Stringa leggere_nominativo_contatto( Contatto contatto )
{
	Stringa nominativo; 		//Variabile ausiliare per copiare il nominativo letto.
	int i; 						//Indice per scorrere gli elementi del nominativo.
	int errore; 				//Codice di errore dei controlli sul nominativo del contatto.
	char carattere; 			//Carattere letto del nominativo.
	int lunghezza_nominativo;	//Lunghezza del campo nominativo.

	//Imposto lo stato dell'errore sulla nuova stringa nominativo dichiarata.
	scrivere_errore_stringa( &nominativo, CODICE_CORRETTO );
	//Eseguo i controlli sulla stringa da leggere.
	errore = CODICE_CORRETTO;
	//Controllo che la lunghezza sia nel range dei valori definito.
	lunghezza_nominativo = leggere_lunghezza_stringa( contatto.nominativo_contatto );
	if( lunghezza_nominativo < LUNGHEZZA_MINIMA_STRINGA || lunghezza_nominativo > LUNGHEZZA_MASSIMA_STRINGA ){
		errore = CODICE_ERRORE_LUNGHEZZA_STRINGA;
	} else{
		//Se la lunghezza è corretta, la imposto al nominativo prima di procedere.
		scrivere_lunghezza_stringa( &nominativo, lunghezza_nominativo );
	}

	i = 0;
	//Controllo che ogni carattere letto, sia corretto (Nel range definito), altrimenti segnalo l'errore nel campo errore apposito.
	while( i < lunghezza_nominativo && errore == CODICE_CORRETTO ){
		carattere = leggere_carattere_stringa( contatto.nominativo_contatto, i );
		if( carattere < INIZIO_ALFABETO_ASCII || carattere > FINE_ALFABETO_ASCII ){
			errore = CODICE_ERRORE_CARATTERE_STRINGA;
		} else{
			scrivere_carattere_stringa( &nominativo, i, carattere );
		}
			i = i + 1;
	}
	//Se ci sono errori setto il campo errore del nominativo.
	if( errore != CODICE_CORRETTO ){
		scrivere_errore_stringa( &nominativo, errore );
	}
	return nominativo;
}

//Scrittura del campo nominativo della struttura Contatto
void scrivere_nominativo_contatto( Contatto *contatto, Stringa nominativo )
{
	int i; 			//Indice per scorrere gli elementi del nominativo.
	int errore; 	//Codice di errore dei controlli sul nominativo del contatto.
	char carattere; //Carattere letto del nominativo.
	errore = CODICE_CORRETTO;
	//Controllo se la lunghezza del nominativo è compresa fra gli estremi di definizione.
	if( leggere_lunghezza_stringa(nominativo) < LUNGHEZZA_MINIMA_STRINGA || leggere_lunghezza_stringa(nominativo) > LUNGHEZZA_MASSIMA_STRINGA ){
		errore = CODICE_ERRORE_NOMINATIVO_CONTATTO;
	}else{
		//Se la lunghezza è corretta, la imposto al nominativo prima di procedere.
		scrivere_lunghezza_stringa(&contatto->nominativo_contatto, leggere_lunghezza_stringa(nominativo));
	}
	//Controllo se i caratteri del nominativo sono coerenti con L'alfabeto del nominativo.
	i = 0;
	while( i < leggere_lunghezza_stringa(nominativo) && errore == CODICE_CORRETTO ){
		carattere = leggere_carattere_stringa( nominativo, i );
		if( carattere < INIZIO_ALFABETO_ASCII  || carattere > FINE_ALFABETO_ASCII ){
			errore = CODICE_ERRORE_CARATTERE_STRINGA;
		} else{
			scrivere_carattere_stringa( &(contatto->nominativo_contatto) , i, carattere);
		}
		i = i + 1;
	}
	//Se ci sono errori segnalo l'errore nel campo apposito della struttura.
	if( errore != CODICE_CORRETTO ){
		scrivere_errore_contatto( contatto , errore );
	}
	return;
}

//Lettura del campo numero_telefono della struttura Contatto.
Stringa leggere_n_telefono_contatto( Contatto contatto )
{
	Stringa n_telefono; 			//Variabile ausiliare per copiare il numero di telefono letto.
	int i; 							//Indice per scorrere gli elementi del numero di telefono.
	int errore; 					//Codice di errore dei controlli sul numero di telefono del contatto.
	char carattere; 				//Cifra letta del numero di telefono.
	int lunghezza_numero_telefono; 	//Lunghezza del campo n_telefono_contatto.

	//Imposto lo stato dell'errore sul nuovo numero di telefono dichiarato.
	scrivere_errore_stringa( &n_telefono, CODICE_CORRETTO );
	errore = CODICE_CORRETTO;
	lunghezza_numero_telefono = leggere_lunghezza_stringa( contatto.n_telefono_contatto );
	//Controllo se la lunghezza_numero_telefono è pari a 10 ( LUNGHEZZA_N_TELEFONO ).
	if( lunghezza_numero_telefono != LUNGHEZZA_N_TELEFONO ){
		errore = CODICE_ERRORE_N_TELEFONO_CONTATTO;
	} else{
		//Se la lunghezza è corretta, la imposto al nominativo prima di procedere.
		scrivere_lunghezza_stringa( &n_telefono, lunghezza_numero_telefono );
	}
	//Controllo se i caratteri del numero di telefono sono coerenti con L'alfabeto del numero di telefono.
	i = 0;
	while( i < lunghezza_numero_telefono && errore == CODICE_CORRETTO ){
		carattere = leggere_carattere_stringa( contatto.n_telefono_contatto, i );
		if( carattere < INIZIO_ALFABETO_NUMERI || carattere > FINE_ALFABETO_NUMERI ){
				scrivere_carattere_stringa( &n_telefono, i, CARATTERE_ERRATO_STRINGA );
				errore = CODICE_ERRORE_N_TELEFONO_CONTATTO;
		} else{
				scrivere_carattere_stringa( &n_telefono, i, carattere );
		}
			i = i + 1;
	}
	//Se ci dovessero essere errori, lo segnalo attraverso l'apposito campo errore nella struttura Contatto.
	if( errore != CODICE_CORRETTO ){
		scrivere_errore_stringa( &n_telefono, errore );
	}
	return n_telefono;
}

//Scrittura del campo numero_telefono della struttura Contatto.
void scrivere_n_telefono_contatto( Contatto *contatto, Stringa n_telefono )
{
	int i; 			//Indice per scorrere gli elementi del numero di telefono.
	int errore; 	//Codice di errore dei controlli sul numero di telefono del contatto.
	char carattere; //Cifra letta del numero di telefono.
	errore = CODICE_CORRETTO;
	//Controllo se la lunghezza_numero_telefono è pari a 10 ( LUNGHEZZA_N_TELEFONO ), altrimenti segnalo l'errore nel campo apposito.
	if( leggere_lunghezza_stringa(n_telefono) != LUNGHEZZA_N_TELEFONO ){
		errore = CODICE_ERRORE_N_TELEFONO_CONTATTO;
	}else{
		//Se la lunghezza è pari a 10, allora la imposto prima di proseguire.
		scrivere_lunghezza_stringa(&contatto->n_telefono_contatto, LUNGHEZZA_N_TELEFONO);
	}
	//Controllo se i caratteri del numero di telefono sono coerenti con L'alfabeto del numero di telefono.
	i = 0;
	while( i < leggere_lunghezza_stringa(n_telefono) && errore == CODICE_CORRETTO ){
		carattere = leggere_carattere_stringa( n_telefono, i );
		if( carattere < INIZIO_ALFABETO_NUMERI  || carattere > FINE_ALFABETO_NUMERI ){
			errore = CODICE_ERRORE_N_TELEFONO_CONTATTO;
		} else{
			scrivere_carattere_stringa( &(contatto->n_telefono_contatto) , i, carattere);
		}
		i = i + 1;
	}
	//Se ci dovessero essere errori, lo segnalo attraverso l'apposito campo errore nella struttura Contatto.
	if( errore != CODICE_CORRETTO ){
		scrivere_errore_contatto( contatto , errore );
	}
	return;
}

//Lettura campo errore della struttura Contatto.
int leggere_errore_contatto ( Contatto contatto )
{
	int errore; //Codice di errore letto.
	errore = contatto.errore_contatto;
	if( errore < CODICE_ERRORE_CRITERIO || errore > CODICE_CORRETTO ){
		errore = CODICE_ERRORE_ERRATO;
	}
	return errore;
}
//Scrittura campo errore della struttura Contatto.
void scrivere_errore_contatto ( Contatto *contatto, int errore )
{
	//Controllo che il campo errore inserito non sia errato.
	if( errore < CODICE_ERRORE_CRITERIO || errore > CODICE_CORRETTO ){
		errore = CODICE_ERRORE_ERRATO;
	}else{
		contatto->errore_contatto = errore;
	}
	return;
}

//  -------------------- FUNZIONI CONTROLLO CONTATTO --------------------
//Controlla la correttezza di un contatto nel contesto definito dalla logica del programma.
int controllare_correttezza_contatto( Contatto contatto_da_controllare )
{
	int errore; //Codice di errore dei controlli sul contatto.
	errore = CODICE_CORRETTO;
	/*
	 * Controllo che tutti i campi nell'ordine:
	 * Contatto già errato (campo errore valorizzato).
	 * Errore struttura stringa nominativo | Errore rilevato dalla funzione di lettura del nominativo.
	 * Errore struttura stringa numero telefono | Errore rilevato dalla funzione di lettura del numero telefono.
	 * Errore stato contatto.
	 */
	if( leggere_errore_contatto(contatto_da_controllare) >= CODICE_ERRORE_CRITERIO && leggere_errore_contatto(contatto_da_controllare) < CODICE_CORRETTO ){
		errore = leggere_errore_contatto(contatto_da_controllare);
	}else if(leggere_errore_stringa(leggere_nominativo_contatto(contatto_da_controllare)) < CODICE_CORRETTO){
		errore = CODICE_ERRORE_NOMINATIVO_CONTATTO;
	} else if ( leggere_errore_stringa( leggere_n_telefono_contatto( contatto_da_controllare ) ) < CODICE_CORRETTO ){
		errore = CODICE_ERRORE_N_TELEFONO_CONTATTO;
	} else if (  leggere_stato_contatto( contatto_da_controllare) < STATO_PREDEFINITO || leggere_stato_contatto( contatto_da_controllare) > STATO_BLOCCATO ){
		errore = CODICE_ERRORE_STATO_CONTATTO;
	}
	return errore;
}

//Copia le informazioni di contatto_da_copiare in contatto_output.
void copiare_contatto(Contatto *contatto_output, Contatto contatto_da_copiare )
{
	int errore; //Codice di errore dei controlli sul contatto.
	//Controllo prima che il contatto da copiare sia corretto.
	errore = controllare_correttezza_contatto( contatto_da_copiare );
	//Se il controllo è verificato, allora proseguo nel copiare tutti i campi.
	if( errore == CODICE_CORRETTO ){
		scrivere_nominativo_contatto( contatto_output, leggere_nominativo_contatto(contatto_da_copiare) );
		scrivere_n_telefono_contatto( contatto_output, leggere_n_telefono_contatto(contatto_da_copiare) );
		scrivere_stato_contatto( contatto_output, leggere_stato_contatto(contatto_da_copiare) );
		scrivere_errore_contatto( contatto_output, leggere_errore_contatto(contatto_da_copiare) );
	} else{
		//Altrimenti segnalo l'errore nell'apposito campo errore del contatto.
		scrivere_errore_contatto( contatto_output, errore );
	}
	return;
}

// -------------------- FUNZIONI ACCESSO RUBRICA --------------------
//Lettura del campo numero_contatti di rubrica.
int leggere_numero_contatti_rubrica( Rubrica rubrica )
{
	int numero_contatti;
	numero_contatti = rubrica.numero_contatti_rubrica;
	//Controllo che il numero dei contatti letto sia nel range di validità, altrimenti segnalo l'errore in output.
	if( numero_contatti < NUMERO_MINIMO_CONTATTI || numero_contatti  > NUMERO_MASSIMO_CONTATTI ){
		numero_contatti = CODICE_ERRORE_LUNGHEZZA_RUBRICA;
	}
	return numero_contatti;
}

//Scrittura del campo numero_contatti di rubrica.
void scrivere_numero_contatti_rubrica( Rubrica *rubrica, int numero_contatti )
{
	//Controllo che il numero dei contatti in input sia nel range di validità, altrimenti segnalo l'errore in output.
	if( numero_contatti < NUMERO_MINIMO_CONTATTI || numero_contatti > NUMERO_MASSIMO_CONTATTI ){
		scrivere_errore_rubrica( rubrica, CODICE_ERRORE_LUNGHEZZA_RUBRICA );
	} else{
		rubrica->numero_contatti_rubrica = numero_contatti;
	}
	return;
}

//Lettura del contatto di una rubrica fornita una posizione all'interno della rubrica.
Contatto leggere_contatto_rubrica( Rubrica rubrica, int posizione )
{
	Contatto contatto_letto; //Contatto letto in posizione posizione.
	int errore;
	//Controllo che la posizione fornita sia coerente con la struttura, altrimenti segnalo l'errore sul contatto fornito in output.
	if( posizione < NUMERO_MINIMO_CONTATTI || posizione >= leggere_numero_contatti_rubrica(rubrica) ){
		errore = CODICE_ERRORE_LUNGHEZZA_STRINGA;
		scrivere_errore_contatto( &contatto_letto, errore );
	} else{
		//"Shallow Copy" del contatto, copio in un altro dato differente, le informazioni di quello all'interno della rubrica.
		copiare_contatto( &contatto_letto, rubrica.contatti_rubrica[posizione]);
	}
	return contatto_letto;
}

//Scrittura di un contatto in rubrica fornita una posizione.
void scrivere_contatto_rubrica( Rubrica *rubrica, int posizione, Contatto contatto )
{
	int errore; //Codice di errore dei controlli sul contatto.
	//Controllo che la struttura dati in cui devo scrivere il contatto sia corretta.
	errore = controllare_correttezza_rubrica(*rubrica);
	if( errore == CODICE_CORRETTO ){
		//Controllo che la posizione in cui scrivere il dato sia coerente con la struttura Rubrica.
		if ( (posizione < NUMERO_MINIMO_CONTATTI || posizione > leggere_numero_contatti_rubrica(*rubrica) )
		&& posizione >= NUMERO_MASSIMO_CONTATTI ){
			errore = CODICE_ERRORE_LUNGHEZZA_RUBRICA;
		} else{
			errore = controllare_correttezza_contatto(contatto);
		}
	}
	//Se i controlli danno esito positivo, copio il contatto in rubrica, altrimenti segnalo l'errore nell'apposito campo della rubrica.
	if ( errore != CODICE_CORRETTO ){
		scrivere_errore_rubrica( rubrica, CODICE_ERRORE_LUNGHEZZA_RUBRICA );
	}else{
		copiare_contatto( &(rubrica->contatti_rubrica[posizione]), contatto);
	}
	return;
}

//Lettura campo errore di rubrica.
int leggere_errore_rubrica ( Rubrica rubrica )
{
	int errore; //Codice di errore dei controlli sul contatto.
	errore = rubrica.errore_rubrica;
	//Controllo che l'errore sia uno fra i valori accettabili.
	if( errore < CODICE_ERRORE_CRITERIO || errore > CODICE_CORRETTO ){
		errore = CODICE_ERRORE_ERRATO;
	}
	return errore;
}

//Scrittura campo errore di rubrica.
void scrivere_errore_rubrica ( Rubrica *rubrica, int errore )
{
	//Controllo che l'errore sia uno fra i valori accettabili.
	if( errore < CODICE_ERRORE_CRITERIO || errore > CODICE_CORRETTO ){
		errore = CODICE_ERRORE_ERRATO;
	}else{
		rubrica->errore_rubrica = errore;
	}
	return;
}

// -------------------- FUNZIONI CONTROLLO RUBRICA --------------------
//Controllo che la struttura rubrica sia coerente alla definizione, ed assieme ad essa ogni singolo contatto al suo interno.
int controllare_correttezza_rubrica( Rubrica rubrica )
{
	int i;						//Scandisce i contatti all'interno della rubrica.
	int errore;					//Individua eventuali errori sulla rubrica o sui contatti controllati.
	Contatto contatto_letto;	//Contatto letto scandendo la rubrica.

	//Controllo sul numero massimo di contatti.
	if( leggere_numero_contatti_rubrica(rubrica) < NUMERO_MINIMO_CONTATTI
			|| leggere_numero_contatti_rubrica(rubrica) > NUMERO_MASSIMO_CONTATTI ){
		errore = CODICE_ERRORE_LUNGHEZZA_RUBRICA;
	} else{
		i = 0;
		errore = CODICE_CORRETTO;
		//Controllo su ogni contatto in rubrica.
		while( i < leggere_numero_contatti_rubrica(rubrica) && errore == CODICE_CORRETTO ){
			copiare_contatto( &contatto_letto, leggere_contatto_rubrica(rubrica, i) ) ;
			errore = controllare_correttezza_contatto( contatto_letto );
			i = i + 1;
		}
	}
	//Se non vi sono errori, il campo errore restituito in output sarà CODICE_CORRETTO, altrimenti CODICE_ERRORE_CONTATTI_RUBRICA.
	if( errore != CODICE_CORRETTO ){
		errore = CODICE_ERRORE_CONTATTI_RUBRICA;
	}
	return errore;
}

//Funzione di inizializzazione di un contatto predefinito, servirà per acquisire in input un contatto di cui ricercarne un singolo parametro.
void inizializzare_contatto_rubrica( Contatto *contatto )
{
	Stringa stringa_predefinita;
	int i;
	/*
	 * Imposto le informazioni predefinite che risultano:
	 * Campo errore: CODICE_CORRETTO.
	 * Campo stato: STATO_PREDEFINITO.
	 * Campo nominativo: Stringa vuota.
	 * Campo numero telefono: 000 000 0000.
	 */
	scrivere_errore_contatto(contatto, CODICE_CORRETTO);
	scrivere_stato_contatto(contatto, STATO_PREDEFINITO);
	scrivere_lunghezza_stringa(&stringa_predefinita, LUNGHEZZA_MINIMA_STRINGA );
	scrivere_nominativo_contatto( contatto, stringa_predefinita );
	scrivere_lunghezza_stringa(&stringa_predefinita, LUNGHEZZA_N_TELEFONO);
	i = 0;
	while( i < LUNGHEZZA_N_TELEFONO ){
		scrivere_carattere_stringa(&stringa_predefinita, i, INIZIO_ALFABETO_NUMERI);
		i = i + 1;
	}
	scrivere_n_telefono_contatto( contatto, stringa_predefinita );
	return;
}

//Funzione di conversione da carattere a intero dei numeri acquisiti dall'utente.
int convertire_in_intero(char carattere)
{
	int numero_corrispondente;            //Numero corrispondente al carattere inserito.

	//Controllo che sia un carattere corrispondente a un numero.
	if( carattere >= INIZIO_ALFABETO_NUMERI && carattere <= FINE_ALFABETO_NUMERI ){
		numero_corrispondente = carattere - INIZIO_ALFABETO_NUMERI;
	}
	return numero_corrispondente;
}

//Funzione per controllare se due stringhe sono uguali.
bool verificare_uguaglianza_stringhe( Stringa stringa_uno, Stringa stringa_due )
{
	bool esito;
	int i;
	//Parto con la condizione che le stringhe siano uguali.
	esito = true;
	//Controllo che le due stringhe non siano errate.
	if ( (controllare_correttezza_stringa(stringa_uno) == CODICE_CORRETTO ) && (controllare_correttezza_stringa(stringa_due) == CODICE_CORRETTO ) ){
		//Verifico che abbiano la stessa lunghezza.
		if ( leggere_lunghezza_stringa(stringa_uno) == leggere_lunghezza_stringa(stringa_due)){
			//Verifico che tutti i caratteri siano uguali.
			i = 0;
			while ( i < leggere_lunghezza_stringa(stringa_uno) && esito == true  ){
				if( leggere_carattere_stringa (stringa_uno, i ) != leggere_carattere_stringa (stringa_due, i ) ){
					esito = false;
				}
				i = i + 1;
			}
		}else{
			esito = false; //Se trovo un carattere che non è uguale, le due stringhe non sono uguali.
		}
	}else{
		esito = false; //Se una delle due stringhe è errata, comunico che le stringhe non sono uguali.
	}
	return esito;
}
