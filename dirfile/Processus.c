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


SProcessus * CreerProcessus (unsigned DureeExec, unsigned Taille)
{
	SProcessus * Proc = (SProcessus *) malloc (sizeof (SProcessus));

	Proc->IDProc = ++NbProc;
	Proc->DureeExec = DureeExec;
	Proc->Taille = Taille;
	Proc->Priorite = 0;
	Proc->NbAccesProc = 0;
	
	return Proc;

} // CreerProcessus ()

void CopierSProc (SProcessus *dest, SProcessus *src)
{
	dest->IDProc		  = src->IDProc;
	dest->DureeExec		  = src->DureeExec;
	dest->Taille		  = src->Taille;
	dest->NbAccesProc	  = src->NbAccesProc;
	dest->Priorite		  = src->Priorite;
	dest->NbPageEnMemoire = src->NbPageEnMemoire;

} // CopierSProc ()

void RecalculerPriorite ()
{
	SProcessus *ListeTmp[5][256];

	for (int i = 0; i < 5; ++i)
	{
		CursFileAttente[i] = 0;
		for (int j = 0; j < 256; ++j)
		{
			ListeTmp[i][j] = (SProcessus *) malloc (sizeof (SProcessus));

			if (NULL == ListePriorite[i][j])
				ListeTmp[i][j] = NULL;
			else
			{
				CopierSProc (ListeTmp[i][j], ListePriorite[i][j]);
				ListePriorite[i][j] = NULL;
			}
		}
	}

	for (int i = 0; i < 5; ++i)
	{

		for (int j = 0; j < 256; ++j)
		{
			if (NULL == ListeTmp[i][j])
				continue;
			
			// Calcul de la nouvelle priorité
			ListeTmp [i][j]->Priorite = (ListeTmp [i][j]->NbAccesProc - 1) / 2;

			AjouterProcListePriorite (ListeTmp[i][j]);

			// Enlève les processus de même ID de l'ancienne file
			unsigned ProcActuel = ListeTmp [i][j]->IDProc;
			for (unsigned k = 0; k < 256; ++k)
				if (NULL != ListeTmp[i][k])
					if (ListeTmp [i][k]->IDProc == ProcActuel)
						ListeTmp [i][k] = NULL;

		}
	}

} // RecalculerPriorite ()


int VerifierAjoutNouveauProc ()
{
	for (int i = 0; i < 256; ++i)
	{
		if (Proc[i] == NULL)
			continue;

		// Recupère la première case libre de ListePriorite
		int j;
		for (j = 0; j < 256; ++j)
			if (ListePriorite [0][j] == NULL)
				break;

		ListePriorite [0][j] = Proc[i];
		Proc[i] = NULL;

	}

	NouveauProc = 0;
	return;

} // VerifierAjoutNouveauProc ()

void AjouterProcListePriorite (SProcessus *Proc)
{
	for (int i = CursFileAttente [Proc->Priorite]; i < 256; ++i)
		if (NULL == ListePriorite[Proc->Priorite][i])
		{
			ListePriorite[Proc->Priorite][i] = Proc;
			break;
		}

} // AjouterProcListePriorite ()

SProcessus * ChercherProcID (unsigned IDProc, unsigned Priorite)
{

	for (int i = 0; i < 256; ++i)
		if (ListePriorite [Priorite][i]->IDProc == IDProc)
			return ListePriorite [Priorite][i];

	printf ("Proc of ID %d and priority %d does not exist !!\n", IDProc, Priorite);
	return;

} // ChercherProcID

void *FilePriorite ()
{
	for ( ; ; )
	{
		NbOrdonnancement = 0;

		// Remet à 0 les curseurs des files
		for (int i = 0; i < 5; ++i)
			CursFileAttente [i] = 0;

		// Applique round robin à la file la plus prioritaire non vide
		for (int i = 0; ; ++i)
		{
			if (1 == NouveauProc)
			{
				pthread_mutex_lock (&mutex);
				VerifierAjoutNouveauProc ();
				pthread_mutex_unlock (&mutex);
			}

			int FileContientElement = 0;

			if (NULL != ListePriorite [i][0])
				FileContientElement = 1;

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

void RoundRobin (unsigned Priorite)
{

	for ( ; CursFileAttente[Priorite] < 256; ++NbOrdonnancement)
	{
		if (NbOrdonnancement > 9)
			return;
		// Tant qu'il y a des proc à éxécuter
		if (NULL == ListePriorite [Priorite][CursFileAttente[Priorite]])
			return;

		SProcessus * ProcExecute = ListePriorite [Priorite][CursFileAttente [Priorite]];

		for (int PosQuantum = 0;
				PosQuantum < Quantum;
				++PosQuantum)
		{

			AccesMemProc (ProcExecute);

			// Si le processus est terminé alors on l'enlève
			if (--ProcExecute->DureeExec == 0)
			{
				printf("Process %d finished.\n", ProcExecute->IDProc);
				ListePriorite[Priorite][CursFileAttente [Priorite]] = NULL;
				++CursFileAttente [Priorite];
				break;
			}

			ListePriorite[Priorite][CursFileAttente[Priorite]] == NULL;
			AjouterProcListePriorite (ProcExecute);
			++CursFileAttente [Priorite];

			if (1 == NouveauProc)
			{
				pthread_mutex_lock (&mutex);
				VerifierAjoutNouveauProc ();
				pthread_mutex_unlock (&mutex);

				if ( 0 != Priorite)
					return;
			}
		}

	}

} // RoundRobin ()

