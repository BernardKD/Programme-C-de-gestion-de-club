#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include<unistd.h>
#include<time.h>
#include"projet.h"

float calculerCotisationsTotales(struct membre *m, int totalmembres){
    float cotisationsTotal = 0;
    for(int i = 0; i < totalmembres; i++){
        cotisationsTotal += m[i].paiement;
    }
    return cotisationsTotal;
}

float calculerBudgetTotal(struct tache *t, struct ressource *r, int totaltaches, int totalressources){
    float budgetTotal = 0;
    for(int i = 0; i < totaltaches; i++){
		budgetTotal += t[i].budget;
    }
	for(int j = 0; j < totalressources; j++){
		budgetTotal += r[j].prixunitaire*r[j].quantite;
    }
    return budgetTotal;
}

float calculerDepensesTotal(struct tache *t, int totaltaches){
    float depensesTotal = 0;
    for(int i = 0; i < totaltaches; i++){
        if(strcmp(t[i].statut, "Terminée") == 0){
            depensesTotal += t[i].budget;
        }
    }
    return depensesTotal;
}

void afficherMembresImpaye(struct membre *t, int totalmembres){
    printf("\n====== Membres n'ayant pas payé la totalité de leurs frais d'inscription ======\n");
	float fonds = 5000.000000;
    for(int i = 0; i < totalmembres; i++){
        if(t[i].paiement < fonds){
            printf("Noms : %s\nPrenoms : %s\nCotisation payée : %.2f / %.2f\n\n", t[i].noms, t[i].prenoms, t[i].paiement, fonds);
        }
    }
}

void afficherProjetsRealises(struct tache *t, int totaltaches){
    printf("\n=============================== Projets réalisés ===============================\n");
	for(int i = 0; i < totaltaches; i++){
        if(strcmp(t[i].statut, "Terminée") == 0){
            printf("Nom de la tâche : %s\nBudget : %.2f\n\n", t[i].libelle, t[i].budget);
        }
    }
}

void afficherStatistiques(struct membre *m, int totalmembres, struct tache *t, int totaltaches, struct ressource *r, int totalressources){
    printf("============================== Statistiques du club ==============================\n\n");
	
    float budgetTotal = calculerBudgetTotal(t, r, totaltaches, totalressources);
    printf("Budget total du club: %.2f\n", budgetTotal);
	
    float depensesTotal = calculerDepensesTotal(t, totaltaches);
    printf("Total des dépenses du club: %.2f\n", depensesTotal);
	
    float budgetRestant = budgetTotal - depensesTotal;
    printf("Budget restant du club: %.2f\n", budgetRestant);

    float cotisationsTotal = calculerCotisationsTotales(m, totalmembres);
    printf("Total des cotisations payées: %.2f\n", cotisationsTotal);

    printf("Nombre de membres: %d\n", totalmembres);
    printf("Nombre de tâches: %d\n", totaltaches);
    printf("Nombre de ressources: %d\n", totalressources);

    int tachesTerminees = 0;
    for(int i = 0; i < totaltaches; i++){
        if(strcmp(t[i].statut, "Terminée") == 0){
            tachesTerminees++;
        }
    }
    printf("Nombre de tâches terminées: %d\n", tachesTerminees);
	
    int ressourcesReservees = 0;
	int dons=0;
    for(int i = 0; i < totalressources; i++){
        if(r[i].reservee > 0){
            ressourcesReservees++;
        }
		if(strcmp(r[i].type,"Don")==0){
            dons++;
        }
    }
    printf("Nombre de ressources réservées: %d\n", ressourcesReservees);
	printf("Nombre de dons: %d\n", dons);
	afficherMembresImpaye(m, totalmembres);
    afficherProjetsRealises(t, totaltaches);
}

int nombremembresf(){
	FILE *f;
	f=fopen("membres.txt","r");
	int i=0, totalmembres;
	char d;
	if(f==NULL){
		printf("Erreur lors de l'ouverture du fichier !");
		return 0;
	}
	if((d = fgetc(f)) == EOF){
		printf("Le fichier est vide !");
		fclose(f);
		return 0;
	}
	while((d = fgetc(f)) != EOF){
    	if(d == '\n')
      	    i++;
	}
	totalmembres = i/11;
	sleep(1);
	fclose(f);
	return totalmembres;
}

int nombretachesf(){
	FILE *f;
	f=fopen("taches.txt","r");
	int i=0, totaltaches;
	char d;
	if(f==NULL){
		printf("Erreur lors de l'ouverture du fichier !");
		return 0;
	}
	if((d = fgetc(f)) == EOF){
		printf("Le fichier est vide !");
		fclose(f);
		return 0;
	}
	while((d = fgetc(f)) != EOF){
    	if(d == '\n')
      	    i++;
	}
	totaltaches = i/7;
	sleep(1);
	fclose(f);
	return totaltaches;
}

int nombreressourcesf(){
	FILE *f;
	f=fopen("ressources.txt","r");
	int i=0, totalressources;
	char d;
	if(f==NULL){
		printf("Erreur lors de l'ouverture du fichier !");
		return 0;
	}
	if((d = fgetc(f)) == EOF){
		printf("Le fichier est vide !");
		fclose(f);
		return 0;
	}
	while((d = fgetc(f)) != EOF){
    	if(d == '\n')
      	    i++;
	}
	totalressources = i/7;
	sleep(1);
	fclose(f);
	return totalressources;
}

void miseajourmembresd(struct membre **t, int *totalmembres){
	FILE *f;
    char d;
    f=fopen("membres.txt","r");
    if(f==NULL){
        printf("Erreur lors de l'ouverture du fichier !");
        return;
    }

    *totalmembres = nombremembresf();
    *t = realloc(*t, (*totalmembres)*sizeof(struct membre));

    if(*t==NULL){
        printf("Erreur lors de l'allocation\n");
        fclose(f);
        return;
    }

    for(int i=0; i<*totalmembres; i++){
        
        // Récupération du numéro du membre
        while((d = fgetc(f)) != ' '){
            ;
        }
        fscanf(f, "%d", &((*t)[i].numero));

        // Récupération du nom
        while((d = fgetc(f)) != ':'){
            ;
        }
        fscanf(f, "%s", (*t)[i].noms);

        // Récupération du prenom
        while((d = fgetc(f)) != ':'){
            ;
        }
        fscanf(f, "%s", (*t)[i].prenoms);

		// Récupération du numero1
        while((d = fgetc(f)) != ':'){
            ;
        }
        fscanf(f, "%s", (*t)[i].numero1);

		// Récupération du numero2
        while((d = fgetc(f)) != ':'){
            ;
        }
        fscanf(f, "%s", (*t)[i].numero2);

		// Récupération du role
        while((d = fgetc(f)) != ':'){
            ;
        }
        fscanf(f, "%s", (*t)[i].role);

		// Récupération du nombre de tranches
        while((d = fgetc(f)) != ':'){
            ;
        }
        fscanf(f, "%d", &((*t)[i].tranches));

        // Récupération du paiement
        while((d = fgetc(f)) != ':'){
            ;
        }
        fscanf(f, "%f", &((*t)[i].paiement));

        // Récupération des coordonnees
        while((d = fgetc(f)) != ':'){
            ;
        }
        fscanf(f, "%s", (*t)[i].coordonnees);

        // Récupération des horaires
        while((d = fgetc(f)) != ':'){
            ;
        }
        fscanf(f, "%s", (*t)[i].horaires);

        // Sauter la ligne d'espacement
        while((d = fgetc(f)) != '\n'){
            ;
        }
    }

    printf("Les membres ont été synchronisées avec succès\n");
    fclose(f);
    return;
}

void miseajourtachesd(struct tache **t, int *totaltaches){
	FILE *f;
    char d;
    f=fopen("taches.txt","r");
    if(f==NULL){
        printf("Erreur lors de l'ouverture du fichier !");
        return;
    }

    *totaltaches = nombretachesf();
    *t = realloc(*t, (*totaltaches)*sizeof(struct tache));

    if(*t==NULL){
        printf("Erreur lors de l'allocation\n");
        fclose(f);
        return;
    }

    for(int i=0; i<*totaltaches; i++){
        
        // Récupération du numéro de la tâche
        while((d = fgetc(f)) != ' '){
            ;
        }
        fscanf(f, "%d", &((*t)[i].numero));

        // Récupération du responsable
        while((d = fgetc(f)) != ':'){
            ;
        }
        fscanf(f, "%s", (*t)[i].responsable);

        // Récupération du libellé
        while((d = fgetc(f)) != ':'){
            ;
        }
        fscanf(f, "%s", (*t)[i].libelle);

        // Récupération du budget
        while((d = fgetc(f)) != ':'){
            ;
        }
        fscanf(f, "%f", &((*t)[i].budget));

        // Récupération du statut
        while((d = fgetc(f)) != ':'){
            ;
        }
        fscanf(f, "%s", (*t)[i].statut);

        // Récupération de la date de fin
        while((d = fgetc(f)) != ':'){
            ;
        }
        fscanf(f, "%s", (*t)[i].datefin);

        // Sauter la ligne d'espacement
        while((d = fgetc(f)) != '\n'){
            ;
        }
    }

    printf("Les tâches ont été synchronisées avec succès\n");
    fclose(f);
    return;
}

void miseajourressourcesd(struct ressource **t, int *totalressources){
	FILE *f;
    char d;
    f=fopen("ressources.txt","r");
    if(f==NULL){
        printf("Erreur lors de l'ouverture du fichier !");
        return;
    }

    *totalressources = nombreressourcesf();
    *t = realloc(*t, (*totalressources)*sizeof(struct ressource));

    if(*t==NULL){
        printf("Erreur lors de l'allocation\n");
        fclose(f);
        return;
    }

    for(int i=0; i<*totalressources; i++){

        // Récupération du numéro de la ressource
        while((d = fgetc(f)) != ' '){
            ;
        }
        fscanf(f, "%d", &((*t)[i].numero));

        // Récupération du nom
        while((d = fgetc(f)) != ':'){
            ;
        }
        fscanf(f, "%s", (*t)[i].nom);

		// Récupération du type
        while((d = fgetc(f)) != ':'){
            ;
        }
        fscanf(f, "%s", (*t)[i].type);

		// Récupération de la quantite
        while((d = fgetc(f)) != ':'){
            ;
        }
        fscanf(f, "%d", &((*t)[i].quantite));

       	// Récupération du nombre de ressources reservees
        while((d = fgetc(f)) != ':'){
            ;
        }
        fscanf(f, "%d", &((*t)[i].reservee));

		// Récupération du prix unitaire de la ressource
        while((d = fgetc(f)) != ':'){
            ;
        }
        fscanf(f, "%f", &((*t)[i].prixunitaire));

        // Sauter la ligne d'espacement
        while((d = fgetc(f)) != '\n'){
            ;
        }
    }

    printf("Les ressources ont été synchronisées avec succès\n");
    sleep(1);
    fclose(f);
    return;
}

void miseajourmembresf(struct membre *t, int totalmembres){
	FILE *f;
    f=fopen("membres.txt","w");
    if(f==NULL){
        printf("Erreur lors de l'ouverture du fichier !");
        return;
    }

    for(int i=0; i<totalmembres; i++){
        fprintf(f,"Membre N* %d\nNoms : %s\nPrenoms : %s\nNumero1 : %s\nNumero2 : %s\nRole : %s\nTranches : %d\nPaiement : %f\nCoordonnees : %s\nHoraires : %s\n\n",i+1,t[i].noms,t[i].prenoms,t[i].numero1,t[i].numero2,t[i].role,t[i].tranches,t[i].paiement,t[i].coordonnees,t[i].horaires);
    }

    printf("Les membres ont été mis à jour avec succès !\n");
    sleep(0.5);
    fclose(f);
    return;
}

void miseajourtachesf(struct tache *t, int totaltaches){
	FILE *f;
    f=fopen("taches.txt","w");
    if(f==NULL){
        printf("Erreur lors de l'ouverture du fichier !");
        return;
    }

    for(int i=0; i<totaltaches; i++){
        fprintf(f,"Tache N* %d\nResponsable : %s\nLibelle : %s\nBudget : %f\nStatut : %s\nDate de fin : %s\n\n",i+1,t[i].responsable,t[i].libelle,t[i].budget,t[i].statut,t[i].datefin);
    }

    printf("Les taches ont été mis à jour avec succès !\n");
    sleep(0.5);
    fclose(f);
    return;
}

void miseajourressourcesf(struct ressource *t, int totalressources){
	FILE *f;
    f=fopen("ressources.txt","w");
    if(f==NULL){
        printf("Erreur lors de l'ouverture du fichier !");
        return;
    }

    for(int i=0; i<totalressources; i++){
        fprintf(f,"Ressource N* %d\nNom : %s\nType : %s\nQuantite : %d\nReservee : %d\nPrix unitaire : %f\n\n",i+1,t[i].nom,t[i].type,t[i].quantite,t[i].reservee,t[i].prixunitaire);
    }

    printf("Les ressources ont été mis à jour avec succès !\n");
    sleep(0.5);
    fclose(f);
    return;
}

void afficherStatistiquesf(struct membre *m, int totalmembres, struct tache *t, int totaltaches, struct ressource *r, int totalressources){
	FILE *f = fopen("projet.txt","w");
	if(f==NULL){
		printf("Erreur lors de l'ouverture du fichier !");
		return;
	}
    fprintf(f,"#######################STATISTIQUES DU CLUB#######################\n\n\n");

    float budgetTotal = calculerBudgetTotal(t, r, totaltaches, totalressources);
    fprintf(f,"Budget total du club: %.2f\n\n", budgetTotal);

    float depensesTotal = calculerDepensesTotal(t, totaltaches);
    fprintf(f,"Total des dépenses du club: %.2f\n\n", depensesTotal);

    float budgetRestant = budgetTotal - depensesTotal;
    fprintf(f,"Budget restant du club: %.2f\n\n", budgetRestant);

    float cotisationsTotal = calculerCotisationsTotales(m, totalmembres);
   	fprintf(f,"Total des cotisations payées: %.2f\n\n", cotisationsTotal);

   	fprintf(f,"Nombre de membres: %d\n", totalmembres);
    fprintf(f,"Nombre de tâches: %d\n", totaltaches);
    fprintf(f,"Nombre de ressources: %d\n\n", totalressources);

    int tachesTerminees = 0;
    for(int i = 0; i < totaltaches; i++){
        if(strcmp(t[i].statut, "Terminée") == 0){
            tachesTerminees++;
        }
    }
    fprintf(f,"Nombre de tâches terminées: %d\n\n", tachesTerminees);

    int ressourcesReservees = 0;
	int dons=0;
    for(int i = 0; i < totalressources; i++){
        if(r[i].reservee > 0){
            ressourcesReservees++;
        }
		if(strcmp(r[i].type,"Don")==0){
            dons++;
        }
    }
    fprintf(f,"Nombre de ressources réservées: %d\n\n", ressourcesReservees);
	fprintf(f,"Nombre de dons: %d\n\n", dons);

	fprintf(f,"\n==Membres n'ayant pas payé la totalité de leurs frais d'inscription==\n\n");
	float fonds = 5000.000000;
    for(int i = 0; i < totalmembres; i++){
        if(m[i].paiement < fonds){
			fprintf(f,"Noms : %s\nPrenoms : %s\nCotisation payée : %.2f / %.2f\n\n", m[i].noms, m[i].prenoms, m[i].paiement, fonds);
        }
    }
	
	fprintf(f,"\n=============================Projets réalisés=========================\n\n");
    for(int i = 0; i < totaltaches; i++){
        if(strcmp(t[i].statut, "Terminée") == 0){
            fprintf(f,"Nom de la tâche : %s\nBudget : %.2f\n\n", t[i].libelle, t[i].budget);
        }
    }
	fclose(f);
	return;
}

void affichermembres(struct membre *t, int totalmembres){
	if(totalmembres==0)
		printf("\nAucun membre n'est enregistré !\n\n");
	else{
		printf("Liste des membres enregistrés :\n\n");
		for(int i=0; i<totalmembres; i++){
			printf("Membre N* %d\n",i+1);
			printf("Noms : %s\n",t[i].noms);
			printf("Prenoms : %s\n",t[i].prenoms);
			printf("Numero1 : %s\n",t[i].numero1);
			printf("Numero2 : %s\n",t[i].numero2);
			printf("Role : %s\n",t[i].role);
			printf("Tranches : %d\n",t[i].tranches);
			printf("Paiement : %f\n",t[i].paiement);
			printf("Coordonnees : %s\n",t[i].coordonnees);
			printf("Horaires : %s\n",t[i].horaires);
			printf("\n");
		}
		sleep(totalmembres);
	}
	sleep(1);
	return;
}

void affichertaches(struct tache *t, int totaltaches){
	if(totaltaches==0)
		printf("\nAucune tache n'est enregistrée !\n\n");
	else{
		printf("Liste des taches enregistrées :\n\n");
		for(int i=0; i<totaltaches; i++){
			printf("Tache N* %d\n",i+1);
			printf("Responsable : %s\n",t[i].responsable);
			printf("Libelle : %s\n",t[i].libelle);
			printf("Budget : %f\n",t[i].budget);
			printf("statut : %s\n",t[i].statut);
			printf("Date de fin : %s\n",t[i].datefin);
			printf("\n");
		}
		sleep(totaltaches);
	}
	sleep(1);
	return;
}

void afficherressources(struct ressource *t, int totalressources){
	if(totalressources==0)
		printf("\nAucune ressource n'est enregistrée !\n");
	else{
		printf("Liste des ressources enregistrées :\n\n");
		for(int i=0; i<totalressources; i++){
			printf("Ressource N* %d\n",i+1);
			printf("Nom : %s\n",t[i].nom);
			printf("Type : %s\n",t[i].type);
			printf("Quantite : %d\n",t[i].quantite);
			printf("Reservee : %d\n",t[i].reservee);
			printf("Prix unitaire : %f\n",t[i].prixunitaire);
			printf("\n");
		}
		sleep(totalressources);
	}
	sleep(1);
	return;
}

void affichernombremembres(int totalmembres){
	printf("Le total de membres enregistrees est : %d\n",totalmembres);
	sleep(2);
}

void affichernombretaches(int totaltaches){
	printf("Le total de taches enregistrees est : %d\n",totaltaches);
	sleep(2);
}

void affichernombreressources(int totalressources){
	printf("Le total de ressources enregistrees est : %d\n",totalressources);
	sleep(2);
}

void ajoutermembres(struct membre **t, int *totalmembres){
	
	int num;
	printf("Entrez le nombre de membres a ajouter : "); 
	scanf("%d",&num);

	*t = realloc(*t, (*totalmembres + num)*sizeof(struct membre));	
	if(*t==NULL){
		printf("Erreur lors de l'allocation\n");
		return;
	}

	for(int i=0; i<num; i++){

		(*t)[*totalmembres+i].numero = *totalmembres+1;

		printf("Entrez le nom du membre %d : ",i+1);
		scanf("%s",(*t)[*totalmembres+i].noms);
		printf("Entrez le prenom du membre %d : ",i+1);
		scanf("%s",(*t)[*totalmembres+i].prenoms);
		printf("Entrez le premier numero du membre %d : ",i+1);
		scanf("%s",(*t)[*totalmembres+i].numero1);
		printf("Entrez le deuxieme numero du membre %d ou 0 s'il en a pas : ",i+1);
		scanf("%s",(*t)[*totalmembres+i].numero2);
		printf("Entrez le role du membre %d : ",i+1);
		scanf("%s",(*t)[*totalmembres+i].role);
		printf("Entrez le nombre de tranche du membre %d : ",i+1);
		scanf("%d",&(*t)[*totalmembres+i].tranches);
		printf("Entrez la somme deja payée du membre %d : ",i+1);
		scanf("%f",&(*t)[*totalmembres+i].paiement);
		printf("Entrez les coordonnees du membre %d : ",i+1);
		scanf("%s",(*t)[*totalmembres+i].coordonnees);
		printf("Entrez les horaires du membre %d : ",i+1);
		scanf("%s",(*t)[*totalmembres+i].horaires);
		
	}
	*totalmembres += num;
	printf("Les membres ont été enregistrées avec succès !\n");
	sleep(2);
	return;
}

void ajoutertaches(struct tache **t, int *totaltaches){
	
	int num;
	char chiffre='0';
	printf("Entrez le nombre de taches a ajouter : "); 
	scanf("%d",&num);

	*t = realloc(*t, (*totaltaches + num)*sizeof(struct tache));	
	if(*t==NULL){
		printf("Erreur lors de l'allocation\n");
		return;
	}

	for(int i=0; i<num; i++){
		
		(*t)[*totaltaches+i].numero=*totaltaches+1;
		
		printf("Entrez le responsable de la tache %d : ",i+1);
		scanf("%s",(*t)[*totaltaches+i].responsable);
		printf("Entrez le libelle de la tache %d : ",i+1);
		scanf("%s",(*t)[*totaltaches+i].libelle);
		printf("Entrez le budget de la tache %d : ",i+1);
		scanf("%f",&(*t)[*totaltaches+i].budget);
		printf("Entrez le chiffre correspondant au statut de la tache %d (Entrez 0 pour \"En_attente_de_démarrage\", entrez 1 pour \"En_cours\" et toute autre valeure pour \"Terminée\") : ",i+1);
		scanf("%c",&chiffre);
		if(chiffre=='0')
			strcpy((*t)[*totaltaches+i].statut,"En_attente_de_démarrage");
		else if(chiffre=='1')
			strcpy((*t)[*totaltaches+i].statut,"En_cours");
		else
			strcpy((*t)[*totaltaches+i].statut,"Terminée");
		printf("Entrez la date de fin de la tache %d : ",i+1);
		scanf("%s",(*t)[*totaltaches+i].datefin);
		
	}
	*totaltaches += num;
	printf("Les taches ont été enregistrées avec succès !\n");
	sleep(2);
	return;
}

void ajouterressources(struct ressource **t, int *totalressources){
	
	int num;
	char chiffre='0';
	printf("Entrez le nombre de ressources a ajouter : "); 
	scanf("%d",&num);

	*t = realloc(*t, (*totalressources + num)*sizeof(struct ressource));	
	if(*t==NULL){
		printf("Erreur lors de l'allocation\n");
		return;
	}

	for(int i=0; i<num; i++){

		(*t)[*totalressources+i].numero=*totalressources+1;

		printf("Entrez le nom de la ressource %d : ",i+1);
		scanf("%s",(*t)[*totalressources+i].nom);
		printf("Entrez le chiffre correspondant au type de la ressource %d (Entrez 0 pour \"Don\" et toute autre valeure pour \"achat\") : ",i+1);
		scanf("%c",&chiffre);
		if(chiffre=='0')
			strcpy((*t)[*totalressources+i].type,"Don");
		else
			strcpy((*t)[*totalressources+i].type,"Achat");
		printf("Entrez la quantite de la ressource %d : ",i+1);
		scanf("%d",&(*t)[*totalressources+i].quantite);
		printf("Entrez la quantite reservee de la ressource %d : ",i+1);
		scanf("%d",&(*t)[*totalressources+i].reservee);
		printf("Entrez le prix unitaire de la ressource %d : ",i+1);
		scanf("%f",&(*t)[*totalressources+i].prixunitaire);
		
	}
	*totalressources += num;
	printf("Les ressources ont été enregistrées avec succès !\n");
	sleep(2);
	return;
}

void modifiermembres(struct membre **t, int totalmembres){
	int nu;
	printf("Entrez le numero du membre à modifier : "); 
	scanf("%d",&nu);
	if((nu==0)|(totalmembres==0)|(totalmembres<nu)|(nu<0))
		printf("Impossible ! Le membre n'exite pas\n");
	else{
		printf("Entrez le nom du membre %d : ",nu);
		scanf("%s",(*t)[nu-1].noms);
		printf("Entrez le prenom du membre %d : ",nu);
		scanf("%s",(*t)[nu-1].prenoms);
		printf("Entrez le premier numero du membre %d : ",nu);
		scanf("%s",(*t)[nu-1].numero1);
		printf("Entrez le deuxieme numero du membre %d : ",nu);
		scanf("%s",(*t)[nu-1].numero2);
		printf("Entrez le role du membre %d : ",nu);
		scanf("%s",(*t)[nu-1].role);
		printf("Entrez le nombre de traches du membre %d : ",nu);
		scanf("%d",&(*t)[nu-1].tranches);
		printf("Entrez la somme deja payee du membre %d : ",nu);
		scanf("%f",&(*t)[nu-1].paiement);
		printf("Entrez les coordonnees du membre %d : ",nu);
		scanf("%s",(*t)[nu-1].coordonnees);
		printf("Entrez les horaires du membre %d : ",nu);
		scanf("%s",(*t)[nu-1].horaires);
		printf("Le membre à été modifié avec succès !\n");
		sleep(1);
	}
	sleep(1);
	return;
}

void modifiertaches(struct tache **t, int totaltaches){
	int nu;
	char chiffre='0';
	printf("Entrez le numero de la tache à modifier : "); 
	scanf("%d",&nu);
	if((nu==0)|(totaltaches==0)|(totaltaches<nu)|(nu<0))
		printf("Impossible ! La tache n'exite pas\n");
	else{
		printf("Entrez le responsable de la tache %d : ",nu);
		scanf("%s",(*t)[nu-1].responsable);
		printf("Entrez le libelle de la tache %d : ",nu);
		scanf("%s",(*t)[nu-1].libelle);
		printf("Entrez le budget de la tache %d : ",nu);
		scanf("%f",&(*t)[nu-1].budget);
		printf("Entrez le chiffre correspondant au statut de la tache %d (Entrez 0 pour \"En_attente_de_démarrage\", entrez 1 pour \"En_cours\" et toute autre valeure pour \"Terminée\") : ",nu);
		scanf("%c",&chiffre);
		if(chiffre=='0')
			strcpy((*t)[nu-1].statut,"En_attente_de_démarrage");
		else if(chiffre=='1')
			strcpy((*t)[nu-1].statut,"En_cours");
		else
			strcpy((*t)[nu-1].statut,"Terminée");
		printf("Entrez la date de fin de la tache %d : ",nu);
		scanf("%s",(*t)[nu-1].datefin);
		printf("La tache à été modifiée avec succès !\n");
		sleep(1);
	}
	sleep(1);
	return;
}

void modifierressources(struct ressource **t, int totalressources){
	int nu;
	char chiffre='0';
	printf("Entrez le numero de la ressource à modifier : "); 
	scanf("%d",&nu);
	if((nu==0)|(totalressources==0)|(totalressources<nu)|(nu<0))
		printf("Impossible ! La ressource n'exite pas\n");
	else{
		printf("Entrez le nom de la ressource %d : ",nu);
		scanf("%s",(*t)[nu-1].nom);
		printf("Entrez le chiffre correspondant au type de la ressource %d (Entrez 0 pour \"Don\" et toute autre valeure pour \"achat\") : ",nu);
		scanf("%c",&chiffre);
		if(chiffre=='0')
			strcpy((*t)[nu-1].type,"Don");
		else
			strcpy((*t)[nu-1].type,"Achat");
		printf("Entrez la quantite de la ressource %d : ",nu);
		scanf("%d",&(*t)[nu-1].quantite);
		printf("Entrez la quantite deja reservee de la ressource %d : ",nu);
		scanf("%d",&(*t)[nu-1].reservee);
		printf("Entrez le prix unitaire de la ressource %d : ",nu);
		scanf("%f",&(*t)[nu-1].prixunitaire);
		printf("La ressource à été modifiée avec succès !\n");
		sleep(1);
	}
	sleep(1);
	return;
}

void planifierressources(struct ressource **t, int totalressources){
	int nu,qnt;
	char chiffre[10];
	if(totalressources==0){	
		printf("\nAucune ressource n'est enregistrée, Opération annulée !\n");
		sleep(1);
		return;
	}
	printf("Entrez un chiffre correspondant à l'opération à effectuer (Entrez 0 pour réserver, 1 pour liberer, 2 pour supprimer et toute autre valeure pour annuler l'opération) : "); 
	scanf("%s",chiffre);
	
	if(chiffre[0]=='0'){
		system("clear");
		afficherressources(*t,totalressources);
		printf("Entrez le numero de la ressource à réserver : "); 
		scanf("%d",&nu);
		if((nu==0)|(totalressources==0)|(totalressources<nu)|(nu<0))
			printf("Impossible ! La ressource n'exite pas\n");
		else{
			printf("Entrez la quantite à réserver de la ressource %d : ",nu);
			scanf("%d",&qnt);
			if(qnt > (*t)[nu-1].quantite - (*t)[nu-1].reservee)
				printf("Quantité non règlementaire, Opération annulée !\n");
			else{
				(*t)[nu-1].reservee += qnt;
				printf("La ressource à été réservée avec succès !\n");
			}
			sleep(1);
			return;
		}
	}else if(chiffre[0]=='1'){
		system("clear");
		afficherressources(*t,totalressources);
		printf("Entrez le numero de la ressource à libérer : "); 
		scanf("%d",&nu);
		if((nu==0)|(totalressources==0)|(totalressources<nu)|(nu<0))
			printf("Impossible ! La ressource n'exite pas\n");
		else{
			printf("Entrez la quantite à libérer de la ressource %d : ",nu);
			scanf("%d",&qnt);
			if(qnt >= (*t)[nu-1].reservee)
				printf("Quantité non règlementaire, Opération annulée !\n");
			else{
				(*t)[nu-1].reservee = (*t)[nu-1].reservee - qnt;
				printf("La ressource à été libérée avec succès !\n");
			}
			sleep(1);
			return;
		}
	}else if(chiffre[0]=='2'){
		system("clear");
		afficherressources(*t,totalressources);
		printf("Entrez le numero de la ressource à supprimer : "); 
		scanf("%d",&nu);
		if((nu==0)|(totalressources==0)|(totalressources<nu)|(nu<0))
			printf("Impossible ! La ressource n'exite pas\n");
		else{
			printf("Entrez la quantite à supprimer de la ressource %d : ",nu);
			scanf("%d",&qnt);
			if(qnt >= (*t)[nu-1].quantite - (*t)[nu-1].reservee)
				printf("Quantité non règlementaire, Opération annulée !\n");
			else{
				(*t)[nu-1].quantite = (*t)[nu-1].quantite - qnt;
				printf("La ressource à été supprimée avec succès !\n");
			}
			sleep(1);
			return;
		}
	}
	printf("Opération annulée !\n");
	sleep(1);
	return;
}

void supprimermembres(struct membre **t, int *totalmembres){
	int nu;
	printf("Entrez le numero du membre à supprimer : "); 
	scanf("%d",&nu);
	if((nu==0)|(*totalmembres==0)|(*totalmembres<nu)|(nu<0))
		printf("Impossible ! Le membre n'exite pas\n");
	else{
    	for (int i = nu-1; i < *totalmembres-1; i++) {
        	(*t)[i] = (*t)[i+1];
    	}
		*t = realloc(*t, (*totalmembres - 1)*sizeof(struct membre));
		*totalmembres -= 1;
		printf("Le membre à été supprimé avec succès !\n");
		sleep(1);
	}
	sleep(1);
	return;
}

void supprimertaches(struct tache **t, int *totaltaches){
	int nu;
	printf("Entrez le numero de la tache à supprimer : "); 
	scanf("%d",&nu);
	if((nu==0)|(*totaltaches==0)|(*totaltaches<nu)|(nu<0))
		printf("Impossible ! La tache n'exite pas\n");
	else{
    	for (int i = nu-1; i < *totaltaches-1; i++) {
        	(*t)[i] = (*t)[i+1];
    	}
		*t = realloc(*t, (*totaltaches - 1)*sizeof(struct tache));
		*totaltaches -= 1;
		printf("La tache à été supprimée avec succès !\n");
		sleep(1);
	}
	sleep(1);
	return;
}

void supprimerressources(struct ressource **t, int *totalressources){
	int nu;
	printf("Entrez le numero de la ressource à supprimer : "); 
	scanf("%d",&nu);
	if((nu==0)|(*totalressources==0)|(*totalressources<nu)|(nu<0))
		printf("Impossible ! La ressource n'exite pas\n");
	else{
    	for (int i = nu-1; i < *totalressources-1; i++) {
        	(*t)[i] = (*t)[i+1];
    	}
		*t = realloc(*t, (*totalressources - 1)*sizeof(struct ressource));
		*totalressources -= 1;
		printf("La ressource à été supprimée avec succès !\n");
		sleep(1);
	}
	sleep(1);
	return;
}
