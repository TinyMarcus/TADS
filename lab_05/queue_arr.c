#include "define.h"
#include "request.h"
#include "queue_arr.h"
#include "comparison.h"

void init_queue_arr(struct queue_arr *queue)
{
	queue->first = 0;
	queue->last = 0;
}

int qin_arr(struct queue_arr *queue, struct request new)
{
	if (queue->last < SIZE)
	{
		queue->queue[queue->last] = new;
		queue->last++;
		return 0;
	}
	else
	{
		return 1;
	}
}

int is_empty_queue_arr(struct  queue_arr *queue)
{
	return (queue->last <= queue->first) ? 1 : 0;
}

struct request qout_arr(struct queue_arr *queue)
{
	struct request x = queue->queue[queue->first];
	queue->queue[queue->first] = queue->queue[queue->first + 1];

	// for (int i = queue->first; i < queue->last; i++)
	// {
	// 	queue->queue[i] = queue->queue[i+1];
	// }
	queue->first++;
	// queue->last--
	return x;
}

struct request create_new_request_arr(float t1, float t2, float t3, float t4)
{
	struct request new;
	new.arrival_time = randomfloat(t1, t2);
	new.process_time = randomfloat(t3, t4);
	new.down_time = 0;
	return new;
}

void waiting_in_queue_arr(struct queue_arr *queue, float t)
{
	for (int i = queue->first; i < queue->last; i++)
	{
		queue->queue[i].down_time += t;
	}
}

void array(void)
{
	int iter = 0;
	float length = 0;
	float t = 0, ta = 0;
	int p = 0;

	struct queue_arr *q1 = malloc(sizeof(struct queue_arr ));
	init_queue_arr(q1);
	struct request new = create_new_request_arr(t1, t2, t3, t4);
	qin_arr(q1, new);
	struct request old = qout_arr(q1);
	t = old.process_time;
	idle = old.arrival_time;
	new = create_new_request_arr(t1, t2, t3, t4);
	ta = new.arrival_time;

	//printf("t=%f idle=%f ta= %f\n", t, idle, ta);
	printf("%sОбработано       Текущая длина     Средняя длина\n", GREEN);
	printf("  заявок            очереди            очереди%s\n", RESET);
	while (n != 1000)
	{
		iter++;
		length += (q1->last - q1->first);

		if (t < ta)
		{
			waiting_in_queue_arr(q1, t);

			if (is_empty_queue_arr(q1) == 0)
			{
				model += t;
				ta -= t;
			}
			else
			{
				idle += ta-t;
				model += ta;
				if(qin_arr(q1, new))
				{
					printf("Очередь переполнена!\n");
					return;
				}
				count_in++;
				new = create_new_request_arr(t1, t2, t3, t4);
				ta = new.arrival_time;
			}
			old = qout_arr(q1);
			t = old.process_time;
			count_work++;

			p = rand() % 100;

			if (p < 80)
			{
				old.down_time = 0;

				if (qin_arr(q1, old))
				{
					printf("Очередь переполнена!\n");
					return;
				}
			}
			else
			{
				twait += old.down_time;
				n++;

				if (n % 100 == 0 && n != 0)
				{
					printf(" %5d               %3d                 %.2f\n", n, q1->last - q1->first, length/iter);
				}
			}
		}
		else
		{
			if (qin_arr(q1, new))
			{
				printf("Очередь переполнена!\n");
				return;
			}
			count_in++;
			model += ta;
			new = create_new_request_arr(t1, t2, t3, t4);
			t -= ta;
			ta = new.arrival_time;
		}
	}
	free(q1);

	printf("\nВремя моделирования - %s%.2f%s\n",GREEN, model, RESET);

	if (n != 0)
	{
		printf("Среднее время пребывания заявки в очереди - %s%.2f%s\n",GREEN, twait/n, RESET);
	}
	printf("\nВошедших заявок - %s%d%s\n",GREEN, count_in, RESET);
	printf("Вышедших заявок - %s%d%s\n",GREEN, n, RESET);
	printf("ОА проработал %s%d%s раз\n",GREEN, count_work, RESET);
	printf("Простой ОА - %s%.2f%s",GREEN, idle, RESET);

	float aver_in = (t1+t2)/2;
	float aver_out = (t3+t4)/2;
	printf("\n%sПогрешность по входу -  %.2f процентов\n",GREEN, 100*fabs(count_in - model/aver_in)/(model/aver_in));
	printf("Погрешность по выходу - %.2f процентов\n%s", 100*fabs(count_work*aver_out + idle - model)/(count_work*aver_out + idle), RESET);
}
