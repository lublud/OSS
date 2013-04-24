/**
 *
 * @file:	Memoire.c
 *
 * @author:	Tom CHASSAGNE && Ludovic LUBEIGT
 *
 * @date:	3/04/13
 *
 * @brief:	Fonctions de gestion de la memoire vive et virtuelle
 *
 **/


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
		//if (NULL != CadrePageMemVirtuelle[i])
		//	continue;
		if (NULL != MemVirtuelle[i])
			continue;
		
		//CadrePageMemVirtuelle[i] = proc;
		
		MemVirtuelle[i] = (SMemoire *) malloc (sizeof (SMemoire));
		MemVirtuelle[i]->IDProc = proc->IDProc;
		MemVirtuelle[i]->PageProc = NombreDePage;
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


void CalculDuNombreDeCadre ()
{
	unsigned i, MemoireManquante;

	/* Mémoire vive */
	NombreCadreMemoireVive = TailleMemoireVive / TailleCadrePages;

	MemoireManquante = TailleMemoireVive - (TailleCadrePages * NombreCadreMemoireVive);
	if (MemoireManquante >  0)
		++NombreCadreMemoireVive;

	printf ("RAM creation (%d frame(s))\n", NombreCadreMemoireVive);

//	CadrePageMemVive = (SProcessus *)
//					malloc (NombreCadreMemoireVive * sizeof (SProcessus));
	
	MemVive = (SMemoire *) malloc (NombreCadreMemoireVive * sizeof (SMemoire));
	
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

//	CadrePageMemVirtuelle = (SProcessus *)
//					malloc (NombreCadreMemoireVirtuelle * sizeof (SProcessus));

	MemVirtuelle = (SMemoire *) malloc (NombreCadreMemoireVirtuelle * sizeof (SMemoire));
					
	CadrePageMemVirtuelleRestante = (unsigned *)
					malloc (NombreCadreMemoireVirtuelle * sizeof (unsigned));

	NbCadreMemVirtuelleLibre = NombreCadreMemoireVirtuelle;

	for (i = 0; i < NombreCadreMemoireVirtuelle; ++i)
		CadrePageMemVirtuelleRestante [i] = TailleCadrePages;

	if (MemoireManquante > 0)
		CadrePageMemVirtuelleRestante [i - 1] = MemoireManquante;

} // CalculDuNombreDeCadre ()

void AccesMemProc (SProcessus * Proc)
{
	srand (time (NULL));
	unsigned PageChoisie = random () % Proc->NbPageEnMemoire + 1;
	
	printf("Process %d executing page %d\n", Proc->IDProc, PageChoisie);
	
	int i =  0;
	
	// Premier remplissage
	for ( ; i < NombreCadreMemoireVive; ++i)
	{
		if (MemVive [i] != NULL) continue;
		
		MemVive [i]->IDProc = Proc->IDProc;
		MemVive [i]->PageProc = PageChoisie;
	}
	
	// Algorithme de la seconde chance
	
	
} // AccesMemProc ()


