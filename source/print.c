
void print_connections(t_room **connections, int con_size)
{
	t_room **temp;
	int i;

	temp = connections;
	i = 0;
	printf("{");
	while (i < con_size)
	{
		printf("%s ", temp[i]->name);
		++i;
	}
	printf("}");
}

void print_rooms(t_room *nodes)
{
	t_room *temp;
			int i;

	temp = nodes;
	while (NULL != temp)
	{
		printf("%s [%d] (%d, %d) type - %d; con_size - %d, index - %d, weight - %d, ", 
			temp->name, temp->index, temp->coords.x, temp->coords.y, temp->type, temp->con_size, temp->index, temp->weight);
		if (0 != temp->con_size)
		{
			i = 0;
			printf("{");
			while (i < temp->con_size)
			{
				printf("%s ", temp->connections[i]->name);
				++i;
			}
			printf("}");
			// print_connections(temp->connections, temp->con_size);
		}
		printf("\n");
		temp = temp->next_a;
	}
}

void print_route(t_route *route)
{
	int i;

	i = -1;
	while (++i < route->size)
		printf("%s ", route->elem[i]->name);
	printf(" size - %d;\n", route->size);
}