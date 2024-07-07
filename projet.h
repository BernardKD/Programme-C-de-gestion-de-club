#ifndef _PROJET_
    #define _PROJET_
	struct membre{
		char noms[30];
		char prenoms[30];
		int numero;
		char numero1[20];
		char numero2[20];
		char role[30];
		int tranches;
		float paiement;			
		char coordonnees[30];
		char horaires[11];
	};	
	struct tache{
		char responsable[30];
		int numero;
		char libelle[30];
		float budget;			
		char statut[25];
		char datefin[10];
	};
	struct ressource{
		char nom[30];
		char type[5];
		int quantite;
		int numero;
		int reservee;
		float prixunitaire;
	};
	float calculerCotisationsTotales(struct membre *m, int totalmembres);
	float calculerBudgetTotal(struct tache *t, struct ressource *r, int totaltaches, int totalressources);
	float calculerDepensesTotal(struct tache *t, int totaltaches);
	void afficherMembresImpaye(struct membre *t, int totalmembres);
	void afficherProjetsRealises(struct tache *t, int totaltaches);
	void afficherStatistiques(struct membre *m, int totalmembres, struct tache *t, int totaltaches, struct ressource *r, int totalressources);
	int nombremembresf();
	int nombretachesf();
	int nombreressourcesf();
	void miseajourmembresd(struct membre **t, int *totalmembres);
	void miseajourtachesd(struct tache **t, int *totaltaches);
	void miseajourressourcesd(struct ressource **t, int *totalressources);
	void miseajourmembresf(struct membre *t, int totalmembres);
	void miseajourtachesf(struct tache *t, int totaltaches);
	void miseajourressourcesf(struct ressource *t, int totalressources);
	void afficherStatistiquesf(struct membre *m, int totalmembres, struct tache *t, int totaltaches, struct ressource *r, int totalressources);
	void affichermembres(struct membre *t, int totalmembres);
	void affichertaches(struct tache *t, int totaltaches);
	void afficherressources(struct ressource *t, int totalressources);
	void affichernombremembres(int totalmembres);
	void affichernombretaches(int totaltaches);
	void affichernombreressources(int totalressources);
	void ajoutermembres(struct membre **t, int *totalmembres);
    void ajoutertaches(struct tache **t, int *totaltaches);
	void ajouterressources(struct ressource **t, int *totalressources);
	void modifiermembres(struct membre **t, int totalmembres);
	void modifiertaches(struct tache **t, int totaltaches);
	void modifierressources(struct ressource **t, int totalressources);
	void planifierressources(struct ressource **t, int totalressources);
	void supprimermembres(struct membre **t, int *totalmembres);
	void supprimertaches(struct tache **t, int *totaltaches);
	void supprimerressources(struct ressource **t, int *totalressources);
#endif
