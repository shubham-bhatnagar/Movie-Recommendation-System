//header for utility_matrix.h
#ifndef UTILITY_MATRIX_H
#define UTILITY_MATRIX_H

void get_movie_names(
					char *movienames, // defined as char *movienames = (char *)malloc(sizeof(char)* No_of_movies * 1024)); where movies will be stored

					char *s // source of dataset file
					);

void get_movie_genres(
					char *moviegenres, // defined as char *moviegenres = (char *)malloc(sizeof(char) * No_of_movies * 1024); where movie genres will be stored

					char *s // source of dataset file
					);

void get_utility_matrix(
						double *utility_matrix, // defined as double *utility_matrix = (double *)malloc(sizeof(double) * No_of_users * No_of_movies); where matrix will be stored

						char *s, // source of dataset file

						int No_of_movies,

						int No_of_users,

						int uid
						);

void new_user_movies(
                     double *newuser, //defined as double *newuser = (double *)malloc(sizeof(double) * No_of_movies); where ratings of new user will be stored

                     char *s, //source of new users' dataset file

                     int uid
                     );

#endif
