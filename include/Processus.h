/**
 *
 * @file: 	Processus.c
 *
 * @author:	Tom CHASSAGNE && Ludovic LUBEIGT
 *
 * @date: 	17/04/13
 *
 * @brief:	Structure des processus
 *
 **/

typedef struct SProcessus
{
	unsigned IDProc;
	unsigned DureeExec;
	unsigned Taille;

	unsigned Priorite;
	unsigned NbAccesProc;
	unsigned NbPageEnMemoire;

} SProcessus;
