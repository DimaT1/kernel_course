#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define SYS_hello_world_kek 436
#define SYS_get_user 437
#define SYS_add_user 438
#define SYS_del_user 439

struct user_data {
	char *surname;
	unsigned int len;
	char *phone;
};

int main()
{
	long res;
	/*
	res = syscall(SYS_hello_world_kek);
	printf("system call returned: %ld\n", res);

	// insert
	struct user_data *a = malloc(sizeof(struct user_data));
	char *surname = malloc(4 * sizeof(char));
	surname[0] = 'k';
	surname[1] = 'e';
	surname[2] = 'k';
	surname[3] = '\0';
	a->surname = surname;
	a->len = 3;
	char *phone = malloc(4 * sizeof(char));
	surname[0] = '1';
	surname[1] = '2';
	surname[2] = '3';
	surname[3] = '\0';
	a->phone = phone;

	res = syscall(SYS_add_user, a);
	printf("a is: %ld\n", a);
	printf("add_user call returned: %ld\n", res);
	*/

 	struct user_data b;
 	res = syscall(SYS_get_user, "kek", 3, &b);
 	printf("get_user call returned: %ld\n", res);
 	printf("b is: %ld\n", (long)&b);
 	printf("%c\n", b.phone[0]);
 
	return 0;
}
