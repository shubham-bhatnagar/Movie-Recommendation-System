//creates utility matrix
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void get_movie_names(char *movienames, char *s){
	char *line, *record;
	char tmp[1024];
	int i=0,j=0;
	FILE *fstream = fopen(s,"r");
	while((line=fgets(tmp,sizeof(tmp),fstream))!=NULL){ //traverse till end of file while storing each line
		record = strtok(line,","); //break line into multiple strings separated by comma
		while(record!=NULL){
			if(j==1){ //second string(i.e. moviename in the csv file)
				strcpy(&movienames[i*1024],record);
			}
			j++;
			record = strtok(NULL,","); //iterate
		}
		i++;j=0;
	}
	fclose(fstream);
	free(line);
	free(record);
}

void get_movie_genres(char *moviegenres, char *s){
	char *line, *record;
	char tmp[1024];
	int i=0,j=0;
	FILE *fstream = fopen(s,"r");
	while((line=fgets(tmp,sizeof(tmp),fstream))!=NULL){
		record = strtok(line,",");
		while(record!=NULL){
			if(j==1){
				strcpy(&moviegenres[i*1024],record);
			}
			j++;
			record = strtok(NULL,",");
		}
		i++;j=0;
	}
	fclose(fstream);
	free(line);
	free(record);
}

void get_utility_matrix(double *utility_matrix, char *s, int No_of_movies, int No_of_users, int uid){
	char *line, *record;
	char tmp[1024];
	int i=0, j=0, k=0;
	FILE *fstream = fopen(s,"r");
	while((line=fgets(tmp,sizeof(tmp),fstream))!=NULL){
		record = strtok(line,",");
		while(record!=NULL){
			if(k==0){ //first string is user id, which will give our row
                i = atoi(record)-1;
			}else if(k==1){ //second string is movie id which will give our coloumn
				j = atoi(record)-1;
			}else { //third is the actual rating
			    /*if(l == uid){
                    utility_matrix[i*No_of_movies+j] = 0.0;
			    }*/
			    //else{
                    utility_matrix[i*No_of_movies + j] = atof(record); //converting string to float/double
			    //}
			}
			record = strtok(NULL,",");
			k++;
		}
		k=0;
	}
	fclose(fstream);
	free(line);
	free(record);
}

void new_user_movies(double *newuser, char *s, int uid){
    char *line, *record;
	char tmp[1024];
	int i,j,k=0;
	FILE *fstream = fopen(s,"r");
	while((line=fgets(tmp,sizeof(tmp),fstream))!=NULL){
		record = strtok(line,",");
		while(record!=NULL){
            if(k==0){
                i = atoi(record) - 1;
            }
			if(k==1){
				j = atoi(record) - 1;
			}
			if(k==2){
				if(i+1==uid){
					newuser[j] = atof(record);
				}
			}
			k++;
			record = strtok(NULL,",");
		}
		k=0;
	}
	fclose(fstream);
	free(line);
	free(record);
}
