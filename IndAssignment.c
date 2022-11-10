#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	int arr[]={2,4,6,8,10,0};
	int arrSize = sizeof(arr)/sizeof(int);
	int start, end;
	int pipefds[2];
	if (pipe(pipefds) == -1) {
		printf("Unable to call the pipe() \n");
		return 1;
	}
	
	int id = fork();
	if (id == -1) {
		return 2;
	}
	if (id == 0) {
		start=0;
		end=arrSize/2;
		
	} else {
		start=arrSize/2;
		end=arrSize;
		
	}
	
	int sum = 0;
	int i;
	for (i = start; i < end; i++) {
		sum += arr[i];
	}
	printf("Summation: %d\n", sum);
	
	
	if (id == 0) {
		close(pipefds[0]);
		write(pipefds[1], &sum, sizeof(sum));
		close(pipefds[1]);
		
	} else {
		int sumChild;
		close(pipefds[1]);
		read(pipefds[0], &sumChild, sizeof(sumChild));
		close(pipefds[0]);
		
		int total = sum + sumChild;
		printf("Total of summation: %d\n", total);
		
	}
	return 0;
}
