#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printGraph(int **, int );

int main(int argc, char** argv) {
	printf("starting ...\n");
	FILE* f_in = fopen("in.txt", "r");
	size_t len = 0;
	char* line = NULL;
	ssize_t read;
	int V = -1;
	int number;
	int **graph = NULL;

	int r = (int) strtol(argv[1], (char **)NULL, 10);
	int s = (int) strtol(argv[2], (char **)NULL, 10);
	printf("r=%i, s=%i\n", r, s);

	int i = 0;
	char *t;
	while ((read = getline(&line, &len, f_in)) != -1) {
		if (V == -1) {
			V = 1;
			char *line1 = malloc(sizeof(char)*strlen(line));
			strcpy(line1, line);
			t = strtok(line1, " ");
			while((t = strtok(NULL, " ")) != NULL) {
				V++;
			}
			printf("V=%i\n", V);
			graph = malloc(V*sizeof(int*));
			for (int j = 0 ; j < V ; j ++) {
				graph[j] = malloc(V*sizeof(int));
			}
		}
		int j = 0;
		t = strtok(line, " ");
		do {
			graph[i][j] = (int) strtol(t, (char **)NULL, 10);
			j++;
		} while ((t = strtok(NULL, " ")) != NULL);
		i++;
	}
	fclose(f_in);
	printGraph(graph, V);

	int d;
	int *p = malloc(V*sizeof(int));
	int *min_p = malloc(V*sizeof(int));
	int cml;
	int min = -1;
	int l;
	for (int k = r; k < V; k += s) {
		p[0] = k;
		d = 1;
		p[1] = -1;
		while (d >= 0) {
			p[d] ++;
			if (p[d] == V) {
				d --;
				continue;
			}
			if (graph[p[d-1]][p[d]] < 0) {
				continue;
			}
			cml = 0;
			for (int j = 0 ; j < d ; j ++) {
				if (p[j] == p[d]) {
					cml = 1;
					break;
				}
			}
			if (cml == 1) {
				continue;
			}
			//for (int j = 0 ; j <= d ; j ++) {
			//	printf("%i ", p[j]);
			//}
			//printf("\n");
			if (d == V-1) {
				int l = 0;
				for (int j = 1 ; j < V ; j ++) {
					l += graph[p[d-1]][p[d]];
				}
				if (min < 0 || l < min) {
					min = l;
					memcpy(min_p, p, V*sizeof(int));
				}
			} else {
				d ++;
				p[d] = -1;
			}
		}
	}

	FILE* f_out = fopen("out.txt", "w");
	if (min < 0) {
		fprintf(f_out, "%i\n", min);
	} else {
		fprintf(f_out, "%i\n", min);
		for (int j = 0 ; j < V ; j ++) {
			fprintf(f_out, "%i ", min_p[j]);
		}
	}
	fclose(f_out);
}

void printGraph(int **graph, int V) {
                for (int i = 0 ; i < V; i++) {
                        for (int j = 0 ; j < V; j++) {
                                printf("%i ", graph[i][j]);
                        }
                        printf("\n");
                }
}

