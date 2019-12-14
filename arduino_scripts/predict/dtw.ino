
//https://github.com/ncanac/dtw

//#include <math.h>
//#include <stdio.h>
//#include <stdlib.h>

int dtw(short *x, short *y, short xsize, short ysize, float window_frac)
{
    /* DTW distance algorithm based on
    https://en.wikipedia.org/wiki/Dynamic_time_warping */
    const short LARGE_VALUE = 32000;
    const short window_help = (xsize-ysize);
    const short min_window = abs(window_help);
    short i, j, minj, maxj, window;
    short dist, mini;
    short **distances = (short**)malloc((xsize + 1) * sizeof(short*));
    for(i = 0; i < xsize + 1; ++i) {
        distances[i] = (short*)malloc((ysize + 1) * sizeof(short));
    }

   
    window = window_frac*ysize;
    
    if(xsize > ysize) {
        window = window_frac*xsize;
    }

    if(window < min_window) {
        window = min_window;
    }

   
    for(i = 0; i <= xsize; ++i) {
        for(j = 0; j <= ysize; ++j) {
            distances[i][j] = LARGE_VALUE;
        }
    }
    distances[0][0] = 0;

    for(i = 0; i < xsize; ++i)
    {
        minj = i - window;
        if(minj < 0)
            minj = 0;
        maxj = i + window;
        if(maxj > ysize)
            maxj = ysize;
//        Serial.println(minj);
//        Serial.println(maxj);
        short diff;
        for(j = minj; j < maxj; ++j)
        {
            diff = x[i]-y[j];
            dist = abs(diff);
            mini = distances[i][j];
            if(mini > distances[i][j+1])
                mini = distances[i][j+1];
            if(mini > distances[i+1][j])
                mini = distances[i+1][j];
            distances[i+1][j+1] = dist + mini;
            
        }
    }

      dist = distances[xsize][ysize];
    
    for(i = 0; i < xsize + 1; ++i) {
        free(distances[i]);
    }
    free(distances);
    
    return dist;
}
