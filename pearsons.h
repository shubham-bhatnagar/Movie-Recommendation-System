//header file for pearsons.c 
#ifndef PEARSONS_H
#define PEARSONS_H

void calc_similarity(
					double *normalizeduser, //Normalized ratings of new user
					
					double *normalized_matrix, //Normalized matrix
					
					double *similarity, //where similarity will be stored defined as double *similarity = malloc(sizeof(double) * No_of_users);
					
					int No_of_users,
					
					int No_of_movies 
					);

#endif
