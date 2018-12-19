#include "define.h"
#include "request.h"
#include "queue_list.h"
#include "comparison.h"

void init_queue_list(struct queue_list *queue)
{
	queue->length = 0;
	queue->in = NULL;
	queue->out = NULL;
}

void qin_list(struct queue_list *queue, struct request *new)
{
	if (queue->out == NULL && queue->in == NULL)
	{
		queue->in = new;
		queue->out = queue->in;
	}
	else
	{
		queue->in->next = new;
		queue->in = new;
	}
	new->next = NULL;
	queue->length++;
}

int is_empty_queue_list(struct queue_list *queue)
{
	return (queue->length == 0) ? 1 : 0;
}

struct request qout_list(struct queue_list *queue)
{
	struct request *tmp;
	struct request x;
	x = *(queue->out);
	tmp = queue->out;
	queue->out = queue->out->next;

	if (queue->out == NULL)
	{
		queue->in = NULL;
	}
	free(tmp);
	queue->length--;
	return x;
}

void create_new_request_list(struct request *new, float t1, float t2, float t3, float t4)
{
	new->arrival_time = randomfloat(t1, t2);
	new->process_time = randomfloat(t3, t4);
	new->down_time = 0;
}

void waiting_in_queue_list(struct queue_list *queue, float t)
{
	for (struct request *i = queue->out; i; i = i->next)
	{
		i->down_time += t;
	}
}

void list(void)
{
	int iter = 0;
	float length = 0;
	float t = 0, ta = 0;
	int p = 0;

	struct queue_list *q2 = malloc(sizeof(struct queue_list));
	init_queue_list(q2);
	struct request *new = (struct request*)malloc(sizeof(struct request));
	create_new_request_list(new, t1, t2, t3, t4);
	qin_list(q2, new);
	struct request *old = (struct request*)malloc(sizeof(struct request));
	*old = qout_list(q2);
	t = old->process_time;
	idle = old->arrival_time;
	new = (struct request*)malloc(sizeof(struct request));
	create_new_request_list(new, t1, t2, t3, t4);
	ta = new->arrival_time;

	printf("%sОбработано       Текущая длина     Средняя длина\n", GREEN);
	printf("  заявок            очереди            очереди%s\n", RESET);

	while (n != 1000)
	{
		iter++;
		length += q2->length;

		if (t < ta)
		{
			waiting_in_queue_list(q2, t);
			if (is_empty_queue_list(q2) == 0)
			{
				model += t;
				ta -= t;
			}
			else
			{
				model += ta;
				idle += ta-t;
				qin_list(q2, new);
				count_in++;
				new = (struct request*)malloc(sizeof(struct request));
				create_new_request_list(new, t1, t2, t3, t4);
				ta = new->arrival_time;
			}
			old = (struct request*)malloc(sizeof(struct request));
			*old = qout_list(q2);
			t = old->process_time;
			count_work++;
			p = rand() % 100;
			if (p < 80)
			{
				old->down_time = 0;
				qin_list(q2, old);
			}
			else
			{
				// free(old);
				twait += old->down_time;
				n++;
				if (n % 100 == 0 && n != 0)
					printf(" %5d               %3d                 %.2f\n", n, q2->length, length/iter);
			}
		}
		else
		{
			qin_list(q2, new);
			count_in++;
			model += ta;
			new = (struct request*)malloc(sizeof(struct request));
			create_new_request_list(new, t1, t2, t3 ,t4);
			t -= ta;
			ta = new->arrival_time;
		}
	}
	while (is_empty_queue_list(q2) != 1)
	{
		*old = qout_list(q2);
	}
	free(q2);
	free(new);
	free(old);


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

void print_table(struct queue_list *que)
{
	printf("%s         Заявка                 Адрес \n", GREEN);
	printf("пocтупление    обработка       в памяти%s\n", RESET);

	for (struct request *i = que->out; i; i = i->next)
	{
		printf("  %.2f           %.2f          %p\n", i->arrival_time, i->process_time, (void*)i);
	}
	printf("\n");

}

int fragmentation(void)
{
	int choice = -1;
	struct queue_list *que = malloc(sizeof(struct queue_list));
	init_queue_list(que);
	struct request *new;

	do
	{
		print_table(que);
		printf("%s[1] - добавление заявки в очередь\n", CYAN);
		printf("[2] - исключение заявки из очереди\n");
		printf("[0] - выход%s\n", RESET);
		printf("\nВаш выбор: ");
		scanf("%d", &choice);

		switch (choice)
		{
			case 1:
				new = (struct request*)malloc(sizeof(struct request));
				create_new_request_list(new, t1, t2, t3, t4);
				qin_list(que, new);
				break;
			case 2:
				if (is_empty_queue_list(que) == 0)
					qout_list(que);
				else
				{
					printf("%sОчередь пуста!%s\n", RED, RESET);
				}
				break;
			case 0:
				break;
			default:
				printf("%sОшибка! Такого пункта меню не существует!%s\n", RED, RESET);
				return WRONG_INPUT;
		}
	} while (choice != 0);

	while (is_empty_queue_list(que) != 1)
	{
		qout_list(que);
	}
	free(que);

	return SUCCESS;
}
