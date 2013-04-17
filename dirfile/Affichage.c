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
	
	printf ("=== OSS - Operating System Simulator ===\n");
	printf ("1 - New process\n");
	printf ("2 - Process(es) in the run queue\n");
	printf ("3 - Diplay memory\n");
	printf ("Choix : ");

	fflush (stdin);
	gets (&Rep);
	int Choix = atoi (&Rep);
	
	if (Choix > 0 && Choix < 4) return Choix;
	else return 0;

} // MenuChoix ()


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
