#include <cs50.h>
#include<stdio.h>

// Max number of candidates
#define MAX 9

typedef struct
{
    int winner;
    int loser;
}
pair;

int candidate_count = 4;
int pair_count = 4;


bool locked[MAX][MAX];

// check circle
int chkCircle(int w, int l, int flg)
{
    printf("flg,  %i\n", flg);
    if (flg == 1)
    {
        return flg;
    }
    else
    {
        // Check 'l' has edges pointing towards someone ( = has [l][?] == true )
        for (int i = 0; i < candidate_count; i++)
        {
            if (locked[l][i])
            {
                printf("l: %i, i: %i\n", l, i);
                // if 'w' find as a loser
                if ( w == i)
                {
                    printf("w(%i) == i(%i)\n", w, i);
                    // make a circle
                    flg = 1;
                    break;
                }
                else
                {
                    chkCircle(w, i, flg);
                }
            }
        }
        return flg;
    }
}
int cnt = 0;
int chkLoser(int w, int l)
{
    // Check 'l' has edges pointing towards someone ( = has [l][?] == true )
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[l][i])
        {
            // if 'w' find as a loser
            if (w == i)
            {
                // make a circle
                printf("l: %i, i: %i\n", l, i);
                return 1;
            }
            cnt += chkLoser(w, i);
        }
    }
    return 0;
}


int main (void) {

    locked[0][1] = true;
    locked[3][1] = true;
    locked[2][3] = true;

    chkLoser(2,0);
    printf("cnt %i\n", cnt);
    if (cnt == 0)
    {
        locked[2][0] = true;
        printf("true: no circle.\n");
    }
    else
    {
        printf("false: make a circle!\n");
    }

    return 0;
}
