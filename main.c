#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include<unistd.h>
#include<math.h>
#include<time.h>
#include"projet.h"
int main()
{
	int num1=0, num2=0, num3=0;
	char n[10], str[30];
	float fraisInscription=5000.00000;
	struct membre *Membre = NULL;
	struct tache *Tache = NULL;
	struct ressource *Ressource = NULL;
	system("clear");
	miseajourmembresd(&Membre,&num1);
	miseajourtachesd(&Tache,&num2);
	miseajourressourcesd(&Ressource,&num3);
	do{
		system("clear");
		printf("###############GESTION D'UN CLUB################\n");
		printf("1- Gestion des membres\n2- Gestion des taches\n3- Gestion des ressources\n4- Suivi des budgets et statistiques\n0- Quitter\n");
		printf("Entrez le chiffre correspondant à votre choix : ");
		scanf("%s",n);	
		switch (n[0])
		{
			case '1' :
				system("clear");
				do{
					system("clear");
					printf("###############GESTION DES MEMBRES################\n");
					printf("1- Afficher les membres\n2- Enregistrer des membres\n3- Mettre à jour un membre\n4- Supprimer un membre\n5- Afficher le total des membres\n6- Retour au menu principal\n0- Quitter\n");
					printf("Entrez le chiffre correspondant à votre choix : ");
					scanf("%s",n);	
					switch (n[0])
					{
						case '1' :
							system("clear");
							affichermembres(Membre,num1);
							break;

						case '2' :
							system("clear");
							ajoutermembres(&Membre,&num1);
							break;

						case '3' :
							system("clear");
							modifiermembres(&Membre,num1);
							break;

						case '4' :
							system("clear");
							supprimermembres(&Membre,&num1);
							break;

						case '5' :
							system("clear");
							affichernombremembres(num1);
							break;

						case '6' :
							system("clear");
							break;

						case '0' :
							system("clear");
							break;

						default:
							printf("\nErreur ! Veuillez choisir une option valable.\n");
							sleep(1);
						break;
					}
					printf("\n");
				}while(n[0] != '0' && n[0] != '6');
				break;

			case '2' :
				system("clear");
				do{
					system("clear");
					printf("###############GESTION DES TACHES################\n");
					printf("1- Afficher les taches\n2- Enregistrer des taches\n3- Mettre à jour une tache\n4- Supprimer une tache\n5- Afficher le total des taches\n6- Retour au menu principal\n0- Quitter\n");
					printf("Entrez le chiffre correspondant à votre choix : ");
					scanf("%s",n);	
					switch (n[0])
					{
						case '1' :
							system("clear");
							affichertaches(Tache,num2);
							break;

						case '2' :
							system("clear");
							ajoutertaches(&Tache,&num2);
							break;

						case '3' :
							system("clear");
							modifiertaches(&Tache,num2);
							break;

						case '4' :
							system("clear");
							supprimertaches(&Tache,&num2);
							break;

						case '5' :
							system("clear");
							affichernombretaches(num2);
							break;

						case '6' :
							system("clear");
							break;

						case '0' :
							system("clear");
							break;

						default:
							printf("\nErreur ! Veuillez choisir une option valable.\n");
							sleep(1);
						break;
					}
					printf("\n");
				}while(n[0] != '0' && n[0] != '6');
				break;

			case '3' :
				system("clear");
				do{
					system("clear");
					printf("###############GESTION DES RESSOURCES################\n");
					printf("1- Afficher les ressources\n2- Enregistrer des ressouces\n3- Mettre à jour une ressource\n4- Supprimer une ressource\n5- Réserver ou libérer une ressource\n6- Afficher le total des ressources\n7- Retour au menu principal\n0- Quitter\n");
					printf("Entrez le chiffre correspondant à votre choix : ");
					scanf("%s",n);	
					switch (n[0])
					{
						case '1' :
							system("clear");
							afficherressources(Ressource,num3);
							break;

						case '2' :
							system("clear");
							ajouterressources(&Ressource,&num3);
							break;

						case '3' :
							system("clear");
							modifierressources(&Ressource,num3);
							break;

						case '4' :
							system("clear");
							supprimerressources(&Ressource,&num3);
							break;

						case '5' :
							system("clear");
							planifierressources(&Ressource,num3);
							break;

						case '6' :
							system("clear");
							affichernombreressources(num3);
							break;

						case '7' :
							system("clear");
							break;

						case '0' :
							system("clear");
							break;

						default:
							printf("\nErreur ! Veuillez choisir une option valable.\n");
							sleep(1);
						break;
					}
					printf("\n");
				}while(n[0] != '0' && n[0] != '7');
				break;

			case '4' :

				
				system("clear");
				do{
					system("clear");
					printf("###############SUIVI DES BUDGETS ET STATISTIQUES################\n");
					printf("1- Definir le montant des frais d'inscription\n2- Afficher les statistiques\n3- Retour au menu principal\n0- Quitter\n");
					printf("Entrez le chiffre correspondant à votre choix : ");
					scanf("%s",n);	
					switch (n[0])
					{
						case '1' :
							system("clear");
							printf("Le montant actuel des frais d'incription est %f \n Entrez le nouveau montant : ",fraisInscription);
							scanf("%s",str);
							fraisInscription = (float) convertChartoFloat(str);
							printf("Le montant des frais d'incription a été mis à jour à %f avec succès !\n",fraisInscription);
							sleep(2);
							break;

						case '2' :
							system("clear");
							afficherStatistiques(Membre,num1,Tache,num2,Ressource,num3,fraisInscription);
							sleep(10);
							break;
						case '3' :
							system("clear");
							break;

						case '0' :
							system("clear");
							break;

						default:
							printf("\nErreur ! Veuillez choisir une option valable.\n");
							sleep(1);
						break;
					}
					printf("\n");
				}while(n[0] != '0' && n[0] != '3');
				break;

			case '0' :
				system("clear");
				break;

			default:
				printf("\nErreur ! Veuillez choisir une option valable.\n");
				sleep(1);
			break;
		}
	}while(n[0] != '0');	
	miseajourmembresf(Membre,num1);
	miseajourtachesf(Tache,num2);
	miseajourressourcesf(Ressource,num3);
	afficherStatistiquesf(Membre,num1,Tache,num2,Ressource,num3,fraisInscription);
	free(Membre);
	free(Tache);
	free(Ressource);
	printf("Au revoir!\n");
	sleep(1);
	system("clear");
	return 0;
}
