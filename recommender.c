//Contains all logic and function calls
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<string.h>

#include "utility_matrix.h"
#include "matrix_normalization.h"
#include "pearsons.h"
#include "kmeans.h"
#include "predictions.h"
#include "sorting.h"

#define No_of_movies 9125

int findusers(){
    char *line, *record;
    char tmp[1024];
    FILE *fstream = fopen("\\Dataset\\ratings_learn.csv","r");
    int j=0;
    int max = 0;
    while((line=fgets(tmp,sizeof(tmp),fstream))!=NULL){
    record = strtok(line,",");
    while(record!=NULL){
        if(j==0){
            int t = atoi(record);
        if(t > max) max = t;
        }
        j++;
        record = strtok(NULL,","); //iterate
    }
    j=0;
    }
    fclose(fstream);
    free(line);
    free(record);
    return max;
}

void recommender(int uid){
    int No_of_users = findusers();
	int i=0,l=0;
	int choice;
	double time_taken;
	int userid = uid;
    clock_t t;
    t = clock();
	int k=16; //number of clusters
	//printf("Choose k: "); scanf("%d",&k); //taking input to test various values for k and deciding which is optimal
	double *utility_matrix = (double *)malloc(sizeof(double) * No_of_users * No_of_movies);
	char *movienames = (char *)malloc(sizeof(char) * No_of_movies * 1024);
	char *moviegenres = (char *)malloc(sizeof(char) * No_of_movies * 1024);

	get_utility_matrix(utility_matrix,"\\Dataset\\ratings_learn.csv",No_of_movies, No_of_users, userid); //getting utility matrix which will contain ratings according to user id(row) and movie id(coloumn)
	get_movie_names(movienames,"\\Dataset\\movies.csv"); //getting movie names according to movie id(index)
	get_movie_genres(moviegenres,"\\Dataset\\movies_genres.csv"); //getting movie genres according to movie id(index)

	double *normalized_matrix = (double *)malloc(sizeof(double) * No_of_users * No_of_movies);
	normalize_matrix(utility_matrix,normalized_matrix,No_of_users,No_of_movies); //normalizing the utility matrix for similarity calculations

	double *newuser = (double *)malloc(sizeof(double) * No_of_movies); //take ratings from user
	new_user_movies(newuser,"\\Dataset\\ratings_learn.csv", userid);
	//newuser[0] = 4.0; newuser[1] = 4.0; newuser[18] = 3.5; newuser[45] = 4.5; newuser[203] = 4.0; newuser[284] = 5.0; newuser[309] = 4.5; newuser[321] = 5.0; newuser[326] = 4.0; newuser[328] = 4.0; newuser[331] = 4.0; newuser[525] = 4.5; newuser[644] = 3.0; newuser[648] = 3.5; newuser[772] = 4.0; newuser[951] = 4.0; newuser[960] = 4.5; newuser[1012] = 4.0; newuser[1019] = 4.0; newuser[1091] = 4.0; newuser[1199] = 4.0; newuser[1234] = 3.5; newuser[1253] = 4.5; newuser[1336] = 4.0; newuser[1352] = 4.0; newuser[1353] = 3.0; newuser[1359] = 3.5; newuser[1401] = 4.5; newuser[1351] = 4.0; newuser[1352] = 3.5; newuser[1353] = 3.5; newuser[1354] = 3.0; newuser[1355] = 3.0; newuser[1553] = 4.0; newuser[1554] = 4.0; newuser[1555] = 3.5; newuser[1559] = 4.0; newuser[1573] = 4.0; newuser[1574] = 4.0; newuser[1795] = 2.5; newuser[2212] = 5.0; newuser[2506] = 3.5; newuser[3001] = 4.5; newuser[3025] = 4.5; newuser[3812] = 4.0; newuser[4147] = 4.0; newuser[4234] = 4.0; newuser[4449] = 4.0; newuser[4608] = 4.0; newuser[4711] = 4.0; newuser[4865] = 3.5; newuser[5127] = 4.5; newuser[5338] = 4.0; newuser[5392] = 4.0; newuser[5393] = 4.0; newuser[5399] = 4.0; newuser[5442] = 4.0; newuser[5448] = 3.0; newuser[5491] = 3.5; newuser[5547] = 4.5; newuser[5584] = 4.0; newuser[6145] = 4.0; newuser[6207] = 4.5; newuser[6274] = 3.0; newuser[6294] = 3.5; newuser[6381] = 4.0; newuser[6415] = 3.5; newuser[6483] = 4.0; newuser[6572] = 4.0; newuser[6583] = 4.0; newuser[6622] = 3.5; newuser[6688] = 4.0; newuser[6691] = 4.0; newuser[6700] = 4.0; newuser[6735] = 3.0; newuser[6753] = 4.5; newuser[6798] = 3.5; newuser[6817] = 3.5; newuser[6841] = 4.0; newuser[6930] = 4.0; newuser[6933] = 4.5; newuser[6979] = 3.5; newuser[6999] = 4.0; newuser[7033] = 3.0; newuser[7072] = 4.0; newuser[7075] = 4.0; newuser[7190] = 4.0; newuser[7201] = 2.0; newuser[7207] = 4.0; newuser[7236] = 4.0; newuser[7263] = 4.0; newuser[7274] = 3.0; newuser[7325] = 3.5; newuser[7442] = 5.0; newuser[7533] = 4.0; newuser[7576] = 3.5; newuser[7582] = 4.0; newuser[7608] = 4.0; newuser[7745] = 4.0; newuser[7817] = 4.0; newuser[7827] = 3.5; newuser[7826] = 4.0; newuser[7835] = 3.5; newuser[7857] = 4.5; newuser[7861] = 3.5; newuser[7863] = 3.5; newuser[7888] = 3.5; newuser[7917] = 4.0; newuser[8001] = 3.5; newuser[8023] = 4.5; newuser[8050] = 4.5; newuser[8065] = 3.5; newuser[8070] = 4.0; newuser[8072] = 4.0; newuser[8085] = 4.0; newuser[8086] = 4.0;newuser[8087] = 4.0; newuser[8090] = 4.0; newuser[8095] = 3.5; newuser[8100] = 4.0; newuser[8101] = 4.0; newuser[8154] = 4.5; newuser[8320] = 4.0; newuser[8382] = 4.0; newuser[8383] = 3.0; newuser[8384] = 4.0; newuser[8405] = 3.5; newuser[8428] = 3.5; newuser[8432] = 3.5; newuser[8536] = 4.5; newuser[8606] = 4.5; newuser[8608] = 4.5; newuser[8633] = 4.0; newuser[8701] = 4.0; newuser[8726] = 3.0; newuser[8740] = 4.0; newuser[8763] = 4.0; newuser[9082] = 3.5;

    double *normalizednewuser = malloc(sizeof(double) * No_of_movies);
	normalize(newuser,normalizednewuser,No_of_movies); //normalizing the users ratings for similarity calculations

	double *similarity = malloc(sizeof(double) * No_of_users);
	calc_similarity(normalizednewuser,normalized_matrix,similarity,No_of_users,No_of_movies); //calculating similarity between new user and users present in dataset

    double *centroids = (double *)malloc(sizeof(double) * k);
	int *cluster_assignment = (int *)malloc(sizeof(int) * No_of_users); //which cluster does the user belong in

	// choose intial centroids at random from dataset(similarity) for clustering to find most similar users

	//printf("Initial centroids\n");
	for(i=0;i<k;i++){
		int n = rand()%No_of_users; //choosing random index
		int m=0, flag=0;
		for(m=0;m<i;m++){
			if(similarity[n] == centroids[m]){ //to check weather we have already chosen that centroid
				flag=1;
				break;
			}
		}
		if(flag==1){ //if already chosen then choose again
			i--;
			continue;
		}
		centroids[i] = similarity[n]; //setting the centroids according to random index generated
		//printf("%lf\n",centroids[i]);
	}
	kmeans(1,similarity,No_of_users,k,centroids,cluster_assignment); //clustering of similarity to find most similar users

	int *similar_users = malloc(sizeof(int) * No_of_users);
	int no_of_susers=0;

	double max = 0;
	int maxid = 0;
	for(i=0;i<k;i++){
		if(centroids[i]>max && centroids[i]<0.3){ //0.3 is chosen based on experimental results (hit and trial)
			max = centroids[i];
			maxid = i; //selecting cluster with max similarity to get most similar users
		}
	}

	//printf("Members of cluster %d(similar users)\n",maxid+1);
	for(i=0;i<No_of_users;i++){
		if(cluster_assignment[i] == maxid){ //if that user belongs to selected cluster with max similarity
			//printf("User %d with similarity %.3lf\n",i+1,similarity[i]);
			similar_users[no_of_susers] = i; //assigning the users from cluster to a new array of most similar users
			no_of_susers++;
		}
	}

	int *recommended_movies = malloc(sizeof(int) * No_of_movies); //array containing index of recommended movies(whose ratings were predicted)
	double *predicted_ratings = malloc(sizeof(double) * No_of_movies); //array of ratings of those recommended movies
	int no_of_recommended_movies = 0;

	no_of_recommended_movies = make_prediction(newuser, similar_users, no_of_susers, similarity, utility_matrix, recommended_movies, predicted_ratings,No_of_movies); //making predictions and saving them in recommended_movies and predicted_ratings arrays

	for(i=0;i<no_of_recommended_movies;i++){ //printing the recommended movies to get an idea (movies whose ratings was calculated)
		printf("Rating for movie %d: %.1lf\n",recommended_movies[i]+1,predicted_ratings[i]);
	}

	sort(recommended_movies,predicted_ratings,no_of_recommended_movies); //sorting the recommended movies in decreasing order according to their predicted ratings

	printf("Top 10 movies recommended for you: \n");

	for(i=0;i<1000;i++){ //selecting top 10 movies from the recommended movies
		if(i==no_of_recommended_movies)  // if number of recommended movies is less than 10 then we will have to end loop early
		{
		    printf("\nSorry these are the only movies that can be recommended based on input.\nPlease enter more input.\n\n");
		    break;
		}
		printf("%d. %s %s",i+1,&movienames[recommended_movies[i] * 1024], &moviegenres[recommended_movies[i] * 1024]);
		if(i>0 && (i+1)%10==0){
            printf("\nDo you want to see more movie recommendations? \nType '0' for No and '1' for Yes: ");
            if(1 != scanf("%d",&choice)){
                printf("\nCharacter inputs are not accepted.\n");
                break;
            }
            if (choice == 0)break;
            else if (choice == 1)
                printf("");
            else{
                printf("\nInvalid choice.\n\n");
                break;
            }
		}
	}
	t = clock() - t;
    time_taken = ((double) t)/CLOCKS_PER_SEC;
    printf("\nTime taken to process: %.2lf seconds\n",time_taken);

	//freeing the memory

	free(utility_matrix);
	free(movienames);
	free(moviegenres);
	free(normalized_matrix);
	free(newuser);
	free(normalizednewuser);
	free(similarity);
	free(centroids);
	free(cluster_assignment);
	free(similar_users);
	free(recommended_movies);
	free(predicted_ratings);

	//THE END
}
