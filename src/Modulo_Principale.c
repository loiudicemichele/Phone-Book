/*
 *							----MODULO PRINCIPALE----
 * ============================================================================
 * Name        : Modulo_Principale.c
 * Author      : Gruppo 3
 * ============================================================================
 */

#include "Impostazioni.h"
#include "Gestire_Interfaccia_Utente.h"

//La funzione richiama il menù principale del programma.
void richiamare_menu()
{
	int stato_configurazione; //Variabile di controllo della configurazione iniziale del programma.
	//Imposto la dimensione dello schermo ad uno standard: 25 righe x 80 colonne.
	impostare_dimensione_schermo();
	//Configurazione della cartella di lavoro del programma.
	imposta_la_cartella_di_esecuzione();
	//Controllo che tutti i file di cui il programma ha bisogno siano esistenti ed apribili.
	stato_configurazione = configurare_programma();
	if ( stato_configurazione == CODICE_CORRETTO ){
		//Se il controllo va a buon fine, mostro il menù principale del programma.
		mostrare_menu();
	}else{
		//Questa stampa diretta è necessaria in quanto non è stato trovato uno dei file.
		printf("Errore! Controlla che il percorso dei file di layout sia corretto!\n");
		system("pause");
	}
}

int main(void)
{
	//Apro il menu.
	richiamare_menu();
	return 0;
}

