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
		fprintf(SortieAffichage, "\033[31m Error: Out of virtual memory\033[0m\n");
		return -1;
	}
	

	NombreDePage = 0;
	for (i = 0; 0 != TailleProcTmp; ++i)
	{
		if (NULL != MemVirtuelle[i])
			continue;

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

	MemVive = (SMemoire *) malloc (NombreCadreMemoireVive * sizeof (SMemoire));


	/* Mémoire virtuelle */
	NombreCadreMemoireVirtuelle = TailleMemoireVirtuelle / TailleCadrePages;

	MemoireManquante = TailleMemoireVirtuelle - (TailleCadrePages * NombreCadreMemoireVirtuelle);
	if (MemoireManquante > 0)
		++NombreCadreMemoireVirtuelle;

	printf ("Virtual memory creation (%d frame(s))\n", NombreCadreMemoireVirtuelle);

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
	unsigned PageChoisie = random () %  Proc->NbPageEnMemoire;

	fprintf(SortieAffichage, "Process %d executing page %d\n", Proc->IDProc, PageChoisie);


	int i;

	// On vérifie si la page est déjà en vive
	for (i = 0; i < NombreCadreMemoireVive; ++i)
	{
		if (MemVive[i] != NULL &&
			MemVive[i]->IDProc == Proc->IDProc &&
			MemVive[i]->PageProc == PageChoisie)
		{
			MemVive[i]->BitRef = 1;
			break;
		}
	}

	// Algorithme de la seconde chance pour ajouter la page en mémoire vive

	// Si la page n'est pas en mémoire vive, on fait la seconde chance
	if (i == NombreCadreMemoireVive)
	{
		fprintf(SortieAffichage, "-> Loading page %d of process %d\n", PageChoisie, Proc->IDProc);

		// On cherche la case dans la mémoire virtuelle pour la supprimer
		for (i = 0; i < NombreCadreMemoireVirtuelle; ++i)
		{
			if (MemVirtuelle[i] != NULL &&
				MemVirtuelle[i]->IDProc == Proc->IDProc &&
				MemVirtuelle[i]->PageProc == PageChoisie)
			{
				MemVirtuelle[i] = NULL;
				++NbCadreMemVirtuelleLibre;
				CadrePageMemVirtuelleRestante[i] += TailleCadrePages;
				break;
			}
		}
		
		// On cherche la case où ajouter dans la vive
		for ( ; ; ++CurseurMem)
		{
			// Si on est à la fin, on revient au début
			if (CurseurMem == NombreCadreMemoireVive)
				CurseurMem = 0;
			
			// Si la case est vide
			if (MemVive[CurseurMem] == NULL)
			{
				// On met la nouvelle dedans
				MemVive[CurseurMem] = (SMemoire *) malloc (sizeof (SMemoire));
				MemVive[CurseurMem]->IDProc = Proc->IDProc;
				MemVive[CurseurMem]->PageProc = PageChoisie;
				MemVive[CurseurMem]->BitRef = 1;
				++CurseurMem;
				break;
			}

			if (1 == MemVive[CurseurMem]->BitRef)
				MemVive[CurseurMem]->BitRef = 0;
			else
			{
				fprintf(SortieAffichage, "-> Saving page %d of process %d\n", MemVive[CurseurMem]->PageProc, MemVive[CurseurMem]->IDProc);
				
				int FirstFreeVirtuelle = 0;
				// On cherche la première place dans la virtuelle
				for ( ; FirstFreeVirtuelle < NombreCadreMemoireVirtuelle; ++FirstFreeVirtuelle)
					if (MemVirtuelle[FirstFreeVirtuelle] == NULL) break;

				// On remet l'ancienne de la vive dans la virtuelle
				MemVirtuelle[FirstFreeVirtuelle] = (SMemoire *) malloc (sizeof (SMemoire));
				MemVirtuelle[FirstFreeVirtuelle]->IDProc = MemVive[CurseurMem]->IDProc;
				MemVirtuelle[FirstFreeVirtuelle]->PageProc = MemVive[CurseurMem]->PageProc;

				// On met la nouvelle dans la vive
				MemVive[CurseurMem]->IDProc = Proc->IDProc;
				MemVive[CurseurMem]->PageProc = PageChoisie;
				MemVive[CurseurMem]->BitRef = 1;
				++CurseurMem;
				break;
			}
		}
	}
	

	sleep (1);

} // AccesMemProc ()


