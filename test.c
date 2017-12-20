#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<conio.h>
#include<string.h>

#include "utility_matrix.h"
#include "matrix_normalization.h"
#include "pearsons.h"
#include "kmeans.h"
#include "predictions.h"

#define No_of_movies 9125
#define No_of_test_users 124

/*int findusers(){
    char *line, *record;
    char tmp[1024];
    FILE *fstream = fopen("C:\\Users\\Shubham\\Desktop\\Recommendation Sytem\\Machine Learning\\Dataset\\ratings_learn.csv","r");
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
			record = strtok(NULL,",");
		}
		j=0;
    }
    fclose(fstream);
    free(line);
    free(record);
    return max;
}

void main(){
	int i=0;
	int No_of_learn_users = findusers();

	double *test_utility_matrix = (double *)malloc(sizeof(double) * No_of_test_users * No_of_movies);
	double *utility_matrix = (double *)malloc(sizeof(double) * No_of_learn_users * No_of_movies);

	get_utility_matrix(utility_matrix,"C:\\Users\\Shubham\\Desktop\\Recommendation Sytem\\Machine Learning\\Dataset\\ratings_learn.csv",No_of_movies,No_of_learn_users,0);
	get_utility_matrix(test_utility_matrix,"C:\\Users\\Shubham\\Desktop\\Recommendation Sytem\\Machine Learning\\Dataset\\ratings_test.csv",No_of_movies,No_of_learn_users,0);

	double *test_normalized_matrix = (double *)malloc(sizeof(double) * No_of_test_users * No_of_movies);
	double *normalized_matrix = (double *)malloc(sizeof(double) * No_of_learn_users * No_of_movies);

	normalize_matrix(test_utility_matrix,test_normalized_matrix,No_of_test_users,No_of_movies);
	normalize_matrix(utility_matrix,normalized_matrix,No_of_learn_users,No_of_movies);

	double sq_sum = 0;
	int count = 0;
	double rmse;

	for(i=0;i<No_of_test_users;i++){
		printf("User: %d\n",i);

		int k=16;
		int j=0;

		double *similarity = malloc(sizeof(double) * No_of_learn_users);
		calc_similarity(&test_normalized_matrix[i*No_of_movies],normalized_matrix,similarity,No_of_learn_users,No_of_movies);

		double *centroids = (double *)malloc(sizeof(double) * k);
		int *cluster_assignment = (int *)malloc(sizeof(int) * No_of_learn_users);

		for(j=0;j<k;j++){
			int n = rand()%No_of_learn_users;
			int m=0, flag=0;
			for(m=0;m<j;m++){
				if(similarity[n] == centroids[m]){
					flag=1;
					break;
				}
			}
			if(flag==1){
				j--;
				continue;
			}
			centroids[j] = similarity[n];
		}

		kmeans(1,similarity,No_of_learn_users,k,centroids,cluster_assignment);

		int *similar_users = malloc(sizeof(int) * No_of_learn_users);
		int no_of_susers=0;

		double max = 0;
		int maxid = 0;
		for(j=0;j<k;j++){
			if(centroids[j]>max){
				max = centroids[j];
				maxid = j;
			}
		}

		for(j=0;j<No_of_learn_users;j++){
			if(cluster_assignment[j] == maxid){
				similar_users[no_of_susers] = j;
				no_of_susers++;
			}
		}

		double *predicted_ratings = malloc(sizeof(double) * No_of_movies);

		test_predictions(&test_utility_matrix[i*No_of_movies], similar_users, no_of_susers, similarity, utility_matrix, predicted_ratings, No_of_movies);

		for(j=0;j<No_of_movies;j++){
			if(predicted_ratings[j]!=0){
				printf("Rating for movie %d: %f\n",j+1,predicted_ratings[j]);
				count++;
				sq_sum += (predicted_ratings[j] - test_utility_matrix[i*No_of_movies + j])*(predicted_ratings[j] - test_utility_matrix[i*No_of_movies + j]);
			}
		}
		free(similarity);
		free(centroids);
		free(cluster_assignment);
		free(similar_users);
		free(predicted_ratings);
	}

	rmse = sqrt(sq_sum/count);

	printf("Root mean square error of this recommender system is: %f",rmse);

	getch();

	free(utility_matrix);
	free(test_utility_matrix);
	free(normalized_matrix);
	free(test_normalized_matrix);
}*/
