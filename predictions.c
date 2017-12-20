#include<stdio.h>
#include<stdlib.h>

int make_prediction(double *user, int *similar_users, int no_of_susers, double *similarity, double *utility_matrix, int *recommended_movies, double *predicted_ratings, int No_of_movies){
	int i=0,k=0;
	int no_of_recommended_movies = 0;
	for(i=0;i<No_of_movies;i++){ //traverse through each movie
		double sum1=0, sum2=0;
		int count=0;
		if(user[i]==0){ //if not rated by the user
			for(k=0;k<no_of_susers;k++){ //traverse through similar users
				if(utility_matrix[similar_users[k]*No_of_movies + i]==0) continue; //all similar users who have also rated movie i
				sum1 += similarity[similar_users[k]]*utility_matrix[similar_users[k]*No_of_movies + i];
				sum2 += similarity[similar_users[k]];
				count++;
			}
			if(count>1){ //the movie is common between atleast two users otherwise if it only has one user then we will get that same rating
				recommended_movies[no_of_recommended_movies] = i; //add movie index to recommended movies
				predicted_ratings[no_of_recommended_movies] = sum1/sum2; //make prediction
				no_of_recommended_movies++;
			}
		}
	}
	return no_of_recommended_movies;
}

void test_predictions(double *user, int *similar_users, int no_of_susers, double *similarity, double *utility_matrix, double *predicted_ratings, int No_of_movies){
	int i=0, k=0;
	for(i=0;i<No_of_movies;i++){
		double sum1=0, sum2=0;
		int count=0;
		if(user[i] != 0){
			for(k=0;k<no_of_susers;k++){
				if(utility_matrix[similar_users[k]*No_of_movies + i]==0) continue;
				sum1 += similarity[similar_users[k]]*utility_matrix[similar_users[k]*No_of_movies + i];
				sum2 += similarity[similar_users[k]];
				count++;
			}
			if(count>1){
				predicted_ratings[i] = sum1/sum2;
			}else{
				predicted_ratings[i] = 0;
			}
		}else{
			predicted_ratings[i] = 0;
		}
	}
}