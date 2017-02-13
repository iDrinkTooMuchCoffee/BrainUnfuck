#include <stdio.h>
#include <stdlib.h>

void interpret(char* inst, long l_Size)
{
	char* tape = calloc(l_Size, 1);
	char* ptr = tape;
	
	for (;*inst != '\0'; ++inst)
	{
		switch (*inst)
		{
			case ' ': continue; 
			case '\n': continue;
			case '>': ++ptr; break;
			case '<': --ptr; break;
			case '+': ++*ptr; break;
			case '-': --*ptr; break;
			case '.': printf("%c", *ptr); break;
			case ',': *ptr = getchar(); break;
			case '[':
				if (!*ptr)
				{
					size_t loop = 1;
					while (loop)
					{
						++inst;
						if (*inst == ']')
							--loop;
						else if (*inst == '[')
							++loop;
					}
				}
				break;
			case ']':
				if (*ptr)
				{
					size_t loop = 1;
					while (loop)
					{
						--inst;
						if (*inst == '[')
							--loop;
						else if (*inst == ']')
							++loop;
					}
				}
				break;
			default:
				printf("Invalid character '%c'\n", *inst);
		}
	}

	free(tape);
}

void read_file(char* inputfile)
{
	FILE* fp;
	long lSize;

	fp = fopen(inputfile, "r");

	if (!fp)
	{
		printf("Error opening file: '%s'", inputfile);
		exit(1);
	}

	// Get the size of the file
	fseek(fp, 0L, SEEK_END);
	lSize = ftell(fp);
	rewind(fp);

	char* buffer = malloc(lSize + 1);
	fread(buffer, lSize, 1, fp);
	fclose(fp);
	buffer[lSize] = 0;

	interpret(buffer, lSize);
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		printf("usage: %s filename", argv[0]);
	}
	else
	{
		read_file(argv[1]);
	}

	exit(0);
	return 0;
}
