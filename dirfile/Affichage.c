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
	}
	
} // AfficheMenuChoix ()

void ChoixNouveauProc ()
{
	unsigned Duree, Taille;
	
	char rep[32];
	int i = -1;
	
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
	
	printf("   Process %d created with duration=%d and size=%d (? pages)\n", i, Proc[i]->DureeExec, Proc[i]->Taille);
	
} // ChoixNouveauProc ()

void AfficheTabProc ()
{
	printf("Current processes:\n");
	
	for (int i = 0; i < 255; ++i)
	{
		if (Proc[i] != NULL)
			printf ("   Process [%d]: duration=%d and size=%d\n", i, Proc[i]->DureeExec, Proc[i]->Taille);
	}
	
} // AfficheTabProc ()

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
