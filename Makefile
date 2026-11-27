CC := clang
CFLAGS := -g -Wall -Werror -Wno-unused-function -Wno-unused-variable

all: work-scheduler

clean:
	rm -f work-scheduler

work-scheduler: work-scheduler.c 
	$(CC) $(CFLAGS) -o work-scheduler work-scheduler.c -lform -lncurses -lpthread

zip:
	@echo "Generating work-scheduler.zip file to submit to Gradescope..."
	@zip -q -r work-scheduler.zip . -x .git/\* .vscode/\* .clang-format .gitignore work-scheduler
	@echo "Done. Please upload work-scheduler.zip to Gradescope."