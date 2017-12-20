//header for sorting.c
#ifndef SORT_H
#define SORT_H

void sort(
		  int *recommended_movies, //list of recommended movies to be sorted based on there predicted ratings
		  
		  double *predicted_ratings, //predicted ratings of those movies
		  
		  int no_of_recommended_movies // no of recommended movies (size of arrays)
		  );
		  
#endif
