#include "shell.h"

/**
 * is_cmd - Determines if a file is an executable command
 * @info: Pointer to the info struct
 * @path: Pointer to the path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - Duplicates characters
 * @pathstr: Poiter to the PATH string
 * @start: Index to start
 * @stop: Index to end
 *
 * Return: Pointer to new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int j = 0, k = 0;

	for (k = 0, j = start; j < stop; j++)
		if (pathstr[j] != ':')
			buf[k++] = pathstr[j];
	buf[k] = 0;
	return (buf);
}

/**
 * find_path - Finds this cmd in the PATH string
 * @info: Pointer to the info struct
 * @pathstr: Pointer to the PATH string
 * @cmd: The cmd to find
 *
 * Return: Full path of cmd if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int j = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[j] || pathstr[j] == ':')
		{
			path = dup_chars(pathstr, curr_pos, j);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[j])
				break;
			curr_pos = j;
		}
		j++;
	}
	return (NULL);
}
