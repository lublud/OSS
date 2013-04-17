/**
 *
 * @file: affichage.c
 *
 * @author: Tom CHASSAGNE && Ludovic LUBEIGT
 *
 * @date: 10/04/13
 *
 * @brief: fonctions d'affichage du projet de système d'exploitation
 *
 **/

#include <stdio.h>


int MenuChoix ()
{
	char Rep [64];
	
	printf ("=== OSS - Operating System Simulator ===\n");
	printf ("1 - New process\n");
	printf ("2 - Process(es) in the run queue\n");
	printf ("3 - Diplay memory\n");
	printf ("Choix : ");

	fflush (stdin);
	gets (&Rep);
	int Choix = atoi (&Rep);
	
	if (Choix > 0 && Choix < 4) return Choix;
	else return 0;

} // MenuChoix ()

