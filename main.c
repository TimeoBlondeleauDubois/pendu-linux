#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int main(void) {
  int recommencer_gagner = 1;
  int compteur_de_win = 0;
  while (recommencer_gagner == 1) {


  //Initialisation des variables pour "le prendre un mot aléatoire"
  FILE *fichier;
  char mot[100];
  int nombre_de_mots = 0;
  int indice_aleatoire = 0;
  int mot_courant = 0;
  char mot_a_faire_deviner[50];

  srand ((unsigned int) time(NULL));

  fichier = fopen("words.txt", "r");
  while (fscanf(fichier, "%s", mot) == 1) { // nb de mots
  	nombre_de_mots = nombre_de_mots + 1;
  }

  indice_aleatoire = rand() % nombre_de_mots; //aléatoire
  fseek(fichier, 0, SEEK_SET); //réintinialiser à 0 pour une deuxième partie

  while (fscanf(fichier, "%s", mot) == 1) {
  	if (mot_courant == indice_aleatoire) {
      	strcpy(mot_a_faire_deviner, mot);
  	}  
  	mot_courant = mot_courant + 1;
  }

  fclose(fichier);

  //initialisation des variables
  size_t incrementation = 0;
  size_t incrementation2 = 0;
  int incrementation3 = 0;
  int incrementation4 = 0;
  int mauvaise_lettre = 0;
  char nom_du_joueur[30];
  int verif_tentative = 0;
  int tentative = 0;
  size_t gagner = 0;
  char lettre_deja_rentree[50] = "";
  int phrase = 0;
  int phrase2 = 0;
  int plusieur_fois_meme_lettre_dans_mot = 0;


  //nom du joueur demandé et stoké + verif qu'il n'existe pas déja
  if (compteur_de_win ==0){ //si la partie vient de démarrer
  	int verif_nom_joueur = 1;

  	while (verif_nom_joueur == 1) {
    	printf("Entrer votre nom de joueur : ");
    	scanf("%s", nom_du_joueur);

    	FILE *scoreFile = fopen("score.txt", "r");
    	char line[100];
    	int nom_trouve = 0;

    	while (fgets(line, sizeof(line), scoreFile) != 0) {
      	if (strstr(line, nom_du_joueur) != 0) {
        	printf("Le nom du joueur existe déjà. Réessayez avec un nom différent.\n");
        	nom_trouve = 1;
        	break;
      	}
    	}

    	fclose(scoreFile);

    	if (nom_trouve == 0) {
      	verif_nom_joueur = 0; // si il n'ya pas de même nom on continue
    	}
  	}

	printf("Votre nom est: %s\n", nom_du_joueur);
  }
  //taille du mot a faire deviner
  char mot_cache[50] = "";
  size_t taille = strlen(mot_a_faire_deviner);

  //affichage des _
  while (incrementation < taille) {
	mot_cache[incrementation] = '_';
	incrementation = incrementation + 1;
  }
  printf("Voici la taille du mot à faire deviner %s\n" , mot_cache);

  while ((tentative < 8) && (gagner != taille)){

	//remise à 0 des variables à chaque début de boucle
	incrementation2 = 0;
	mauvaise_lettre = 0;
	verif_tentative = 0;
	incrementation4 = 0;
	phrase = 0;
	plusieur_fois_meme_lettre_dans_mot = 0;
	char lettre = 'a';
	printf("\nentrer une lettre ");
	scanf(" %c" , &lettre); //demander une lettre a l'utilisateur

	if (lettre >= 'A' && lettre <= 'Z') { //convertir maj en minuscule
  	lettre = lettre + ('a' - 'A');
	}

	if ((lettre >= 'a' && lettre <= 'z') || (lettre >= 'A' && lettre <= 'Z')) { //si la lettre est bien une lettre minuscule ou majuscule
  	while (incrementation2 < taille) {
    	if (lettre == mot_a_faire_deviner[incrementation2]) { // si la lettre est dans le mot
      	mot_cache[incrementation2] = lettre;
        	incrementation2 = incrementation2 + 1;
        	gagner = gagner + 1;
        	mauvaise_lettre = 1;
        	verif_tentative = 1;
        	plusieur_fois_meme_lettre_dans_mot = plusieur_fois_meme_lettre_dans_mot + 1;
      	}
      	else { //si la lettre n'est pas dans le mot
        	incrementation2 = incrementation2 + 1;
      	}
    	}
  	}

  	//si l'utilisateur n'a pas mit de lettre min ou maj
  	else {
    	verif_tentative = 1; //ne pas compter une tentative si c'est un chiffre
    	printf("vous n'avez pas mit une lettre\n");
  	}

  	//si la lettre n'est pas dans le mot rajouter +1 a tentative
  	if (verif_tentative == 0){
    	tentative = tentative + 1;
  	}

  	incrementation3 = incrementation3 + 1;
  	lettre_deja_rentree[incrementation3] = lettre;
  	while (incrementation4 < incrementation3) {
    	if (lettre == lettre_deja_rentree[incrementation4]) {
      	lettre_deja_rentree[incrementation4] = '\0';
      	printf("vous avez deja rentré cette lettre\n");
      	if (mauvaise_lettre == 1){ //dans le cas ou la lettre est bonne et a été utilisé 2 fois ou plus
        	if (plusieur_fois_meme_lettre_dans_mot == 1){
        	gagner = gagner - 1;
        	}
        	else if (plusieur_fois_meme_lettre_dans_mot == 2){
          	gagner = gagner - 2;
        	} // toute ces boucle sont la si une lettre rentre bonne est reutilisé alors que la lettre est x fois dans le mot
        	else if (plusieur_fois_meme_lettre_dans_mot == 3){
          	gagner = gagner - 3;
        	}
        	else if (plusieur_fois_meme_lettre_dans_mot == 4){
          	gagner = gagner - 4;
        	}
        	else if (plusieur_fois_meme_lettre_dans_mot == 5){
          	gagner = gagner - 5;
        	}
        	else if (plusieur_fois_meme_lettre_dans_mot == 6){
          	gagner = gagner - 6;
        	}
        	else if (plusieur_fois_meme_lettre_dans_mot == 7){
          	gagner = gagner - 7;
        	}
      	}
      	else{ //dans le cas ou la lettre n'est pas bonne et a été utilisé 2 fois ou plus
        	if ((lettre >= 'a' && lettre <= 'z') || (lettre >= 'A' && lettre <= 'Z')) {//dans le cas ou ce n'est pas une lettre et qui a été utiliser 2 fois ou plus
          	tentative = tentative - 1;
        	}
      	}
    	}
  	incrementation4 = incrementation4 + 1;
  	}

	//printf("nb de tentative %d \n" , tentative); //pour regarder les résultats
	//printf("gagner %d \n" , gagner);

	phrase = phrase2; // affichage du nb d'essais restant si l'utilisateur vient de se tromper
	phrase2 = tentative;
	if (phrase != tentative){
  	if (tentative == 1){
    	printf("  __\n |  |______\n |     	|\n |_________|\n ");} //dessin du pendu en fonction du nb d'éssais
    	else if (tentative == 2){
      	printf("   |\n   |\n   |\n   |\n   |\n  _|_\n |   |______\n |      	|\n |__________|\n ");}
    	else if (tentative == 3){
      	printf("	____\n   |\n   |\n   |\n   |\n   |\n  _|_\n |   |______\n |      	|\n |__________|\n ");}
    	else if (tentative == 4){
      	printf("	____\n   |	|\n   |\n   |\n   |\n   |\n  _|_\n |   |______\n |      	|\n |__________|\n ");}
    	else if (tentative == 5){
      	printf("	____\n   |	|\n   |	O\n   |\n   |\n   |\n  _|_\n |   |______\n |      	|\n |__________|\n ");}
    	else if (tentative == 6){
      	printf("	____\n   |	|\n   |	O\n   |   / \\ \n   |\n   |\n  _|_\n |   |______\n |      	|\n |__________|\n ");}
    	else if (tentative == 7){
      	printf("	____\n   |	|\n   |	O\n   |   /|\\ \n   |	|\n   |\n  _|_\n |   |______\n |      	|\n |__________|\n ");}
    	else if (tentative == 8){
      	printf("	____\n   |	|\n   |	O\n   |   /|\\ \n   |	|\n   |   / \\ \n  _|_\n |   |______\n |      	|\n |__________|\n ");}
  	if (tentative != 8){
    	printf("\nVous vous êtes trompé, vous êtes à %d erreurs, attention vous n'avez que 8 tentatives\n" , tentative );}
	}

	if (gagner != taille){ // si l'utilisateur n'a pas gagné
  	if (tentative != 8){
    	printf("voici la progression du mot: %s\n" , mot_cache); //affichage du mot caché avec les lettres trouvées sauf si perdu
  	}
	}
	} //sortie de la grosse boucle while

	if (tentative == 8) { //cas où l'utilisateur a perdu
  	printf("__  	__                  	\n \\ \\	/ /                  	\n  \\ \\  / /	___	_   _   ___ \n   \\ \\/ /	/ _ \\  | | | | / __|\n	\\  /	| (_) | | |_| | \\__ \\\n 	\\/  	\\___/   \\__,_| |___/\n  __ _  __   __   ___   ____\n / _` | \\ \\ / /  / _ \\ |_  /\n| (_| |  \\ V /  |  __/  / / \n \\__,_|   \\_/	\\___| /___|\n                    	_    	\n                   	| |   	\n _ __	___  _ __   __| | _   _ \n| '_ \\  / _ \\| '__| / _` || | | |\n| |_) ||  __/| |   | (_| || |_| |\n| .__/  \\___||_|	\\__,_| \\__,_|\n| |                          	\n|_|                          	\n\nLe mot que vous deviez trouver est: %s" , mot_a_faire_deviner);
  	recommencer_gagner = 0;
  	printf("\nvous étiez à %d victoires d'affilées" , compteur_de_win
    	);
      	FILE *fichier = fopen("score.txt", "a");

      	fprintf(fichier, "\n%s = %d victoires d'affilées" , nom_du_joueur , compteur_de_win);
      	fclose(fichier);

	} //affichage du message de fin de partie et sauvergarde des scores

  	else{ //cas où l'utilisateur a gagner
 	printf("\n \n __  	__                  	\n \\ \\	/ /                  	\n  \\ \\  / /	___	_   _   ___ \n   \\ \\/ /	/ _ \\  | | | | / __|\n	\\  /	| (_) | | |_| | \\__ \\\n 	\\/  	\\___/   \\__,_| |___/\n\n  __ ___   _____ ____     	\n / _` \\ \\ / / _ \\_  /     	\n| (_| |\\ V /  __// /   	__ \n \\__,_| \\_/ \\___/___| 	/_/ \n\n  __ _  __ _  __ _ _ __   ___ \n / _` |/ _` |/ _` | '_ \\ / _ \\\n| (_| | (_| | (_| | | | |  __/\n \\__, |\\__,_|\\__, |_| |_|\\___|\n  __/ |   	__/ |       	\n |___/   	|___/        	\n\n le mot est: %s" , mot_a_faire_deviner);
    	compteur_de_win = compteur_de_win + 1;
    	printf("\n vous en êtes à %d victoires d'affilées\n" , compteur_de_win
	);

  }
  }
  return 0;
}

