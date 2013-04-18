/**
 *
 * @file: main.c
 *
 * @author: Tom CHASSAGNE && Ludovic LUBEIGT
 *
 * @date: 3/04/13
 *
 * @brief Programme principale du projet d'système d'exploitation
 *
 **/

#include "include.h"

void CalculDuNombreDeCadre ()
{
	unsigned i, MemoireManquante;

	/* Mémoire vive */
	NombreCadreMemoireVive = TailleMemoireVive / TailleCadrePages;

	MemoireManquante = TailleMemoireVive - (TailleCadrePages * NombreCadreMemoireVive);
	if (MemoireManquante >  0)
		++NombreCadreMemoireVive;

	printf ("RAM creation (%d frame(s))\n", NombreCadreMemoireVive);

	CadrePageMemVive = (SProcessus *)
					malloc (NombreCadreMemoireVive * sizeof (SProcessus));
	CadrePageMemViveRestante = (unsigned *)
					malloc (NombreCadreMemoireVive * sizeof (unsigned));


	for (i = 0; i < NombreCadreMemoireVive; ++i)
		CadrePageMemViveRestante [i] = TailleCadrePages;

	if (MemoireManquante > 0)
		CadrePageMemViveRestante [i - 1] = MemoireManquante;



	/* Mémoire virtuelle */
	NombreCadreMemoireVirtuelle = TailleMemoireVirtuelle / TailleCadrePages;

	MemoireManquante = TailleMemoireVirtuelle - (TailleCadrePages * NombreCadreMemoireVirtuelle);
	if (MemoireManquante > 0)
		++NombreCadreMemoireVirtuelle;

	printf ("Virtual memory creation (%d frame(s))\n", NombreCadreMemoireVirtuelle);

	CadrePageMemVirtuelle = (SProcessus *)
					malloc (NombreCadreMemoireVirtuelle * sizeof (SProcessus));
	CadrePageMemVirtuelleRestante = (unsigned *)
					malloc (NombreCadreMemoireVirtuelle * sizeof (unsigned));

	NbCadreMemVirtuelleLibre = NombreCadreMemoireVirtuelle;

	for (i = 0; i < NombreCadreMemoireVirtuelle; ++i)
		CadrePageMemVirtuelleRestante [i] = TailleCadrePages;

	if (MemoireManquante > 0)
		CadrePageMemVirtuelleRestante [i - 1] = MemoireManquante;

} // CalculDuNombreDeCadre ()


int main(int argc, const char *argv[])
{
	if (argc != 1)
	{
		fprintf (stderr, "Error: no argument expected.\n");
		return 1;
	}

	int pFils;

	Initialisation ();

	printf ("\n\nCalculating page frame's number ...\n");
	CalculDuNombreDeCadre ();
	
	AfficheMenuChoix ();

	/*
	if ( (pFils = fork ()) < 0)
	{
		perror ("fork()");
		exit (1);
	}

	if (0 == pFils) // Fils
	{
		// ToDo
	}
	// Père
	*/

	return 0;

} // main ()
