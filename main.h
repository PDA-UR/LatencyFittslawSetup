#ifndef __fitts_main__
#define __fitts_main__

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <pthread.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <sys/stat.h>

#define PI 3.14159265

#define WIDTH 1920
#define HEIGHT 1080

#define EASY 0
#define MEDIUM 1
#define HARD 2

#define NUM_WIDTH 15
#define NUM_DISTANCE 10

#define MAX_CLICKS 10000

#define DEBUG 0

#define TARGET_COLOR 0xFF000000
#define COLOR_BLACK 0xFF000000
#define COLOR_WHITE 0xFFFFFFFF
#define COLOR_RED 0xFF0000FF
#define COLOR_HEIDENELKE 0xFF4B009C
#define COLOR_HEIDENELKE_LIGHT 0xFF8B40DC
#define BACKGROUND_COLOR 0xFFCCCCCC

#define NUM_TARGET 20

#define NUM_ITERATIONS NUM_WIDTH * NUM_DISTANCE

#define LOG_PATH "log"

extern int PARTICIPANT_ID;
extern int EXPERIMENT;
extern int LATENCY_CLICK_MIN;
extern int LATENCY_CLICK_MAX;
extern int LATENCY_MOVE_MIN;
extern int LATENCY_MOVE_MAX;

extern int TARGET_WIDTH[NUM_WIDTH];
extern int TARGET_DISTANCE[NUM_DISTANCE];

extern int click_count_total;

extern int current_target;

typedef struct {
    int w;
    int d;
} TargetTemplate;

typedef struct {
    double x;
    double y;
    int w;
    int d;
    int n;
} Target;

//typedef struct {
//    int id;
//    long timestamp;
//    int w;
//    int d;
//    double time;
//    int clicks;
//    int travel_distance;
//    int num_targets;
//} Sequence;

typedef struct {
    int id;
    int sequence;
    int trial;
    long timestamp;
    int w;
    int d;
    int x_target;
    int y_target;
    int x_cursor;
    int y_cursor;
    int x_cursor_start;
    int y_cursor_start;
    double time; // in ms
    int clicks;
    int travel_distance;
} Trial;

typedef struct {
    int id;
    int sequence;
    long timestamp;
    int w;
    int d;
    int x_target;
    int y_target;
    int x_cursor;
    int y_cursor;
    int distance; // target -> cursor
    int success;
} Click;

TargetTemplate targetTemplates[NUM_ITERATIONS];

Click clicks[MAX_CLICKS];

Trial trials[NUM_TARGET * NUM_ITERATIONS];

//Sequence sequences[NUM_ITERATIONS];

// templates
TargetTemplate createTargetTemplate(int w, int d);

Target createTarget(int n, int d, int w);

void initTargetTemplates();

// utils
void swap(TargetTemplate *a, TargetTemplate *b);

long millis();

long long micros();

int min(int a, int b);

int max(int a, int b);

int checkCollision(int x, int y, Target *t);

int calculateDistance(int x1, int y1, int x2, int y2);

// log
void logClicks();

void logTrials();

//void logSequences();

// main
void finish();

void handleInput();

void render(SDL_Renderer* renderer);

void update(double deltaTime);

int main(int argc, char** argv);

#endif
