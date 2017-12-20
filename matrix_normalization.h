//Header file for matrix_normalization.c
#ifndef MATRIX_NORMALIZATION_H
#define MATRIX_NORMALIZATION_H

void normalize_matrix(
					  double *utility_matrix, //defined as double *utility_matrix = (double *)malloc(sizeof(double) * No_of_users * No_of_movies); Non normalized Utility matrix
					  
					  double *normalized_matrix, // defined as double *normalized_matrix = (double *)malloc(sizeof(double) * No_of_users * No_of_movies); new matrix where normalize matrix will be stored
					  
					  int No_of_users,
					  
					  int No_of_movies
					  );
					  
void normalize( //normalizes ratings of new user(1D array)
			   double *user, // defined as double *user = malloc(sizeof(double) * No_of_movies); contains ratings from the new user.
			   
			   double *normalizeduser, // defined as double *normalizeduser = malloc(sizeof(double) * No_of_movies); contains normalized ratings of the new user.
			   
			   int No_of_movies //length of array
			  );

#endif
