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
	for (int i = 0; i < 255; ++i)
	{
		if (Proc[i] == NULL) continue;
		
		Proc[i]->Priorite = (Proc[i]->NbAccesProc - 1) / 2;
	}
	
} // RecalculePriorite ()

void RoundRobin (unsigned Priorite)
{
	for ( ; ; )
	{
		printf("JE SUIS ROUND ROBIN. RESPECT MY AUTHORITY :\n");
		
		if (Proc[0] != NULL)
			printf ("   Process [0]: duration=%d and size=%d\n", Proc[0]->DureeExec, Proc[0]->Taille);
		
		sleep (5);
	}
	
} // RoundRobin ()

