#include "main.h"

TargetTemplate createTargetTemplate(int w, int d)
{
    //if(DEBUG > 1) printf("createTargetTemplate()\n");

    TargetTemplate targetTemplate;
    targetTemplate.w = w;
    targetTemplate.d = d;
    return targetTemplate;
}

//Target createTarget(int x, int y, TargetTemplate *targetTemplate)
Target createTarget(int n, int d, int w)
{
    Target target;

    int x, y;
    double a;

    //a = (2 * PI / NUM_TARGET) * n;
    a = (2 * PI / NUM_TARGET) * (ceil(n / 2) + (n % 2) * ((NUM_TARGET + 1) / 2));

    //printf("%d %f\n", n, (ceil(n / 2) + (n % 2) * ((NUM_TARGET + 1) / 2)));

    x = (sin(a) * d) / 2;
    y = (cos(a) * d) / 2;

    target.n = n;
    target.x = x + WIDTH / 2;
    target.y = y + HEIGHT / 2;
    target.w = w;
    target.d = d;

    return target;
}

void initTargetTemplates()
{
    if(DEBUG > 1) printf("initTargetTemplates()\n");

    int i = 0;
    for(int w = 0; w < NUM_WIDTH; w++)
    {
        for(int d = 0; d < NUM_DISTANCE; d++)
        {
            targetTemplates[i] = createTargetTemplate(TARGET_WIDTH[w], TARGET_DISTANCE[d]);
            i++;
        }
    }

    if(DEBUG > 1) printf("templates created\n");


	for(int j = 0; j < NUM_ITERATIONS; j++)
	{
        TargetTemplate *a = &targetTemplates[j];
        TargetTemplate *b = &targetTemplates[rand() % NUM_ITERATIONS];
		swap(a, b);
	}

	//for(int j = 0; j < NUM_ITERATIONS; j++)
	//{
    //    printf("%d %d\n", targetTemplates[j].w, targetTemplates[j].d);
	//}

    if(DEBUG > 1) printf("end initTargetTemplates()\n");
}
