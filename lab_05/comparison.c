#include "define.h"
#include "queue_arr.h"
#include "queue_list.h"
#include "request.h"

unsigned long long int tick(void)
{
	unsigned long long int time = 0;
	__asm__ __volatile__ ("rdtsc" : "=A" (time));
	return time;
}

float randomfloat(float min, float max)
{
	return (float) rand() / RAND_MAX * (max - min) + min;
}

void compare(int n)
{
	struct queue_list *que_list = malloc(sizeof(struct queue_list));
	init_queue_list(que_list);
	struct queue_arr *que_arr = malloc(sizeof(struct queue_arr));
	init_queue_arr(que_arr);
	struct request *list, array;
	unsigned long long timel1, timel2, timel3;
	unsigned long long timea1, timea2, timea3;

	timel1 = tick();

	for (int i = 0; i < n; i++)
	{
		list = (struct request*)malloc(sizeof(struct request));
		create_new_request_list(list, t1, t2, t3, t4);
		qin_list(que_list, list);
	}
	timel2 = tick();

	for (int i = 0; i < n; i++)
		qout_list(que_list);
	timel3 = tick();
	//free(list);
	free(que_list);

	timea1 = tick();

	for (int i = 0; i < n; i++)
	{
		array = create_new_request_arr(t1, t2, t3, t4);
		qin_arr(que_arr, array);
	}
	timea2 = tick();

	for (int i = 0; i < n; i++)
		qout_arr(que_arr);
	timea3 = tick();
	free(que_arr);

	printf("%s                  Время  входа        Время выхода     Используемая\n", GREEN);
	printf("                   %d заявок          %d заявок         память\n%s", n, n, RESET);
	printf(" %s Массив%s           %6lld тик         %8lld тик       %4d байт\n",GREEN, RESET, timea2 - timea1, timea3 - timea2, (int)sizeof(struct queue_arr));
	printf("  %sСписок%s           %6lld тик         %8lld тик       %4d байт\n", GREEN, RESET, timel2 - timel1, timel3 - timel2, (int)sizeof(struct queue_list)*SIZE + (int)sizeof(struct request));
}
