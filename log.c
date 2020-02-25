#include "main.h"

void logClicks()
{
    char path[256];
    sprintf(path, "%s/clicks_participant_%d_trial_%d.csv", LOG_PATH, PARTICIPANT_ID, EXPERIMENT);

	struct stat st_directory = {0};

    // create log directory if it doesn't exist
	if (stat(LOG_PATH, &st_directory) == -1) mkdir(LOG_PATH, 0777);

	FILE *logFile = fopen(path, "w");

	if (logFile == NULL)
	{
		printf("Error opening log file\n");
		return;
	}

    fprintf(logFile, "id,sequence,timestamp_ms,participant_id,experiment,latency_click_min,latency_click_max,latency_move_min,latency_move_max,target_width,target_distance,target_x,target_y,cursor_x,cursor_y,distance_cursor_target,success\n");

    //// print clicks
    for(int i = 0; i < click_count_total; i++)
    {
        fprintf( logFile,
                "%d,%d,%ld,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n", 
                clicks[i].id,
                clicks[i].sequence,
                clicks[i].timestamp,
                PARTICIPANT_ID,
                EXPERIMENT,
                LATENCY_CLICK_MIN,
                LATENCY_CLICK_MAX,
                LATENCY_MOVE_MIN,
                LATENCY_MOVE_MAX,
                clicks[i].w,
                clicks[i].d,
                clicks[i].x_target,
                clicks[i].y_target,
                clicks[i].x_cursor,
                clicks[i].y_cursor,
                clicks[i].distance,
                clicks[i].success);

    //    printf( "%d %d %ld | %d %d | %d %d %d %d | %d %d\n", 
    //            clicks[i].id,
    //            clicks[i].sequence,
    //            clicks[i].timestamp,
    //            clicks[i].w,
    //            clicks[i].d,
    //            clicks[i].x_target,
    //            clicks[i].y_target,
    //            clicks[i].x_cursor,
    //            clicks[i].y_cursor,
    //            clicks[i].distance,
    //            clicks[i].success);
    }

	if (fclose(logFile) == EOF)
	{
		printf("Error closing log file\n");
	}
}

void logTrials()
{
    char path[256];
    sprintf(path, "%s/iterations_participant_%d_trial_%d.csv", LOG_PATH, PARTICIPANT_ID, EXPERIMENT);

	struct stat st_directory = {0};

    // create log directory if it doesn't exist
	if (stat(LOG_PATH, &st_directory) == -1) mkdir(LOG_PATH, 0777);

	FILE *logFile = fopen(path, "w");

	if (logFile == NULL)
	{
		printf("Error opening log file\n");
		return;
	}

    fprintf(logFile, "id,sequence,trial,timestamp_ms,participant_id,experiment,latency_click_min,latency_click_max,latency_move_min,latency_move_max,target_width,target_distance,target_x,target_y,cursor_x,cursor_y,cursor_x_start,cursor_y_start,task_time_ms,clicks_needed,travel_distance\n");

    // log trials
    for(int i = 0; i < NUM_ITERATIONS * NUM_TARGET; i++)
    {
        fprintf( logFile,
                "%d,%d,%d,%ld,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%f,%d,%d\n", 
                trials[i].id,
                trials[i].sequence,
                trials[i].trial,
                trials[i].timestamp,
                PARTICIPANT_ID,
                EXPERIMENT,
                LATENCY_CLICK_MIN,
                LATENCY_CLICK_MAX,
                LATENCY_MOVE_MIN,
                LATENCY_MOVE_MAX,
                trials[i].w,
                trials[i].d,
                trials[i].x_target,
                trials[i].y_target,
                trials[i].x_cursor,
                trials[i].y_cursor,
                trials[i].x_cursor_start,
                trials[i].y_cursor_start,
                trials[i].time * 1000,
                trials[i].clicks,
                trials[i].travel_distance);
    }

    // print Trials
    //for(int i = 0; i < NUM_ITERATIONS * NUM_TARGET; i++)
    //{
    //    printf( "%d %d %ld | %d %d | %d %d %d %d | %f %d %d\n",
    //            trials[i].id,
    //            trials[i].sequence,
    //            trials[i].timestamp,
    //            trials[i].w,
    //            trials[i].d,
    //            trials[i].x_target,
    //            trials[i].y_target,
    //            trials[i].x_cursor,
    //            trials[i].y_cursor,
    //            trials[i].time,
    //            trials[i].clicks,
    //            trials[i].travel_distance);
    //}

	if (fclose(logFile) == EOF)
	{
		printf("Error closing log file\n");
	}
}
