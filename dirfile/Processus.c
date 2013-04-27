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
	CalculPriorite = 1;
	SProcessus *ListeTmp[5][256];

	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 256; ++j)
		{
			ListeTmp[i][j] = (SProcessus *) malloc (sizeof (SProcessus));

			if (NULL == ListePriorite[i][j])
				ListeTmp[i][j] = NULL;
			else
			{
				CopierSProc (ListeTmp[i][j], ListePriorite[i][j]);

				pthread_mutex_lock (&mutex);
				ListePriorite[i][j] = NULL;
				pthread_mutex_unlock (&mutex);
			}
		}
	}

	for (int i = 0; i < 5; ++i)
	{

		for (int j = 0; j < 256; ++j)
		{
			if (NULL == ListeTmp[i][j])
				continue;
			
			// Calcul de la nouvelle priorité si NbAccessProc n'est pas nul
			if (0 != ListeTmp[i][j]->NbAccesProc)
				ListeTmp [i][j]->Priorite = (ListeTmp [i][j]->NbAccesProc - 1) / 2;
			else
				ListeTmp[i][j]->Priorite = 0;

			ListeTmp [i][j]->NbAccesProc = 0;

			// Ajout du processus à la bonne liste de priorité
			pthread_mutex_lock (&mutex);
			AjouterProcListePriorite (ListeTmp[i][j]);
			NouveauProc = 1;
			pthread_mutex_unlock (&mutex);

		}
	}
	CalculPriorite = 0;

} // RecalculerPriorite ()

void AjouterProcListePriorite (SProcessus *Proc)
{

	for (int i = CursFileAttente [Proc->Priorite]; i < 256; ++i)
		if (NULL == ListePriorite[Proc->Priorite][i])
		{
			ListePriorite[Proc->Priorite][i] = Proc;
			break;
		}
		else if (ListePriorite[Proc->Priorite][i]->IDProc == Proc->IDProc)
			break;

} // AjouterProcListePriorite ()

SProcessus * ChercherProcID (unsigned IDProc, unsigned Priorite)
{

	for (int i = 0; i < 256; ++i)
		if (ListePriorite [Priorite][i]->IDProc == IDProc)
			return ListePriorite [Priorite][i];

	fprintf(SortieAffichage, "Proc of ID %d and priority %d does not exist !!\n", IDProc, Priorite);
	return;

} // ChercherProcID

void SupprimerPageMemoire (unsigned IDProc)
{
	int i;
	for (i = 0; i < NombreCadreMemoireVive; ++i)
	{
		if (MemVive[i] != NULL &&
			MemVive[i]->IDProc == IDProc)
		{
			MemVive[i] = NULL;
		}
	}

	for (i = 0; i < NombreCadreMemoireVirtuelle; ++i)
	{
		if (MemVirtuelle[i] != NULL &&
			MemVirtuelle[i]->IDProc == IDProc)
		{
			MemVirtuelle[i] = NULL;
			++NbCadreMemVirtuelleLibre;
		}
	}
	
} // SupprimerPageMemoire ()

void *FilePriorite ()
{
	for ( ; ; )
	{
		NbOrdonnancement = 0;

		// Applique round robin à la file la plus prioritaire non vide
		for (int i = 0; ; ++i)
		{
			if (1 == NouveauProc)
			{
				pthread_mutex_lock (&mutex);
				fprintf (SortieAffichage, "Process(es) %sconsidered.\n", ListeNouveauProc);
				sprintf (ListeNouveauProc, "");
				NouveauProc = 0;
				pthread_mutex_unlock (&mutex);
				i = -1;
				continue;
			}

			int FileContientElement = 0;

			for (int j = 0; j < 256; ++j)
				if (NULL != ListePriorite [i][j])
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

		for (int i = 0; i < 5; ++i)
			CursFileAttente[i] = 0;

		fprintf(SortieAffichage, "\n...Calculating new priorities...\n");
		RecalculerPriorite ();
		fprintf(SortieAffichage, "Done!\n\n");
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
		int IndProcFini;

		for (int PosQuantum = 0;
				PosQuantum < Quantum;
				++PosQuantum)
		{
			IndProcFini = -1;

			AccesMemProc (ProcExecute);

			// Si le processus est terminé alors on l'enlève
			if (--ProcExecute->DureeExec == 0)
			{
				fprintf (SortieAffichage, "! Process %d finished.\n", ProcExecute->IDProc);
				SupprimerPageMemoire (ProcExecute->IDProc);

				for (IndProcFini = 0; IndProcFini < 256; ++IndProcFini)
					if (NULL != ListePriorite[Priorite][IndProcFini] &&
							ProcExecute->IDProc == ListePriorite[Priorite][IndProcFini]->IDProc)
						ListePriorite[Priorite][IndProcFini] = NULL;
				++CursFileAttente [Priorite];
				break;
			}
		}


		// si le processus ne s'est pas fini
		if (-1 == IndProcFini)
		{
			++ProcExecute->NbAccesProc;

			// on le retire de la file
			ListePriorite[Priorite][CursFileAttente[Priorite]] = NULL;
			int ind;
			++CursFileAttente[Priorite];

			// pour le placer en fin de file
			for (ind = CursFileAttente[Priorite]; ; ++ind)
				if (NULL == ListePriorite[Priorite][ind])
				{
					ListePriorite[Priorite][ind] = ProcExecute;
					break;
				}
		}

		if (1 == NouveauProc)
		{
			pthread_mutex_lock (&mutex);

			fprintf (SortieAffichage, "Process(es) %sconsidered.\n", ListeNouveauProc);
			sprintf (ListeNouveauProc, "");

			if ( 0 != Priorite)
			{
				NouveauProc = 0;
				pthread_mutex_unlock (&mutex);
				return;
			}
			pthread_mutex_unlock (&mutex);
		}
	}

} // RoundRobin ()

