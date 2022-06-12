#include<stdio.h>

typedef struct
{
    int winner;
    int loser;
}
pair;

int cmpnum(const void *n1, const void *n2);

int main (void) {
  int array[10] = { 2, 1, 8, 5, 4, 7, 9, 0, 6, 3 };
  int i;

  qsort(pairs, pair_count, sizeof(pair), cmpnum);
}

// For qsort function (compare to margin between pairs)
int cmpnum(const void *n1, const void *n2)
{
    // 
    long m1 = preferences[((pair *)n1)->winner] - preferences[((pair *)n1)->loser];
    long m2 = preferences[((pair *)n2)->winner] - preferences[((pair *)n2)->loser];

    if (m1 > m2)
    {
        return -1;
    }
    else if (m1 < m2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
