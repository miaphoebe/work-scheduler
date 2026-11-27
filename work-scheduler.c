#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_ARGS 7
#define MAX_LINE 256

void* threadHelper;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

typedef struct task{
    char taskName[MAX_LINE];
    char dueDate[MAX_LINE];
    char dueTime[MAX_LINE];
    double estTimeToComp;
    char dependentOn[MAX_LINE];
    char doBefore[MAX_LINE];
} task_t;

task_t task;

int read_field(FILE *input, char *line){
    char c;
    //char line[MAX_LINE];
    int i = 0;

    while(i < MAX_LINE -1){
        c = getc(input);
        if(c == EOF){
            if(i == 0){
                return -1;
            }
            break;
        }
        if(c == ';' || c == '\n'){
            break;
        }
        line[i] = c;
        i++;
    }
    // for (i = 0; 
    //     (i < MAX_LINE - 1) && ((c = getc(input)) != EOF) && c != ';' && c != '\n'; 
    //     i++){

    //    line[i] = c;
    //}

    // if(i == 0 && c == EOF){
    //     return -1;
    // }

    //i++;
    line[i] = '\0';
    
    // line[MAX_LINE - 1] = '\n';
    // for(int i = 0; i < MAX_ARGS; i++){
    //     args[i] = strsep(&line, ";");
    // }
    return i;
}

int read_task(FILE *input, task_t *task){
    char estTimeToComp[MAX_LINE];
    if(read_field(input, task->taskName) == -1){
        return 0;
    }
    //Reads the fields and checks
    if(read_field(input, task->dueDate) == -1){
        printf("failed to read dueDate\n");
        return -1;
    }
    if(read_field(input, task->dueTime) == -1){
        printf("failed to read dueTime\n");
        return -1;
    }
    if(read_field(input, estTimeToComp) == -1){
        printf("failed to read estTimeToComp\n");
        return -1;
    }
    if(read_field(input, task->dependentOn) == -1){
        printf("failed to read dependentOn\n");
        return -1;
    }
    if(read_field(input, task->doBefore) == -1){
        printf("failed to read doBefore\n");
        return -1;
    }

    //We used https://www.ibm.com/docs/en/zos/3.2.0?topic=functions-strtod-convert-character-string-double
    //to find the string to double function.
    task->estTimeToComp = strtod(estTimeToComp, NULL);

    return 1;
}

void* threadHelper(){

}
// in main:
// for (task in tasks)
// l make thread that starts with task as highest priority
// pick highest scoring task

int main(int argc, char **argv){
    FILE *input, *schedule;

    input = fopen(argv[1], "r");

    //const char delim[] = ";";

    //char* args[MAX_ARGS];

    //checks if the file opens
    if(input == NULL){
        perror("failed to open");
        exit(1);
    }

    schedule = fopen("schedule.txt", "w");

    if (schedule == NULL) {
        perror("failed to open");
        exit(1);
    }
//Setting the max number of tasks the user can have to 100.
    task_t tasks[100];
//number of tasks the user has
    int numTasks = 0;

    int result;

    while(numTasks < 100){
        result = read_task(input, &tasks[numTasks]);

        if(result == 0){
            break;
        }
        if(result == -1){
            printf("faild to read task!\n");
            break;
        }
        numTasks++;
    }

    //Loop print the tasks
    for(int i = 0; i < numTasks; i++){
        fprintf(schedule, "%s:\n", tasks[i].taskName);
        fprintf(schedule, "Due Date: %s\n", tasks[i].dueDate);
        fprintf(schedule, "Due Time: %s\n", tasks[i].dueTime);
        fprintf(schedule, "Estimated Time: %f\n", tasks[i].estTimeToComp);
        fprintf(schedule, "Depenent on: %s\n", tasks[i].dependentOn);
        fprintf(schedule, "Do Before: %s\n\n", tasks[i].doBefore);
    }

    // char c;
    // char line[MAX_LINE];
    // for (int i = 0; (i < MAX_LINE - 1) && ((c = getc(input)) != EOF); i++){
    //     line[i] = c;
    // }
    // line[MAX_LINE - 1] = '\n';
    // for(int i = 0; i < MAX_ARGS; i++){
    //     args[i] = strsep(&line, ";");
    // }

    
    // while ((c = getc(input)) != EOF){
    //     char line[MAX_LINE];
    //     for (int i = 0; c != '\n'; i++){
    //         line[i] = c;
    //         //putc(c, schedule);
    //     }
    //     for(int i = 0; i < MAX_ARGS; i++){
    //         args[i] = strsep(&line, ";");
    //     }
    // }
    // do {
    //     c = getc(input);
    //     putc(c, schedule);
    // }while (c != EOF);
    //char line[256];

    // while(fgets(line, sizeof(line), input) != NULL){
    //     printf("%s", line);
    // }
    fclose(input);
    fclose(schedule);
    return 0;

    // // threads!!
    // pthread_t thread;
    // int rc = pthread_create(&thread, NULL, threadHelper, NULL);


    // // task 1
    // // task 2

    // // thread 1: task 1 then task 2
    // // thread 2: task 2 then task 1
    // // winning thread: most completed tasks

    // // in each thread:
    // // - numCompletable
    // // - dependencies? : true if dependencies work out, 
    // // if ever false, return because thread failed

    // FILE *schedule = fopen("schedule.txt", "w");

    // if (schedule == NULL) {
    //     perror("failed to open");
    //     return 1;
    // }
    // fprintf(schedule, "hi");
}

