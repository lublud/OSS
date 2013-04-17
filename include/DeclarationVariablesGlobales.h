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

SProcessusEnMemoire **CadrePageMemVive;
unsigned *CadrePageMemViveRestante;
SProcessusEnMemoire **CadrePageMemVirtuelle;
unsigned *CadrePageMemVirtuelleRestante;

SProcessus * Proc [256];
