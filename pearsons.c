//Centered cosine similarity
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

double pearson_correlation(double *A, double *B, unsigned int size){
    double dot_p=0.0;
    double mag_a=0.0;
    double mag_b=0.0;
    int i;
    for(i=0; i<size; i++){
        dot_p += A[i]*B[i];
        mag_a += A[i]*A[i];
        mag_b += B[i]*B[i];
    }
    return dot_p/(sqrt(mag_a)*sqrt(mag_b));
}

void calc_similarity(double *normalizeduser, double *normalized_matrix, double *similarity, int No_of_users, int No_of_movies){
	int i=0,j=0;
	for(i=0;i<No_of_users;i++){ //traverse through each user
		double *A;
		A = (double *)malloc(sizeof(double) * No_of_movies);
		
		//get rating vector for that user
		for(j=0; j<No_of_movies; j++){
			A[j] = normalized_matrix[i*No_of_movies + j];
		}
		
		//find similarity between new user and ith user
		similarity[i] = pearson_correlation(normalizeduser,A,No_of_movies);
		free(A);
	}
}
