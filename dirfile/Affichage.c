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

void CreerTerminalAffichage ()
{
	// Crée la nouvelle fenêtre et calcule son ID
	system ("ls /dev/pts > .tty1");
	system ("gnome-terminal -t \"OSS Monitoring\"");
	sleep (1);
	system ("ls /dev/pts > .tty2");
	system ("diff -n .tty1 .tty2 | tail -n 1 > .tty");
	
	// Récupère l'ID contenu dans le fichier
	int FileTty = open (".tty", O_RDONLY);
	char buf [3];
	read (FileTty, buf, 3);
	int tty = atoi (&buf);
	system ("rm .tty1 .tty2 .tty");
	
	// Génère l'url du terminal d'affichage et l'ouvre dans SortieAffichage
	char url [12];
	sprintf(url, "/dev/pts/%d", tty);
	SortieAffichage = fopen (url, "a");
	
	printf("Opened the monitoring terminal at %s\n", url);
	fprintf(SortieAffichage, "\n=== OSS - Operating System Simulator ===\n\n");
	
} // CreerTerminalAffichage ()

int MenuChoix ()
{
	char Rep [64];
	
	printf ("\n=== OSS - Operating System Simulator ===\n");
	printf ("1 - New process\n");
	printf ("2 - Process(es) in the run queue\n");
	printf ("3 - Diplay memory\n");
	printf ("4 - Process(es) with their duration\n");
	printf ("5 - Exit program\n");
	
	printf ("Choice : ");

	fflush (stdin);
	gets (&Rep);
	int Choix = atoi (&Rep);
	
	printf("\n");

	if (Choix > 0 && Choix < 6) return Choix;
	else return 0;

} // MenuChoix ()

void AfficheMenuChoix ()
{

	for ( ; ; )
	{
		int Rep = MenuChoix ();

		if 		(Rep == 0) continue;
		else if (Rep == 1) ChoixNouveauProc ();
		else if (Rep == 2) AfficheTabProc ();
		else if (Rep == 3) AfficherEtatMemoire ();
		else if (Rep == 4) AfficherProcDuree ();
		else if (Rep == 5) return;
	}

} // AfficheMenuChoix ()

void ChoixNouveauProc ()
{
	for (; 1 == CalculPriorite;);

	unsigned Duree, Taille;

	char rep[32];
	int i = -1;
	int NombreDePage;

	for ( ; -1 == i; )
	{
		printf ("Enter processus duration: ");
		gets (&rep);
		
		if (strcmp(rep, "") == 0)
		{
			i = -1;
			printf ("\033[31mYou need to enter something !\033[0m\n");
			continue;
		}
		for (i = 0; NULL != rep [i]; ++i)
			if (! isdigit (rep [i]))
			{
				i = -1;
				printf ("\033[31mIt's not a number!\033[0m\n");
				break;
			}
	}

	Duree = atoi (&rep);

	i = -1;
	for ( ; -1 == i; )
	{	
		printf ("Enter processus size: ");
		gets (&rep);
		
		if (strcmp(rep, "") == 0)
		{
			i = -1;
			printf ("\033[31mYou need to enter something !\033[0m\n");
			continue;
		}
		for (i = 0; NULL != rep [i]; ++i)
			if (! isdigit (rep [i]))
			{
				i = -1;
				printf ("\033[31mIt's not a number!\033[0m\n");
				break;
			}
	}

	Taille = atoi (&rep);

	pthread_mutex_lock (&mutex);
	
	SProcessus * ProcTemp = CreerProcessus (Duree, Taille);
	
	NombreDePage = AjouterNouveauProcessusEnMemoire (ProcTemp);
	// Si le proc demande plus de mémoire que disponible
	if (-1 == NombreDePage)
	{
		free (ProcTemp);
		pthread_mutex_unlock (&mutex);
		return;
	}

	// Ajout du processus
	ProcTemp->NbPageEnMemoire = NombreDePage;
	AjouterProcListePriorite (ProcTemp);

	char *tmp = (char *) malloc (8);
	sprintf (tmp, "%d, ", NbProc);
	strcat (ListeNouveauProc, tmp);
	free (tmp);

	NouveauProc = 1;

	pthread_mutex_unlock (&mutex);

	printf("\nProcess %d created with duration=%d and size=%d (%d pages)\n",
			NbProc, ProcTemp->DureeExec, ProcTemp->Taille, ProcTemp->NbPageEnMemoire);

} // ChoixNouveauProc ()

void AfficheTabProc ()
{
	printf("Priority\t\tQueue line\n");
	
	for (int i = 0; i < 5; ++i)
	{
		printf("%d\t\t\t", i);
		for (int j = CursFileAttente[i]; j < 256; ++j)
		{
			if (ListePriorite [i][j] != NULL)
				printf ("%d, ", ListePriorite [i][j]->IDProc);
		}
		printf("\n");
	}
	
} // AfficheTabProc ()

void AfficherProcDuree ()
{
	printf("Process : duration\n");
	
	for (int i = 0; i < 5; ++i)
	{
		for (int j = CursFileAttente[i]; j < 256; ++j)
		{
			if (ListePriorite [i][j] != NULL)
				printf ("Process %d : %d\n", ListePriorite [i][j]->IDProc, ListePriorite [i][j]->DureeExec);
		}
	}
	
} // AfficheProcDuree ()

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
			printf ("%4d: %2d, %2d ", i, MemVive[i]->IDProc, MemVive[i]->PageProc);

		if ( ! (++i % 5) )
			printf ("\n");
	}
	
	printf("\n");
	
	printf ("Virtual memory (%d frame(s))\n(frame, process's ID, process's page)\n",
				NombreCadreMemoireVirtuelle);

	for (i = 0; i < NombreCadreMemoireVirtuelle; )
	{
		if (NULL == MemVirtuelle[i])
			printf ("%4d:        ", i);
		else
			printf ("%4d: %2d, %2d ", i, MemVirtuelle[i]->IDProc, MemVirtuelle[i]->PageProc);

		if ( ! (++i % 5) )
			printf ("\n");
	}

} // AfficherEtatMemoire ()

void Initialisation ()
{

	char rep[32];
	int i = -1;
	
	for ( ; -1 == i;)
	{
		printf ("Enter RAM size: ");
		gets (&rep);
		
		if (strcmp(rep, "") == 0)
		{
			i = -1;
			printf ("\033[31mYou need to enter something !\033[0m\n");
			continue;
		}
		for (i = 0; NULL != rep [i]; ++i)
			if (! isdigit (rep [i]))
			{
				i = -1;
				printf ("\033[31mIt's not a number!\033[0m\n");
				break;
			}

	}
	TailleMemoireVive = atoi (&rep);

	i = -1;
	for ( ; -1 == i;)
	{
		printf ("Enter virtual memory size: ");
		gets (&rep);
		
		if (strcmp(rep, "") == 0)
		{
			i = -1;
			printf ("\033[31mYou need to enter something !\033[0m\n");
			continue;
		}
		for (i = 0; NULL != rep [i]; ++i)
			if (! isdigit (rep [i]))
			{
				i = -1;
				printf ("\033[31mIt's not a number!\033[0m\n");
				break;
			}

		if ( (-1 != i) && (TailleMemoireVive > atoi (&rep)) )
		{
			i = -1;
			printf ("\033[31mVirtual memory size has to be greater than RAM size!\033[0m\n");
		}

	}
	TailleMemoireVirtuelle = atoi (&rep);

	i = -1;
	for ( ; -1 == i;)
	{
		printf ("Enter page frames size: ");
		gets (&rep);
		
		if (strcmp(rep, "") == 0)
		{
			i = -1;
			printf ("\033[31mYou need to enter something !\033[0m\n");
			continue;
		}
		for (i = 0; NULL != rep [i]; ++i)
			if (! isdigit (rep [i]))
			{
				i = -1;
				printf ("\033[31mIt's not a number!\033[0m\n");
				break;
			}

		if ( (-1 != 1) && (0 == atoi (&rep)) )
		{
			i = -1;
			printf ("\033[31mYou can't have a page frames size at 0\033[0m\n");
		}
	}
	TailleCadrePages = atoi (&rep);

	i = -1;
	for ( ; -1 == i;)
	{
		printf ("Enter quantum: ");
		gets (&rep);
		
		if (strcmp(rep, "") == 0)
		{
			i = -1;
			printf ("\033[31mYou need to enter something !\033[0m\n");
			continue;
		}
		for (i = 0; NULL != rep [i]; ++i)
			if (! isdigit (rep [i]))
			{
				i = -1;
				printf ("\033[31mIt's not a number!\033[0m\n");
				break;
			}
	}
	Quantum = atoi (&rep);

	ListeNouveauProc = (char *) malloc (64);

} // Initialisation ()
