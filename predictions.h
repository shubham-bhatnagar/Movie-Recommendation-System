#ifndef PREDICTIONS_H
#define PREDICTIONS_H

int make_prediction(
					double *user, //new  user ratings defiend as double *user = (double *)malloc(sizeof(double) * No_of_movies); 
					
					int *similar_users, //ids of all similar users based on clustering
					
					int no_of_susers, //number of similar users
					
					double *similarity, //similarity with all the existing user
					
					double *utility_matrix, //utility matrix
					
					int *recommended_movies, //list of recommended movies to be saved in
					
					double *predicted_ratings, //predicted ratigs of those movies to be saved in
					
					int No_of_movies
					); //returns number of recommended movies
					
void test_predictions(
					  double *user, 
					  int *similar_users, 
					  int no_of_susers, 
					  double *similarity, 
					  double *utility_matrix, 
					  double *predicted_ratings,
					  int No_of_movies
					  );
					
#endif