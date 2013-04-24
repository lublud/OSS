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

//SProcessus **CadrePageMemVive;
unsigned *CadrePageMemViveRestante;
//SProcessus **CadrePageMemVirtuelle;
unsigned *CadrePageMemVirtuelleRestante;

SMemoire ** MemVive;
SMemoire ** MemVirtuelle;

SProcessus * Proc [256];

SProcessus * ListePriorite [5][256];
unsigned * FileAttente [5][256];
