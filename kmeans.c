//Credit: https://www.medphysics.wisc.edu/~ethan/kmeans/
//This file contains k-means clustering algorithm 
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define sqr(x) ((x)*(x))

#define MAX_CLUSTERS 16

#define MAX_ITERATIONS 100

#define BIG_double (INFINITY)

void fail(char *str)
  {
    printf(str);
    exit(-1);
  }

double calc_distance(int dim, double *p1, double *p2)
  {
    double distance_sq_sum = 0;
    int ii;

    for (ii = 0; ii < dim; ii++)
      distance_sq_sum += sqr(p1[ii] - p2[ii]);

    return distance_sq_sum;

  }

void calc_all_distances(int dim, int n, int k, double *X, double *centroid, double *distance_output)
  {
	int ii, jj;
    for (ii = 0; ii < n; ii++) // for each point
      for (jj = 0; jj < k; jj++) // for each cluster
        {
         // calculate distance between point and cluster centroid
          distance_output[ii*k + jj] = calc_distance(dim, &X[ii*dim], &centroid[jj*dim]);
        }
  }

double calc_total_distance(int dim, int n, int k, double *X, double *centroids, int *cluster_assignment_index)
 // NOTE: a point with cluster assignment -1 is ignored
  {
    double tot_D = 0;
    int ii;

   // for every point
    for (ii = 0; ii < n; ii++)
      {
       // which cluster is it in?
        int active_cluster = cluster_assignment_index[ii];

       // sum distance
        if (active_cluster != -1)
          tot_D += calc_distance(dim, &X[ii*dim], &centroids[active_cluster*dim]);
      }

    return tot_D;
  }

void choose_all_clusters_from_distances(int dim, int n, int k, double *distance_array, int *cluster_assignment_index)
  {
	int ii,jj;

   // for each point
    for (ii = 0; ii < n; ii++)
      {
        int best_index = -1;
        double closest_distance = BIG_double;

       // for each cluster
        for (jj = 0; jj < k; jj++)
          {
           // distance between point and cluster centroid

            double cur_distance = distance_array[ii*k + jj];
            if (cur_distance < closest_distance)
              {
                best_index = jj;
                closest_distance = cur_distance;
              }
          }

       // record in array
        cluster_assignment_index[ii] = best_index;
      }
  }

void calc_cluster_centroids(int dim, int n, int k, double *X, int *cluster_assignment_index, double *new_cluster_centroid)
  {
    int cluster_member_count[MAX_CLUSTERS];
	int ii,jj;

   // initialize cluster centroid coordinate sums to zero
    for (ii = 0; ii < k; ii++)
      {
        cluster_member_count[ii] = 0;

        for (jj = 0; jj < dim; jj++)
          new_cluster_centroid[ii*dim + jj] = 0;
     }

   // sum all points
   // for every point
    for (ii = 0; ii < n; ii++)
      {
       // which cluster is it in?
        int active_cluster = cluster_assignment_index[ii];

       // update count of members in that cluster
        cluster_member_count[active_cluster]++;

       // sum point coordinates for finding centroid
        for (jj = 0; jj < dim; jj++)
          new_cluster_centroid[active_cluster*dim + jj] += X[ii*dim + jj];
      }


   // now divide each coordinate sum by number of members to find mean/centroid
   // for each cluster
    for (ii = 0; ii < k; ii++)
      {
        if (cluster_member_count[ii] == 0)
          printf("WARNING: Empty cluster %d! \n", ii);

       // for each dimension
        for (jj = 0; jj < dim; jj++)
          new_cluster_centroid[ii*dim + jj] /= cluster_member_count[ii];  /// XXXX will divide by zero here for any empty clusters!

      }
  }

void get_cluster_member_count(int n, int k, int *cluster_assignment_index, int *cluster_member_count)
  {
	int ii;

   // initialize cluster member counts
    for (ii = 0; ii < k; ii++)
      cluster_member_count[ii] = 0;

   // count members of each cluster
    for (ii = 0; ii < n; ii++)
      cluster_member_count[cluster_assignment_index[ii]]++;
  }

void cluster_diag(int dim, int n, int k, double *X, int *cluster_assignment_index, double *cluster_centroid)
  {
    int cluster_member_count[MAX_CLUSTERS];
    int ii;

    get_cluster_member_count(n, k, cluster_assignment_index, cluster_member_count);

    //printf("  Final clusters \n");
    //for (ii = 0; ii < k; ii++)
      //printf("    cluster %d:     members: %8d, centroid (%f) \n", ii+1, cluster_member_count[ii], cluster_centroid[ii*dim + 0]);
  }

void copy_assignment_array(int n, int *src, int *tgt)
  {
	int ii;

    for (ii = 0; ii < n; ii++)
      tgt[ii] = src[ii];
  }

int assignment_change_count(int n, int a[], int b[])
  {
    int change_count = 0;
	int ii;

    for (ii = 0; ii < n; ii++)
      if (a[ii] != b[ii])
        change_count++;

    return change_count;
  }

void kmeans(
            int  dim,		                     // dimension of data

            double *X,                        // pointer to data
            int   n,                         // number of elements

            int   k,                         // number of clusters
            double *cluster_centroid,         // initial cluster centroids
            int   *cluster_assignment_final  // output
           )
  {
    double *dist                    = (double *)malloc(sizeof(double) * n * k);
    int   *cluster_assignment_cur  = (int *)malloc(sizeof(int) * n);
    int   *cluster_assignment_prev = (int *)malloc(sizeof(int) * n);


    if (!dist || !cluster_assignment_cur || !cluster_assignment_prev)
      fail("Error allocating dist arrays");

   // initial setup
    calc_all_distances(dim, n, k, X, cluster_centroid, dist);
    choose_all_clusters_from_distances(dim, n, k, dist, cluster_assignment_cur);
    copy_assignment_array(n, cluster_assignment_cur, cluster_assignment_prev);

   // BATCH UPDATE
    double prev_totD = BIG_double;
    int batch_iteration = 0;
    while (batch_iteration < MAX_ITERATIONS)
      {
//        printf("batch iteration %d \n", batch_iteration);
//        cluster_diag(dim, n, k, X, cluster_assignment_cur, cluster_centroid);

        // update cluster centroids
         calc_cluster_centroids(dim, n, k, X, cluster_assignment_cur, cluster_centroid);

        // deal with empty clusters
        // XXXXXXXXXXXXXX

        // see if we've failed to improve
         double totD = calc_total_distance(dim, n, k, X, cluster_centroid, cluster_assignment_cur);
         if (totD > prev_totD)
          // failed to improve - currently solution worse than previous
           {
            // restore old assignments
             copy_assignment_array(n, cluster_assignment_prev, cluster_assignment_cur);

            // recalc centroids
             calc_cluster_centroids(dim, n, k, X, cluster_assignment_cur, cluster_centroid);

            // printf("  negative progress made on this step - iteration completed (%.2f) \n", totD - prev_totD);

            // done with this phase
             break;
           }

        // save previous step
         copy_assignment_array(n, cluster_assignment_cur, cluster_assignment_prev);

        // move all points to nearest cluster
         calc_all_distances(dim, n, k, X, cluster_centroid, dist);
         choose_all_clusters_from_distances(dim, n, k, dist, cluster_assignment_cur);

         int change_count = assignment_change_count(n, cluster_assignment_cur, cluster_assignment_prev);

        // printf("%3d   %u   %9d  %16.2f %17.2f\n", batch_iteration, 1, change_count, totD, totD - prev_totD);
         fflush(stdout);

        // done with this phase if nothing has changed
         if (change_count == 0)
           {
            // printf("  no change made on this step - iteration completed \n");
             break;
           }

         prev_totD = totD;

         batch_iteration++;
      }

	cluster_diag(dim, n, k, X, cluster_assignment_cur, cluster_centroid);

   // write to output array
    copy_assignment_array(n, cluster_assignment_cur, cluster_assignment_final);

    free(dist);
    free(cluster_assignment_cur);
    free(cluster_assignment_prev);
  }
