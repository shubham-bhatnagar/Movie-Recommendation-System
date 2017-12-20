#include<stdio.h>
#include<stdlib.h>
#include<string.h>

double calc_average(double *utility_matrix,int No_of_movies){ //inputs: utility matrix and user id
	double average, sum=0;
	int i=0, count=0;
	
	//traverse through each rating
	for(i=0;i<No_of_movies;i++){
		if(utility_matrix[i]!=0){ // if rated
			count++; //increase count
			sum += utility_matrix[i]; //add to total sum
		}
	}
	return average = sum/count;
}

void normalize_matrix(double *utility_matrix, double *normalized_matrix, int No_of_users, int No_of_movies){ //inputs: utility matrix and new matrix to save normalized ratings
	int i=0,j=0;
	for(i=0;i<No_of_users;i++){
		//calculate average for i^th user
		double average = calc_average(&utility_matrix[i*No_of_movies],No_of_movies);
		
		//traverse through each movie rating
		for(j=0;j<No_of_movies;j++){
			if(utility_matrix[i*No_of_movies + j] == 0){
				normalized_matrix[i*No_of_movies + j] = 0;
			}else{
				normalized_matrix[i*No_of_movies + j] = utility_matrix[i*No_of_movies + j] - average; //subtract average rating from current rating
			}
		}
	}
}

void normalize(double *user, double *normalizeduser, int No_of_movies){ //inputs: rating vector of new user and new vector to save normalized ratings
	int i=0, count = 0;
	double sum=0, average=0;
	
	//calculating average based on which movies have been rated
	for(i=0;i<No_of_movies;i++){
		if(user[i]!=0){
			sum += user[i];
			count++;
		}
	}
	average = sum/count;
	
	//normalizing the vector
	for(i=0;i<No_of_movies;i++){
		if(user[i]==0){
			normalizeduser[i] = 0; //rating becomes zero if not rated
		}else{
			normalizeduser[i] = user[i] - average; //subtract average rating from current rating
		}
	}
}