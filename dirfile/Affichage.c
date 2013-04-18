/**
 *
 * @file: Affichage.c
 *
 * @author: Tom CHASSAGNE && Ludovic LUBEIGT
 *
 * @date: 10/04/13
 *
 * @brief fonctions d'affichage du projet de système d'exploitation
 *
 **/

int MenuChoix ()
{
	char Rep [64];
	
	printf ("\n=== OSS - Operating System Simulator ===\n");
	printf ("1 - New process\n");
	printf ("2 - Process(es) in the run queue\n");
	printf ("3 - Diplay memory\n");
	printf ("Choice : ");

	fflush (stdin);
	gets (&Rep);
	int Choix = atoi (&Rep);
	
	printf("\n");

	if (Choix > 0 && Choix < 4) return Choix;
	else return 0;

} // MenuChoix ()

void AfficheMenuChoix ()
{
	
	for ( ; ; )
	{
		int Rep = MenuChoix ();
		
		if (Rep == 0) continue;
		else if (Rep == 1) ChoixNouveauProc();
		else if (Rep == 2) AfficheTabProc();
		else if (Rep == 3) AfficherEtatMemoire ();
	}
	
} // AfficheMenuChoix ()

void ChoixNouveauProc ()
{
	unsigned Duree, Taille;
	
	char rep[32];
	int i = -1;
	int NombreDePage;
	
	printf ("Enter processus duration: ");
	for (gets (&rep); -1 == i;)
	{
		for (i = 0; NULL != rep [i]; ++i)
			if (! isdigit (rep [i]))
			{
				i = -1;
				printf ("It's not a number!\n");
				printf ("Enter processus duration: ");
				gets (&rep);
				break;
			}

	}
	Duree = atoi (&rep);

	i = -1;
	printf ("Enter processus size: ");
	for (gets (&rep); -1 == i;)
	{
		for (i = 0; NULL != rep [i]; ++i)
			if (! isdigit (rep [i]))
			{
				i = -1;
				printf ("It's not a number!\n");
				printf ("Enter processus size: ");
				gets (&rep);
				break;
			}

	}
	Taille = atoi (&rep);
	
	// Cherche une case vide
	for (i = 0; i < 256; ++i)
	{
		if (Proc[i] == NULL)
		{
			Proc[i] = CreerProcessus (Duree, Taille, i);
			break;
		}
	}

	NombreDePage = AjouterNouveauProcessusEnMemoire (Proc[i]);
	if (-1 == NombreDePage)
	{
		free (Proc [i]);
		return;
	}
	Proc[i]->NbPageEnMemoire = NombreDePage;
	
	printf("\nProcess %d created with duration=%d and size=%d (%d pages)\n",
			i, Proc[i]->DureeExec, Proc[i]->Taille, Proc[i]->NbPageEnMemoire);
	
} // ChoixNouveauProc ()

int AjouterNouveauProcessusEnMemoire (SProcessus *proc)
{
	unsigned NombreDePage, i, PremierCadre;
	int TailleProcTmp = proc->Taille;

	if ( (NbCadreMemVirtuelleLibre * TailleCadrePages) < proc->Taille )
	{
		fprintf (stderr, "\033[31m Error: Out of virtual memory\033[0m\n");
		return -1;
	}


	NombreDePage = 0;
	for (i = 0; 0 != TailleProcTmp; ++i)
	{
		if (NULL != CadrePageMemVirtuelle[i])
			continue;

		CadrePageMemVirtuelle[i] = proc;
		++NombreDePage;

		--NbCadreMemVirtuelleLibre;


		if (TailleProcTmp > CadrePageMemVirtuelleRestante[i])
		{
			TailleProcTmp -= CadrePageMemVirtuelleRestante[i];
			CadrePageMemVirtuelleRestante[i] -= CadrePageMemVirtuelleRestante[i];
		}
		else
		{
			CadrePageMemVirtuelleRestante[i] -= TailleProcTmp;
			TailleProcTmp = 0;
		}


	}

	return NombreDePage;

} // AjouterNouveauProcessusEnMemoire ()

void AfficheTabProc ()
{
	printf("Current processes:\n");
	
	for (int i = 0; i < 256; ++i)
	{
		if (Proc[i] != NULL)
			printf ("   Process [%d]: duration=%d and size=%d\n", i, Proc[i]->DureeExec, Proc[i]->Taille);
	}
	
} // AfficheTabProc ()

void AfficherEtatMemoire ()
{
	unsigned PageProcessus[256], i;

	for (i = 0; i < 256; ++i)
		PageProcessus[i] = 0;

	printf ("Virtual memory (%d frame(s))\n(frame, process's ID, process's page)\n",
				NombreCadreMemoireVirtuelle);

	for (i = 0; i < NombreCadreMemoireVirtuelle;)
	{
		if (NULL == CadrePageMemVirtuelle[i])
			printf ("%4d:        ", i);
		else
				printf ("%4d: %2d, %2d ", i, CadrePageMemVirtuelle[i]->IDProc,
						PageProcessus[CadrePageMemVirtuelle[i]->IDProc]++);

		if ( ! (++i % 4) )
			printf ("\n");
	}

} // AfficherEtatMemoire ()

void Initialisation ()
{

	char rep[32];
	int i = -1;

	printf ("Enter RAM size: ");
	for (gets (&rep); -1 == i;)
	{
		for (i = 0; NULL != rep [i]; ++i)
			if (! isdigit (rep [i]))
			{
				i = -1;
				printf ("It's not a number!\n");
				printf ("Enter RAM size: ");
				gets (&rep);
				break;
			}

	}
	TailleMemoireVive = atoi (&rep);

	i = -1;
	printf ("Enter virtual memory size: ");
	for (gets (&rep); -1 == i;)
	{
		for (i = 0; NULL != rep [i]; ++i)
			if (! isdigit (rep [i]))
			{
				i = -1;
				printf ("It's not a number!\n");
				printf ("Enter virtual memory size: ");
				gets (&rep);
				break;
			}

		if ( (-1 != i) && (TailleMemoireVive > atoi (&rep)) )
		{
			i = -1;
			printf ("Virtual memory size has to be greater than RAM size!\n");
			printf ("Enter virtual memory size: ");
			gets (&rep);
			break;
		}

	}
	TailleMemoireVirtuelle = atoi (&rep);

	i = -1;
	printf ("Enter page frames size: ");
	for (gets (&rep); -1 == i;)
	{
		for (i = 0; NULL != rep [i]; ++i)
			if (! isdigit (rep [i]))
			{
				i = -1;
				printf ("It's not a number!\n");
				printf ("Enter page frames size: ");
				gets (&rep);
				break;
			}

		if ( (-1 != 1) && (0 == atoi (&rep)) )
		{
			i = -1;
			printf ("You can't have a page frames size at 0");
			printf ("Etner page frames size: ");
			gets (&rep);
			break;
		}
	}
	TailleCadrePages = atoi (&rep);

	i = -1;
	printf ("Enter quantum: ");
	for (gets (&rep); -1 == i;)
	{
		for (i = 0; NULL != rep [i]; ++i)
			if (! isdigit (rep [i]))
			{
				i = -1;
				printf ("It's not a number!\n");
				printf ("Enter quantum: ");
				gets (&rep);
				break;
			}
	}
	Quantum = atoi (&rep);

} // Initialisation ()
