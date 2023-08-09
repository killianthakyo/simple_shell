#include "main.h"

/**
 * path_handler - locates commands in PATH
 * @command: command to be located
 * Return: full path of the command
 */
char *path_handler(char *command)
{
	char *path, *path_copy, *file_path, *path_token;
	int len_command, len_directory;
	struct stat buff;

	path = getenv("PATH");
	if (path)
	{
		path_copy = strdup(path);
		len_command = _strlen(command);
		path_token = strtok(path_copy, ":");
		while (path_token)
		{
			len_directory = _strlen(path_token);
			file_path = malloc(len_command + len_directory + 2);
			if (file_path == NULL)
			{
				perror("Error allocating memory");
				exit(EXIT_FAILURE);
			}
			file_path = path_concat(path_token, file_path, command);
			if (stat(file_path, &buff) == 0)
			{
				free(path_copy);
				return (file_path);
			}
			else
			{
				free(file_path);
				path_token = strtok(NULL, ":");
			}
		}
		free(path_copy);
		if (stat(command, &buff) == 0)
		{
			return (command);
		}
		return (NULL);
	}
	return (NULL);
}
/**
 * path_concat - concat tokens to path
 * @path_token: path token
 * @command: command
 * @file_path: file path
 * Return: concatenated path
 */
char *path_concat(char *path_token, char *file_path, char *command)
{
	(void)*_strcpy(file_path, path_token);
	(void)*_strcat(file_path, "/");
	(void)*_strcat(file_path, command);
	(void)*_strcat(file_path, "\0");

	return (file_path);
}
