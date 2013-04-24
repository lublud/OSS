/**
 *
 * @file:	Processus.c
 *
 * @author:	Tom CHASSAGNE && Ludovic LUBEIGT
 *
 * @date:	17/04/13
 *
 * @brief:	Fonctions liées aux processus
 *
 **/


SProcessus * CreerProcessus (unsigned DureeExec, unsigned Taille, unsigned IDProc)
{
	SProcessus * Proc = (SProcessus *) malloc (sizeof (SProcessus));

	Proc->IDProc = IDProc;
	Proc->DateSoumission; // = ... ?
	Proc->DureeExec = DureeExec;
	Proc->Taille = Taille;
	Proc->Priorite = 0;
	Proc->NbAccesProc = 0;

	return Proc;

} // CreerProcessus ()

void RecalculerPriorite ()
{
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 255; ++j)
		{
			if (ListePriorite [i][j] == NULL) continue;
			
			// Calcul de la nouvelle priorité
			ListePriorite [i][j]->Priorite = (ListePriorite [i][j]->NbAccesProc - 1) / 2;
			
			// !! Puis remet le processus dans sa bonne liste de priorité
		}
	}

} // RecalculerPriorite ()

void ResetFileAttente ()
{
	CurseurFileAttente = 0;
	
	// Initialisation de FileAttente
	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 256; ++j)
			FileAttente [i][j] = -1;
	
} // ResetFileAttente

int VerifierAjoutNouveauProc ()
{
	if (Proc[0] != NULL)
	{
		for (int i = 0; i < 256; ++i)
		{
			if (Proc[i] == NULL) break;

			// Recupère la première case libre de ListePriorite
			int j = 0;
			for ( ; j < 256; ++j)
				if (ListePriorite [0][j] == NULL) break;

			ListePriorite [0][j] = Proc[i];
			Proc[i] = NULL;
			
			// Recupère la première case libre de FileAttente
			int k = CurseurFileAttente;
			for ( ; k < 256; ++k)
				if (FileAttente [0][k] == -1) break;

			FileAttente [0][k] = ListePriorite [0][j]->IDProc;
		}

		// mutex
		NouveauProc = 0;
		return;
	}

} // VerifierAjoutNouveauProc ()

void *FilePriorite ()
{
	for ( ; ; )
	{
		NbOrdonnancement = 0;

		ResetFileAttente();

		// Applique round robin à la file la plus prioritaire non vide
		for (int i = 0; ; ++i)
		{
			if (1 == NouveauProc)
				VerifierAjoutNouveauProc ();
			int FileContientElement = 0;

			if (NULL != ListePriorite [i][0])
				FileContientElement = 1;

			/*
			for (int j = 0; j < 256; ++j)
			{
				if (ListePriorite [i][j] == NULL) continue;
				else
				{
					FileContientElement = 1;
					break;
				}
			}
			*/

			// Si la liste est non vide, on Round Robin
			if (FileContientElement)
			{
				RoundRobin (i);
				if (10 == NbOrdonnancement)
					break;

				// on remet à 0 au cas où l'on ait ajouté un proc dans RoundRobin
				i = -1;
			}

			if (4 == i)
				i = -1;


		}

		printf("Calculating new priorities...\n");
		RecalculerPriorite();
		printf("Done!\n");
	}

} // FilePriorite ()

// Retourne le nombre de réordo effectués
void RoundRobin (unsigned Priorite)
{
	/*
	for ( ; ; )
	{
		printf("JE SUIS ROUND ROBIN. RESPECT MY AUTHORITY :\n");
		
		if (Proc[0] != NULL)
			printf ("   Process [0]: duration=%d and size=%d\n", Proc[0]->DureeExec, Proc[0]->Taille);
		
		sleep (5);
	}
	*/

	printf("JE SUIS ROUND ROBIN. RESPECT MY AUTHORITY !\n");

	// Vérifie d'abord si des processus ont été ajouté
	/*
	if (Proc[0] != NULL)
	{
		for (int i = 0; i < 256; ++i)
		{
			if (Proc[i] == NULL) break;

			int j = 0;
			// Recupère la première case
			for ( ; j < 256; ++j)
				if (ListePriorite [0][j] == NULL) break;

			ListePriorite [0][j] = Proc[i];
			Proc[i] = NULL;
		}

		return;
	}
	*/

	// Zouboudabidou ! Et que ça saute ! Perlinpainpain saut de lapin.
	// Qui sont mortels et lancent des carottes volantes dirigées
	
	for ( ; CurseurFileAttente < 256; )
	{
		if (FileAttente[Priorite][CurseurFileAttente] == -1) break;

		printf ("FileAttente[%d][%d] = %d\n",
					Priorite, CurseurFileAttente, FileAttente [Priorite][CurseurFileAttente]);
		SProcessus * ProcExecute = ListePriorite [Priorite][FileAttente [Priorite][CurseurFileAttente]];

		for (int PosQuantum = 0;
				ProcExecute->DureeExec-- > 0 || PosQuantum < Quantum;
				++PosQuantum)
		{
			// Si le processus est terminé alors on l'enlève
			if (ProcExecute->DureeExec-- == 0)
			{
				ListePriorite [Priorite][FileAttente [Priorite][CurseurFileAttente]] = NULL;
				return;
			}
			
			// Le programme va sigfault dans :
			AccesMemProc (ProcExecute);

			++CurseurFileAttente;

			if (1 == NouveauProc)
			{
				VerifierAjoutNouveauProc ();
				if ( 0 != Priorite)
					return;
			}
		}
	}
	printf ("FinRR\n");

} // RoundRobin ()
