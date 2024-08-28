#include <stdio.h>
#include "decimal.h"
#include <string.h>
#include <stdlib.h>


void inscription(FILE* file)
{
    char login[100] , password[100];
    printf("Entrez l'utilisateur : ");
    scanf("%s", login);
    printf("Entrez le mot de passe : ");
    scanf("%s",password);
    fprintf(file,"%s;%s\n",login,password);
    fclose(file);
    printf("Inscription reussi\n");

}
void connection(FILE* file)
{
    char login[100] , password[100];
    printf("L'utilisateur : ");
    scanf("%s",login);
    printf("mot de passe : ");
    scanf("%s",password);
    search(file,login,password);

}
void search(FILE* file ,const char* login ,const char* password)
{
    char line[100];
    int octet1,octet2,octet3,octet4;
    char Utilisateur[100];
    char Mot_de_passe[100];
    int restart;
    rewind(file);
    while(fgets(line,sizeof(line,file),file)!=NULL)
    {
        line[strcspn(line,"\n")]=0;
        char* pointvirgule=strtok(line,";");
        if(pointvirgule!=NULL)
        {
           strncpy(Utilisateur,pointvirgule,sizeof(Utilisateur));
            pointvirgule=strtok(NULL,";");
            if(pointvirgule!=NULL)
            {
               strncpy(Mot_de_passe,pointvirgule,sizeof(Mot_de_passe));
                if(strcmp(login,Utilisateur)==0 && strcmp(password,Mot_de_passe)==0)
                {
                    printf("connection Reussi \n");
                    demandeIP(&octet1,&octet2,&octet3,&octet4);
                    classIP(octet1,octet2,octet3,octet4);
                    return ;
                    fclose(file);
                }
            }
        }
    }
    if( strcmp(login,Utilisateur)!=0 && strcmp(password,Mot_de_passe)!=0)
    {
        printf("Recommencer ou Quitter ? (1/0)");
        scanf("%d",&restart);
        if(restart==1)
        {
            rewind(file);
            connection(file);
            //deconnect();
        }
        else
        {
            fclose(file);
        }
    }
    
}
void choice ()
{
    int octet1,octet2,octet3,octet4;
    FILE* file=fopen("liste.txt","a+");
    if(file==NULL)
    {
        printf("Erreur d'ouverture \n");
    }
    int numero ;
    printf("__________________\n");
    printf("|                 |\n");
    printf("|Open their choice|\n");
    printf("___________________\n");
    printf("1-Connection\n");
    printf("2-New Compte\n");
    scanf("%d",&numero);
    switch (numero)
    {
        case 1:
            connection(file);
            break;
        case 2:
            inscription(file);
            demandeIP(&octet1,&octet2,&octet3,&octet4);
            classIP(octet1,octet2,octet3,octet4);
            break;
        default:
            printf("choix invalide\n");
            fclose(file);
            break;
    }
    
}
void demandeIP(int* octet1, int* octet2, int* octet3, int* octet4)
{
    while (1) 
    {
        printf("Entrez une adresse IP  : ");
        if (scanf("%d.%d.%d.%d", octet1, octet2, octet3, octet4) != 4) 
        {
            printf("Format invalide. Veuillez réessayer.\n");
            while (getchar() != '\n'); // Nettoyage du tampon d'entrée
            continue;
        }
        if (*octet1 >= 0 && *octet1 <= 255 &&
            *octet2 >= 0 && *octet2 <= 255 &&
            *octet3 >= 0 && *octet3 <= 255 &&
            *octet4 >= 0 && *octet4 <= 255) 
        {
            printf("Adresse IP valide.\n");
            break; 
        } 
        else 
        {
            printf("Adresse IP invalide.\n");
        }
    }
}

void classIP(int octet1, int octet2, int octet3, int octet4)
{
    char class;

    if (octet1 >= 0 && octet1 <= 127) 
    {
        class = 'A';
    }
    else if (octet1 >= 128 && octet1 <= 191) 
    {
        class = 'B';
    }
    else if (octet1 >= 192 && octet1 <= 223) 
    {
        class = 'C';
    }
    else if (octet1 >= 224 && octet1 <= 239) 
    {
        class = 'D';
    }
    else if (octet1 >= 240 && octet1 <= 255) 
    {
        class = 'E';
    }
    else 
    {
        printf("Pas d'adresse IP valide.\n");
        return;
    }

    switch (class)
    {
    case 'A':
        printf("L'IP est de classe A.\n");
        break;
    case 'B':
        printf("L'IP est de classe B.\n");
        break;
    case 'C':
        printf("L'IP est de classe C.\n");
        break;
    case 'D':
        printf("L'IP est de classe D.\n");
        break;
    case 'E':
        printf("L'IP est de classe E.\n");
        break;
    default:
        break;
    }
    deconnect();
}
void deconnect()
{
    char close[10];
    FILE* file=fopen("liste.txt","r");
    if(file==NULL)
    {
        printf("Erreur d'ouverture du fichier\n");
        return ;
    }
    printf("vous voulez deconnecter (oui/non) ? : ");
    scanf("%s",close);
    if(strcmp(close,"oui")==0)
    {
        fclose(file);
        exit(0);
    }
    else if(strcmp(close,"non")==0)
    {
        connection(file);
    }
    else
    {
        fclose(file);
        exit(1);
    }
       
}