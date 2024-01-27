#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

int **create_2d_array(int nrow, int ncol)
{
  int **a = (int **)malloc(nrow * sizeof(int *));
  for (int i = 0; i < nrow; i++)
  {
    a[i] = (int *)malloc(ncol * sizeof(int));
  }
  return a;
}

void free_2d_array(int **a, int nrow)
{
  for (int i = 0; i < nrow; i++)
  {
    free(a[i]);
  }
  free(a);
}

int **get_rand_matrix(int nrow, int ncol)
{
  int **a = create_2d_array(nrow, ncol);
  srand(time(NULL));
  for (int i = 0; i < nrow; i++)
  {
    for (int j = 0; j < ncol; j++)
    {
      a[i][j] = rand() % 100;
    }
  }
  return a;
}

void write_matrix(int **a, int nrow, int ncol, char *filename)
{
  FILE *f = fopen(filename, "w");
  fprintf(f, "%d %d\n", nrow, ncol);
  for (int i = 0; i < nrow; i++)
  {
    for (int j = 0; j < ncol; j++)
    {
      fprintf(f, "%d", a[i][j]);
      if (j < ncol - 1)
        fprintf(f, " ");
    }
    if (i < nrow - 1)
      fprintf(f, "\n");
  }
  fclose(f);
}

int **read_matrix(char *filename)
{
  int nrow, ncol;
  //int nrow = get_line_count(filename);
  //int ncol = nrow;
  FILE *f = fopen(filename, "r");
  fscanf(f, "%d %d\n", &nrow, &ncol);
  int **a = create_2d_array(nrow, ncol);
  for (int i = 0; i < nrow; i++)
  {
    for (int j = 0; j < ncol; j++)
    {
      fscanf(f, "%d", &a[i][j]);
    }
  }
  fclose(f);
  return a;
}

void print_matrix(int **a, int nrow, int ncol)
{
  for (int i = 0; i < nrow; i++)
  {
    for (int j = 0; j < ncol; j++)
    {
      printf("%d", a[i][j]);
      if (j < ncol - 1)
        printf(" ");
    }
    printf("\n");
  }
}

bool array_equal(int **a, int **b, int nrow, int ncol)
{
  for (int i = 0; i < nrow; i++)
  {
    for (int j = 0; j < ncol; j++)
    {
      if (a[i][j] != b[i][j])
        return false;
    }
  }
  return true;
}

int main(int argc, char const *argv[])
{
    //below statements run if one command line arguments is supplied
    if (argc == 2) {
      int nrow = strtol(argv[1], NULL, 10), ncol = strtol(argv[1], NULL, 10);
      int **a = get_rand_matrix(nrow, ncol);
      int **c = get_rand_matrix(nrow, ncol);
      print_matrix(a, nrow, ncol);
      print_matrix(c, nrow, ncol);
      char *filename = "matrix3.txt";
      write_matrix(a, nrow, ncol, filename);
      append_matrixes(filename, c, nrow, ncol);
      int **b = read_matrix(filename);
      assert(array_equal(a, b, nrow, ncol));
      free_2d_array(b, nrow);
      free_2d_array(a, nrow);
      free_2d_array(c, nrow);
    }
    //below statements run if two command line arguments are supplied
    if(argc == 3) {
      char *file1 = argv[1];
      char *file2 = argv[2];

      int nrows = get_line_count(file1);

      int **a = read_matrix(file1);
        print_matrix(a, nrows, nrows);
        int **b = read_matrix(file2);
        print_matrix(b, nrows, nrows);
        char *filename = "matrix3.txt";
        write_matrix(a, nrows, nrows, filename);
        append_matrixes(filename, b, nrows, nrows);

        free_2d_array(a, 3);
        free_2d_array(b, 3);
    } 
    //below statements run if no command line arguments are supplied
    else {
        int condition;
        printf("Would you like to input a file name(1) or an integer(2)?");
        scanf("%d", &condition);
        if (condition == 1) {
          //statements runs if inpout is a file name
          char *file1[20];
          char *file2[20];
          printf("Input a file name: ");
          scanf("%s", &file1);
          printf("Input another file name: ");
          scanf("%s", &file2);

          //get number of rows
          int nrows = get_line_count(file1);

          int **a = read_matrix(file1);
          print_matrix(a, nrows, nrows);
          int **b = read_matrix(file2);
          print_matrix(b, nrows, nrows);
          char *filename = "matrix3.txt";
          write_matrix(a, nrows, nrows, filename);
          append_matrixes(filename, b, nrows, nrows);

          free_2d_array(a, nrows);
          free_2d_array(b, nrows);


        } else if (condition == 2) {
          //statements run if the input is an integer
          printf("Input an integer: ");
          int nrow;
          scanf("%d", &nrow);
          int ncol = nrow;
          int **a = get_rand_matrix(nrow, ncol);
          int **c = get_rand_matrix(nrow, ncol);
          print_matrix(a, nrow, ncol);
          print_matrix(c, nrow, ncol);
          char *filename = "matrix3.txt";
          write_matrix(a, nrow, ncol, filename);
          write_matrix(c, nrow, ncol, filename);
          int **b = read_matrix(filename);
          assert(array_equal(a, b, nrow, ncol));
          free_2d_array(b, nrow);
          free_2d_array(a, nrow);
        }
    }
  return 0;
}

void append_matrixes(char *file1, int **a, int nrow, int ncol) {
  FILE *f = fopen(file1, "a");
  fprintf(f, "\n%d %d\n", nrow, ncol);
  for (int i = 0; i < nrow; i++)
  {
    for (int j = 0; j < ncol; j++)
    {
      fprintf(f, "%d", a[i][j]);
      if (j < ncol - 1)
        fprintf(f, " ");
    }
    if (i < nrow - 1)
      fprintf(f, "\n");
  }
  fclose(f);
}

int get_line_count(char *file) {
  FILE *f = fopen(file, "r");

  char c;

  int count = 0;

  while (c != EOF) {
    c = getc(f);
    if (c == '\n') {
      count++;
    }
  }
  fclose(f);

  return count;
}