#include <stdio.h>
#include <stdlib.h>

void echo()
{
	printf("%s", "Enter a word to be echoed:\n");
	char buf[128];
	//gets(buf);
	fgets(buf, 128, stdin);
	printf("%s\n", buf);
}

int main()
{
	echo();
}
