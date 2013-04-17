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
	unsigned DateSoumission;
	unsigned DureeExec;
	unsigned Taille;

	unsigned NbAccesProc;
	unsigned Priorite;

} SProcessus;

