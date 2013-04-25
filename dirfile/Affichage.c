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
	printf ("4 - Exit program\n");
	printf ("Choice : ");

	fflush (stdin);
	gets (&Rep);
	int Choix = atoi (&Rep);
	
	printf("\n");

	if (Choix > 0 && Choix < 5) return Choix;
	else return 0;

} // MenuChoix ()

void AfficheMenuChoix ()
{

	for ( ; ; )
	{
		int Rep = MenuChoix ();

		if 		(Rep == 0) continue;
		else if (Rep == 1)
		{
			pthread_mutex_lock (&mutex);
			ChoixNouveauProc ();
			pthread_mutex_unlock (&mutex);
		}
		else if (Rep == 2) AfficheTabProc ();
		else if (Rep == 3) AfficherEtatMemoire ();
		else if (Rep == 4) return;
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
			Proc[i] = CreerProcessus (Duree, Taille);
			break;
		}
	}
	
	/*
	// Cherche une case vide
	for (i = 0; i < 256; ++i)
	{
		if (ListePriorite[0][i] == NULL)
		{
			ListePriorite[0][i] = CreerProcessus (Duree, Taille, i);
			break;
		}
	}
	*/

	NombreDePage = AjouterNouveauProcessusEnMemoire (Proc[i]);
	// Si le proc demande plus de mémoire que disponible
	if (-1 == NombreDePage)
	{
		free (Proc [i]);
		return;
	}
	
	// Ajout du processus
	Proc[i]->NbPageEnMemoire = NombreDePage;
	//ListePriorite[0][i]->NbPageEnMemoire = NombreDePage;
	
	
	NouveauProc = 1;

	printf("\nProcess %d created with duration=%d and size=%d (%d pages)\n",
			i, Proc[i]->DureeExec, Proc[i]->Taille, Proc[i]->NbPageEnMemoire);

} // ChoixNouveauProc ()

void AfficheTabProc ()
{
	printf("Priority\t\tQueue line\n");
	
	for (int i = 0; i < 5; ++i)
	{
		printf("%d\t\t\t", i);
		for (int j = 0; j < 256; ++j)
		{
			if (FileAttente [i][j] != -1)
			printf ("%d, ", FileAttente [i][j]);
			//	printf ("   Process [%d]: duration=%d and size=%d\n", i, Proc[i]->DureeExec, Proc[i]->Taille);
		}
		printf("\n");
	}
	
} // AfficheTabProc ()

void AfficherEtatMemoire ()
{
	unsigned PageProcessus[256], i;

	for (i = 0; i < 256; ++i)
		PageProcessus[i] = 0;

	printf ("RAM memory (%d frame(s))\n(frame, process's ID, process's page)\n",
				NombreCadreMemoireVive);

	for (i = 0; i < NombreCadreMemoireVive; )
	{
		//if (NULL == CadrePageMemVive[i])
		if (NULL == MemVive[i])
			printf ("%4d:        ", i);
		else
		//	printf ("%4d: %2d, %2d ", i, CadrePageMemVive[i]->IDProc,
		//				PageProcessus[CadrePageMemVive[i]->IDProc]++);
			printf ("%4d: %2d, %2d ", i, MemVive[i]->IDProc, MemVive[i]->PageProc);

		if ( ! (++i % 5) )
			printf ("\n");
	}
	
	printf("\n");
	
	printf ("Virtual memory (%d frame(s))\n(frame, process's ID, process's page)\n",
				NombreCadreMemoireVirtuelle);

	for (i = 0; i < NombreCadreMemoireVirtuelle; )
	{
		//if (NULL == CadrePageMemVirtuelle[i])
		if (NULL == MemVirtuelle[i])
			printf ("%4d:        ", i);
		else
		//	printf ("%4d: %2d, %2d ", i, CadrePageMemVirtuelle[i]->IDProc,
		//				PageProcessus[CadrePageMemVirtuelle[i]->IDProc]++);
			printf ("%4d: %2d, %2d ", i, MemVirtuelle[i]->IDProc, MemVirtuelle[i]->PageProc);

		if ( ! (++i % 5) )
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
