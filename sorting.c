//contains sorting
void sort(int *recommended_movies, double *predicted_ratings, int no_of_recommended_movies){
	int i=0,j=0;
	
	//sorting recommended movies and their ratings from highest rating to lowest
	for(i=0;i<no_of_recommended_movies;i++){
		for(j=i+1;j<no_of_recommended_movies;j++){
			if(predicted_ratings[i]<predicted_ratings[j]){
				double temp1; int temp2;
				temp1 = predicted_ratings[i]; temp2 = recommended_movies[i];
				predicted_ratings[i] = predicted_ratings[j]; recommended_movies[i] = recommended_movies[j];
				predicted_ratings[j] = temp1; recommended_movies[j] = temp2;
			}
		}
	}
}
