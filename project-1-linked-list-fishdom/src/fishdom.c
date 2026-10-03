#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct  fish_info_node{

    float weight;
    float v_length;
    float d_length;
    float c_length;
    float h_length;
    float f_length;
    char date[100];
    char city[100];
    struct fish_info_node *next;
};
struct fish_species_node{
    char species[100];
    struct fish_info_node *right;
    struct fish_species_node *down;
};
void saveUpdatedList(struct fish_species_node *);
void AddSpeciesList(struct fish_species_node*);
void addFishData(struct fish_species_node *);
void display(struct fish_species_node*);
void printStatistic (struct fish_species_node*);
void deleteFish (struct fish_species_node*, float deleteWeight);
void searchFishData(struct fish_species_node*);
struct fish_species_node* initializeFishing(char *file) {
    FILE *infle;
    struct fish_species_node *head = NULL;
    struct fish_species_node *tail = NULL;
    infle = fopen("fishingArchive.txt", "r");
    if (infle == NULL) {
        printf("Error opening the file.\n");

    }
    else {
        printf("File is open\n");
        rewind(infle);
    }
    char species[100], date[100], city[100];
    float weight, v_length, d_length, c_length, h_length, f_length;

    while (fscanf(infle, "%99[^;];%f;%f;%f;%f;%f;%f;%99[^;];%99s\n",species, &weight, &v_length, &d_length, &c_length, &h_length, &f_length, date, city)!=EOF){
        struct fish_species_node *tmp = (struct fish_species_node*) malloc(sizeof (struct fish_species_node));
        if (tmp==NULL){
            perror("Memory allocation failed.\n");
        }
        int samespecies = 0;
        struct  fish_species_node *same = head;
        while (same!=NULL){
            struct fish_info_node *nexttemp= (struct fish_info_node*) malloc(sizeof (struct fish_info_node));
            if (nexttemp == NULL) {
                perror("Memory allocation failed.\n");
            }
            struct fish_info_node *samenext= same->right;

            if (strcmp(same->species,species)==0){
                samespecies = 1;
                while (samenext->next!=NULL){
                    samenext = samenext->next;
                }
                nexttemp->weight = weight;
                nexttemp->v_length = v_length;
                nexttemp->d_length = d_length;
                nexttemp->c_length = c_length;
                nexttemp->h_length = h_length;
                nexttemp->f_length = f_length;
                strcpy(nexttemp->date, date);
                strcpy(nexttemp->city, city);
                nexttemp->next=NULL;
                samenext->next = nexttemp;


            }
            same = same->down;
        }
        if(samespecies==0){
            strcpy(tmp->species ,species);
            tmp->right = (struct fish_info_node*) malloc(sizeof (struct fish_info_node));
            tmp->right->weight = weight;
            tmp->right->v_length = v_length;
            tmp->right->d_length = d_length;
            tmp->right->c_length = c_length;
            tmp->right->h_length = h_length;
            tmp->right->f_length = f_length;
            strcpy(tmp->right->date, date);
            strcpy(tmp->right->city, city);
            tmp->right->next = NULL;
            if (head==NULL){
                head = tmp;
                tail = tmp;
                tail->down=NULL;
            }
            else{
                tail->down = tmp;
                tail = tmp;
                tail->down=NULL;
                }

        }

    }
    fclose(infle);
    return head;
}

int main() {
    int exit = 0;
    int choose;
    char filename[100];


    struct fish_species_node *fishlist = initializeFishing("fishingArchive.txt" );
    display( fishlist);


    if (fishlist == NULL) {
        perror("Memory allocation failed");
    }


    while (exit != 1) {
        printf("\n-----MENU--------------------------------------\n1. Add Fish Data \n2. Delete Fish Data \n3. Print Fish Statistics \n4. Search Fish Data \n5. Add Species List \n6. Exit\n");
        scanf("%d", &choose);
        printf("Enter your option: %d", choose);

        if (choose == 1) {
            addFishData(fishlist);
            display( fishlist);
        }
        else if (choose == 2){
            float deleteWeight;
            printf("\nProvide fish weight threshold in grams: \n");
            scanf("%f", &deleteWeight);
            deleteFish(fishlist,deleteWeight);
            display( fishlist);
        }
        else if(choose==3){
            printStatistic(fishlist);
        }
        else if(choose==4){
            searchFishData(fishlist);
        }
        else if (choose == 5){
            AddSpeciesList(fishlist);
            display( fishlist);
        }
        else if (choose == 6) {
            printf("byee!!!");
            saveUpdatedList(fishlist);
            exit = 1;
            break;
        }
    }

    free(fishlist);

    return 0;
}


void addFishData(struct fish_species_node *l) {
    int control = 0;
    char name[100];
    struct fish_species_node *head = l;
    struct fish_species_node *tail = l;
    struct fish_info_node *newfishinfo = (struct fish_info_node *)malloc(sizeof(struct fish_info_node));

    if (newfishinfo == NULL) {
        perror("Memory allocation failed");
        return;
    }

    printf("\n");
    printf("Species: ");
    scanf("%s", name);

    while (tail != NULL) {
        if (strcmp(name, tail->species) == 0) {
            control = 1;
            break;
        }
        tail = tail->down;
    }

    if (control == 1) {
        printf("Weight of the fish in grams: ");
        scanf("%f", &newfishinfo->weight);

        printf("Vertical length in CM: ");
        scanf("%f", &newfishinfo->v_length);

        printf("Diagonal length in CM: ");
        scanf("%f", &newfishinfo->d_length);

        printf("Cross length in CM: ");
        scanf("%f", &newfishinfo->c_length);

        printf("Height in CM: ");
        scanf("%f", &newfishinfo->h_length);

        printf("Fish Length in CM: ");
        scanf("%f", &newfishinfo->f_length);

        printf("Fishing date (day/month/year): ");
        scanf("%s", newfishinfo->date);

        printf("City: ");
        scanf("%s", newfishinfo->city);

        fflush(stdin);

        // Find the last node of fish info for this species
        struct fish_info_node *current = tail->right;
        if (current == NULL) {
            tail->right = newfishinfo;
        } else {
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newfishinfo;
        }
        newfishinfo->next = NULL;
    } else {
        printf("\n Species doesn't exist.\n");
        free(newfishinfo);
    }
}

void AddSpeciesList(struct fish_species_node *l){

    struct fish_species_node *tmp = (struct fish_species_node *)malloc(sizeof(struct fish_species_node));
    struct fish_species_node *head = l;
    struct fish_species_node *tail = l;
    printf("\n");
    if (tmp == NULL) {
        perror("Memory allocation failed");
        return;
    }
    tmp->right = (struct fish_info_node *)malloc(sizeof(struct fish_info_node));
    if (tmp->right == NULL) {
        perror("Memory allocation failed");
        return;
    }

    printf("Species: ");
    scanf("%s", tmp->species);
    printf("Weight of the fish in grams: ");
    scanf("%f", &tmp->right->weight);

    printf("Vertical length in CM: ");
    scanf("%f", &tmp->right->v_length);

    printf("Diagonal length in CM: ");
    scanf("%f", &tmp->right->d_length);

    printf("Cross length in CM: ");
    scanf("%f", &tmp->right->c_length);

    printf("Height in CM: ");
    scanf("%f", &tmp->right->h_length);

    printf("Fish Length in CM: ");
    scanf("%f", &tmp->right->f_length);

    printf("Fishing date (day/month/year): ");
    scanf("%s", tmp->right->date);

    printf("City: ");
    scanf("%s", tmp->right->city);
    tmp->down;
    while (tail->down!=NULL){
        tail = tail->down;
    }
    tail->down= tmp;
    tail = tmp;
    tail->down = NULL;
    tail->right->next =NULL;


}
void printStatistic (struct fish_species_node*l){
    struct fish_species_node *statistic = l;
    int count=0;
    int control=0;
    char species[50];
    printf("\n Provide the species: \n");
    scanf("%s",species);
    while (statistic!=NULL){
        if(strcmp(species,statistic->species)==0){
            control = 1;
            break;
        }
        statistic = statistic->down;
    }
    if(control==1){
        while (statistic->right!=NULL){
            count++;
            statistic->right  = statistic->right->next;
        }
        printf("The number of available fish data is %d\n", count);
    }
    else{
        perror("species doesn't find\n");
    }



}
void deleteFish(struct fish_species_node *l,float deleteWeight) {
    int count = 0;
    struct fish_species_node *remove = l;

    while (remove != NULL) {
        struct fish_info_node *iter = remove->right;
        struct fish_info_node *tmp = remove->right;

        while (iter != NULL) {
            if (iter->weight == deleteWeight) {
                if (tmp == remove->right) {
                    // Deleting the first node
                    remove->right = iter->next;
                } else {
                    tmp->next = iter->next;
                }

                free(tmp);
                ++count;
                break; // Exit loop after deletion
            }
            tmp = iter;
            iter = iter->next;
        }
        remove = remove->down;
    }

    printf("%d fish data were deleted from your list!\n", count);
}
void searchFishData(struct fish_species_node*l){
    char choose[100];
    printf("Enter your search option (C for city/M for month):");
    scanf("%s", choose);
    if (strcmp(choose, "C") == 0) {
        char c[100];
        printf("\nEnter the City");
        scanf("%s",c);
        printf("\n");
        struct fish_species_node *tmp =l;
        while (tmp!=NULL){
            struct fish_info_node *tmpnext = tmp->right;
            while (tmpnext!=NULL){
                if(strcmp(tmpnext->city,c)==0){
                    printf("%s;%f;%f;%f;%f;%f;%f;%s;%s", tmp->species, tmpnext->weight,tmpnext->v_length,tmpnext->d_length,tmpnext->c_length,tmpnext->h_length,tmpnext->f_length,tmpnext->date,tmpnext->city);
                    printf("\n");
                }
                tmpnext=tmpnext->next;
            }
            tmp =tmp->down;
        }


    }
    if (strcmp(choose, "M") == 0){
        int m;
        struct fish_species_node *tmp =l;
        char *token;

        printf("\nEnter the month number:");
        scanf("%d",&m);
        printf("\n");

        while (tmp!=NULL){
            int day,month,year;
            struct fish_info_node *tmpnext = tmp->right;
            while (tmpnext!=NULL){
                //Get the first token day
                token = strtok(tmpnext->date, "/");
                day = atoi(token);
                //Get the second token for month
                token = strtok(NULL, "/");
                month = atoi(token);
                //Get the third token for year
                token = strtok(NULL, "/");
                year = atoi(token);

                if(month==m){
                    printf("%s;%f;%f;%f;%f;%f;%f;%s;%s", tmp->species, tmpnext->weight,tmpnext->v_length,tmpnext->d_length,tmpnext->c_length,tmpnext->h_length,tmpnext->f_length,tmpnext->date,tmpnext->city);
                    printf("\n");
                }
                tmpnext=tmpnext->next;
            }
            tmp =tmp->down;
        }
    }
}
void saveUpdatedList(struct fish_species_node *l) {
    FILE *outfile ;
	fopen("fishingArchive.txt", "w");
    if (outfile == NULL) {
        perror("Error file");
        return;
    }

    struct fish_species_node *fishSpecies = l;

    while (fishSpecies != NULL) {
        struct fish_info_node *tailtFish = fishSpecies->right;

        while (tailtFish != NULL) {
            fprintf(outfile, "%s;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%s;%s\n",fishSpecies->species, tailtFish->weight, tailtFish->v_length,tailtFish->d_length, tailtFish->c_length, tailtFish->h_length,tailtFish->f_length, tailtFish->date, tailtFish->city);

            tailtFish = tailtFish->next;
        }

        fishSpecies = fishSpecies->down;
    }

    fclose(outfile);
    printf("Data has been successfully saved to fishingArchive.txt");
}