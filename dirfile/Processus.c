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


SProcessus * CreerProcessus (unsigned DateSoum, unsigned DureeExec)
{
	SProcessus * Proc = (SProcessus *) malloc (sizeof (SProcessus));

	Proc->DateSoumission = DateSoum;
	Proc->DureeExecution = DureeExec;
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
