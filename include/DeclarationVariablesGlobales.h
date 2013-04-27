/**
 *
 * @file: 	DeclarationVariablesGlobales.h
 *
 * @author: Tom CHASSAGNE && Ludovic LUBEIGT
 *
 * @date: 	17/04/13
 *
 * @brief:	Liste des variables globales utilisée dans les fichiers sources.
 *
**/

FILE * SortieAffichage;

unsigned TailleMemoireVive, TailleMemoireVirtuelle, TailleCadrePages, Quantum;
unsigned NombreCadreMemoireVive, NombreCadreMemoireVirtuelle;
unsigned NbCadreMemVirtuelleLibre;
unsigned NbOrdonnancement;
unsigned NouveauProc = 0;
unsigned NbProc = 0;
unsigned CalculPriorite = 0;

char *ListeNouveauProc;

unsigned CursFileAttente [5];

unsigned CurseurMem = 0;

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

unsigned *CadrePageMemVirtuelleRestante;

SMemoire ** MemVive;
SMemoire ** MemVirtuelle;

SProcessus * ListePriorite [5][256];
