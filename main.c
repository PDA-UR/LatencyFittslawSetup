#include "main.h"

int PARTICIPANT_ID = 0;
int EXPERIMENT = 0;
int LATENCY_CLICK_MIN = 0;
int LATENCY_CLICK_MAX = 0;
int LATENCY_MOVE_MIN = 0;
int LATENCY_MOVE_MAX = 0;

int iteration = 0;
int click_count = 0;
int click_count_total = 0;
//int click_count_sequence = 0;
int travel_distance = 0;
int travel_distance_sequence = 0;
int lastX;
int lastY;
int cursor_x_start = 0;
int cursor_y_start = 0;

double trial_time = 0;
//double sequence_time = 0;

int TARGET_WIDTH[NUM_WIDTH] = {100, 95, 90, 85, 80, 75, 70, 65, 60, 55, 50, 45, 40, 35, 30}; // 15
int TARGET_DISTANCE[NUM_DISTANCE] = {650, 600, 550, 500, 450, 400, 350, 300, 250, 200}; // 10

int mouse_down = 0;

Target targets[NUM_TARGET];

int current_target;

void initTargets()
{
    for(int i = 0; i < NUM_TARGET; i++)
    {
        targets[i] = createTarget(i, targetTemplates[iteration].d, targetTemplates[iteration].w);
    }

    current_target = 0;

    if(iteration >= NUM_ITERATIONS) finish();
}

void finish()
{
    // write log files
    logClicks();
    logTrials();
    //logSequences();

    SDL_Quit();
    exit(1);
}

void handleInput()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (event.button.button == SDL_BUTTON_LEFT || event.button.button == SDL_BUTTON_RIGHT)
            {
        		mouse_down = 1;

                int mouseX, mouseY;

                SDL_GetMouseState(&mouseX, &mouseY);

                Target target = targets[current_target];

                int success = checkCollision(mouseX, mouseY, &target);
                
                // handle click
                Click click = { click_count_total,
                                iteration,
                                millis(),
                                target.w,
                                target.d,
                                target.x,
                                target.y,
                                mouseX,
                                mouseY,
                                max(calculateDistance(target.x, target.y, mouseX, mouseY) - target.w / 2, 0),
                                success};

                clicks[click_count_total] = click;

                click_count_total++;
                click_count++;
                //click_count_sequence++;

                if(success)
                {
                    Trial trial = { (iteration * NUM_TARGET) + current_target,
                                    iteration,
                                    current_target,
                                    millis(),
                                    target.w,
                                    target.d,
                                    target.x,
                                    target.y,
                                    mouseX,
                                    mouseY,
                                    cursor_x_start,
                                    cursor_y_start,
                                    trial_time,
                                    click_count,
                                    travel_distance};

                    //printf("%d %d %d %d\n", iteration, NUM_TARGET, current_target, (iteration * NUM_TARGET) + current_target);
                    trials[(iteration * NUM_TARGET) + current_target] = trial;
                    // add to array

                    current_target++;
                    click_count = 0;
                    travel_distance = 0;
                    trial_time = 0;
                    cursor_x_start = mouseX;
                    cursor_y_start = mouseY;

                    if(current_target == NUM_TARGET)
                    {
                        iteration++;
                        initTargets();
                    }
                }
            }
        }

	    // test
        if (event.type == SDL_MOUSEBUTTONUP)
        {
            if (event.button.button == SDL_BUTTON_LEFT || event.button.button == SDL_BUTTON_RIGHT)
            {
		        mouse_down = 0;
		    }
	    }

        if(event.type == SDL_KEYDOWN)
        {
            switch(event.key.keysym.sym)
            {
            case SDLK_q:
                finish();
                SDL_Quit();
                exit(1);
                break;
            }
        }
    }
}

void render(SDL_Renderer* renderer)
{
    //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderClear(renderer);

    for(int i = NUM_TARGET; i >= current_target; i--)
    {
        if(i == current_target) filledCircleColor(renderer, targets[i].x, targets[i].y, targets[i].w / 2, COLOR_HEIDENELKE);

        circleColor(renderer, targets[i].x, targets[i].y, targets[i].w / 2, COLOR_BLACK);

        //else
        //{
        //    //filledCircleColor(renderer, targets[i].x, targets[i].y, targets[i].w / 2, COLOR_BLACK);
        //    //filledCircleColor(renderer, targets[i].x, targets[i].y, (targets[i].w / 2) - 3, COLOR_WHITE);
        //}
    }

    // circle in bottom right corner used to measure end to end latency
    if(!mouse_down)
    {
    	filledCircleColor(renderer, 1900, 1000, 100, TARGET_COLOR);
    }

    SDL_RenderPresent(renderer);
}

void update(double deltaTime)
{
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    trial_time += deltaTime;
    //sequence_time += deltaTime;

    int dist = calculateDistance(mouseX, mouseY, lastX, lastY);

    travel_distance += dist;
    //travel_distance_sequence += dist;

    lastX = mouseX;
    lastY = mouseY;
    
    //Target target = targets[current_target];

}

int main(int argc, char** argv)
{
    if(sscanf(argv[1], "%d", &PARTICIPANT_ID) == EOF) printf("incorrect partcipant id");
    if(sscanf(argv[2], "%d", &EXPERIMENT) == EOF) printf("incorrect experiment id");
    if(sscanf(argv[3], "%d", &LATENCY_CLICK_MIN) == EOF) printf("incorrect latency click min");
    if(sscanf(argv[4], "%d", &LATENCY_CLICK_MAX) == EOF) printf("incorrect latency click max");
    if(sscanf(argv[5], "%d", &LATENCY_MOVE_MIN) == EOF) printf("incorrect latency move min");
    if(sscanf(argv[6], "%d", &LATENCY_MOVE_MAX) == EOF) printf("incorrect latency move max");

    double timer = micros();
    double deltaTime = 0;
    SDL_Window* window;
    SDL_Renderer* renderer;

    srand(time(0));

    SDL_Init(SDL_INIT_EVERYTHING);

    initTargetTemplates();

    window = SDL_CreateWindow(__FILE__, 0, 0, WIDTH, HEIGHT, SDL_WINDOW_FULLSCREEN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    system("xsetroot -cursor_name arrow");

    initTargets();

    while(1)
    {
        deltaTime = (micros() - timer) / 1000000.0;
        timer = micros();

        update(deltaTime);
        handleInput();
        render(renderer);
	    //usleep(2000);
    }

    SDL_Quit();

    return 0;
}
