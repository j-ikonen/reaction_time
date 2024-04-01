#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// #include <unistd.h>
#include <pthread.h>

#define UPPER_LIM 8000  // ms
#define LOWER_LIM 1000  // ms


void wait_for_input(void *arg) {
        clock_t *hit = (clock_t *) arg;
        getchar();
        *hit = clock();
        pthread_exit(NULL);
}

float game_round() {
        pthread_t thread;
        clock_t current, start, hit, react;
        int err, wait;

        wait = rand() % (UPPER_LIM - LOWER_LIM + 1) + LOWER_LIM;
        react = ((float)wait / 1000) * CLOCKS_PER_SEC;
        err = pthread_create(&thread, NULL, wait_for_input, &hit);
        // Thread creation error
        if (err) {
                printf("An error occurred: %d", err);
                return 1;
        }

        printf("Wait for 'GO' and press ENTER.\n");
        start = clock();
        while(1) {
                current = clock();
                if (current > (react + start) ) {
                        printf("GO\n");
                        break;
                }
        }
        pthread_join(thread, NULL);

        
        float reaction_time = (float)(hit - start - react) / CLOCKS_PER_SEC;
        if (reaction_time <= 0) {
                printf("DQ, Reaction before 'GO'.\n");
        } else {
                printf("Reaction time: %f s.\n", reaction_time);
        }
        return reaction_time;
}

int main() {
        float record;
        int reaction_exists = 0;

        srand( time(NULL) );
        while(1) {
                if (reaction_exists) {
                        printf("Time to beat: %f s.\n", record);
                }
                float reaction = game_round();
                if (!reaction_exists || record > reaction) {
                        record = reaction;
                        reaction_exists = 1;
                        printf("New record!\n");
                }
                printf("\n");
        }

        return 0;
}
