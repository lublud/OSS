/**
 *
 * @file: DeclarationVariablesGlobales.h
 *
 * @author: Tom CHASSAGNE && Ludovic LUBEIGT
 *
 * @date: 17/04/13
 *
 * @brief Liste des variables globales utilisée dans les fichiers sources.
 *
**/


unsigned TailleMemoireVive, TailleMemoireVirtuelle, TailleCadrePages, Quantum;
unsigned NombreCadreMemoireVive, NombreCadreMemoireVirtuelle;
unsigned NbCadreMemVirtuelleLibre;
unsigned NbOrdonnancement;
unsigned NouveauProc = 0;
unsigned NbProc = 0;

unsigned CursFileAttente [5];

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

unsigned *CadrePageMemViveRestante;
unsigned *CadrePageMemVirtuelleRestante;

SMemoire ** MemVive;
SMemoire ** MemVirtuelle;

SProcessus * Proc [256];

SProcessus * ListePriorite [5][256];
