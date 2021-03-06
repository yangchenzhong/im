#include "util.h"
#include "./log/io.h"
#include <sys/resource.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int getmaxfilenumber()
{
	struct rlimit rlt;
	if (getrlimit(RLIMIT_NOFILE, &rlt) == 0)
	{
		return rlt.rlim_cur;
	}

	return 1024;
}

int setmaxfilenumber(int filenumber)
{
	struct rlimit rlt;
	if (getrlimit(RLIMIT_NOFILE, &rlt) == 0)
	{
		rlt.rlim_cur = (filenumber >= rlt.rlim_max) ? rlt.rlim_max : filenumber;
		if (setrlimit(RLIMIT_NOFILE, &rlt) == 0)
		{
			return SUCCESS;
		}
	}

	return FAILED;
}

int setcorefilesize(int filesize)
{
	struct rlimit rlt;
	if (getrlimit(RLIMIT_CORE, &rlt) == 0)
	{
		rlt.rlim_cur = (filesize >= rlt.rlim_max) ? rlt.rlim_max : filesize;
		if (setrlimit(RLIMIT_CORE, &rlt) == 0)
		{
			return SUCCESS;
		}
	}

	return FAILED;
}

int getcorefilesize()
{
	struct rlimit rlt;
	if (getrlimit(RLIMIT_CORE, &rlt) == 0)
	{
		return rlt.rlim_cur;
	}

	return 0;
}

int getpidfromfile()
{
	int pid = -1;
	int fileno = -1;
	int flag = O_RDONLY;
	mode_t mode = S_IRUSR | S_IWUSR;
	if ((fileno = open("pid", flag, mode)) != -1)
	{
		char cpid[20];
		if (readline(fileno, cpid, 20) > 0)
		{
			pid = atoi(cpid);
		}

		closefile(fileno);
	}

	return pid;
}

int setpidtofile()
{
	int pid = getpid();
	int fileno = -1;
	int flag = O_WRONLY | O_CREAT;
	mode_t mode = S_IRUSR | S_IWUSR;
	if ((fileno = open("pid", flag, mode)) != -1)
	{
		/*清空文件*/
		clearfile(fileno);

		char cpid[20] = {0};
		sprintf(cpid, "%d", pid);
		if (writefile(fileno, cpid, strlen(cpid)) <= 0)
		{
			printf("%s\n", "write pid to file failed!");
			closefile(fileno);
			return FAILED;
		}

		closefile(fileno);
	}

	return SUCCESS;
}