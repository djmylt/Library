/*
 * Sparse Table
 *
 * Performs range minimum queries in constant time
 * nlogn building time
 *
 * Author: Shrey Banga
 */
#include <cstdio>
#include <cstdlib>
#include <time.h>

#define FORab(i,a,b) for(int i = (a); i < (b); i++)
#define FORn(i,n) FORab(i,0,n)

template <typename T>
T MIN(const T& a, const T& b) {
  return (a < b) ? a : b;
}

template <typename T>
T MAX(const T& a, const T& b) {
  return (a > b) ? a : b;
}

template <typename T>
void SWAP(T& a, T& b) {
  T t = a;
  a = b;
  b = t;
}

template <class T>
class SparseTable {
  public:
  SparseTable(T* a, int n)
  : max(n), logmax(0), A(a), M(0) {
    while((1 << logmax) <= max)
      logmax++;
    logmax++;

    M = new int*[logmax];
    for(int i = 0; i < logmax; i++)
      M[i] = new int[max];

    // Populate first row
    for(int j = 0; j < max; j++)
      M[0][j] = j;

    // Populate rest using recurrence
    // M[i][j] = M[i][j-1] + M[i + 2^(j-1)][j-1]
    for(int i = 1; i < logmax; i++) {
      int k = 1 << (i - 1);
      for(int j = max - 1; j >= (max - k); j--)
        M[i][j] = M[i-1][j];
      for(int j = max - k - 1; j >= 0; j--) {
        int p = M[i-1][j], q = M[i-1][j+k];
        M[i][j] = (A[p] < A[q]) ? p : q;
      }
    }
  }

  // Assuming i <= j and i,j are in range
  int rmq(int i, int j) {
    int diff = j-i+1, k = 0, w = 2;
    while(w < diff) {
      w <<= 1;
      k++;
    }
    w >>= 1;
    int l = MAX(0, j + 1 - w);
    int p = M[k][i], q = M[k][l];
    return (A[p] < A[q]) ? p : q;
  }

  ~SparseTable() {
    for(int i = 0; i < logmax; i++)
      delete[] M[i];
    delete[] M;
  }

  private:
  int max, logmax;
  T *A;
  int **M;

  SparseTable(const SparseTable& t)
  : max(t.max), logmax(t.logmax), A(0), M(0) {
  }

  SparseTable& operator = (const SparseTable&) {
    return *this;
  }
};

int main(int argc, char **argv) {
    int count = atoi(argv[1]);
    clock_t start;
    double time = 0;
    FILE *list_file = fopen("list", "r");
    int *a = new int[count];
    int x;
    int i, j;
    for(i = 0; i < count; i++)
        fscanf(list_file, "%d", &a[i]);
    fclose(list_file);

    SparseTable<int> t(a, count);

    FILE *result_file = fopen("sparse_table_results", "w");

    FILE *query_file = fopen("queries", "r");

    while(fscanf(query_file, "%d %d\n", &i, &j) == 2) {
        start = clock();
        x = t.rmq(i,j);
        time += (double)(clock() - start) / (CLOCKS_PER_SEC/1000);
        fprintf(result_file, "%d\n", x);
    }

    fclose(query_file);

    fclose(result_file);
    FILE *process_file = fopen("/proc/self/statm", "r");
    unsigned long size, resident, share, text, lib, data, dt;
    if (fscanf(process_file, "%lu %lu %lu %lu %lu %lu %lu", &size, &resident, &share, &text, &lib, &data, &dt) == 7) {
        printf("%f,%lu,%lu\n", time, size, data);
    }
    fclose(process_file);
}

