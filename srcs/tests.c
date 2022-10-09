/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 01:54:57 by sotherys          #+#    #+#             */
/*   Updated: 2022/10/09 21:04:18 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_left(int *pipefd, char **argv)
{
	int		pid;
	int		res;
	
	pid = fork();
	if (pid == -1) 
		return ;
	if (pid == 0)
	{//child
		dup2(pipefd[1], 1); //теперь fd=1 указывает не на STDOUT, а на pipefd[1]=fd для записи в пайп
		close(pipefd[0]);
		close(pipefd[1]);
		res = execve("/bin/echo", argv, NULL);
		if (res == -1)
		{
			ft_putstr_fd("Execve echo error", 2);
			return ;
		}
	}
	else
	{
		// close(pipefd[1]);
		waitpid(pid, NULL, 0);
		printf("echo success!!\n");
	}
		
}

void	pipe_right(int *pipefd, char **argv)
{
	int		pid;
	int		res;
	
	pid = fork();
	if (pid == -1) 
		return ;
	if (pid == 0)
	{
		dup2(pipefd[0], 0); //теперь 0 указывает не на STDIN, а на fd чтения из пайпа
		close(pipefd[0]);
		close(pipefd[1]);
		res = execve("/usr/bin/wc", argv, NULL);
		if (res == -1)
		{
			ft_putstr_fd("Execve wc error", 2);
			return ;
		}
	}
	else
	{
		close(pipefd[1]);
		// close(pipefd[0]); //если не закрывать pipefd[0] (read_end) нет зависания, главное закрыть pipefd[0] (write_end), иначе он будет бесконечно ждать записи в себя
		waitpid(pid, NULL, 0);
		printf("wc success!!\n");
	}
}

/*
	echo a b c d | wc
*/

void	pipe_()
{
	int		pipefd[2];
	char	*argv_left[6] = {"echo", "a", "b", "c", "d", NULL};
	char	*argv_right[2] = {"wc", NULL};

	pipe(pipefd);
	pipe_left(pipefd, argv_left);
	pipe_right(pipefd, argv_right);
}

void	many_pipes()
{
	int	pipe_n;
	int	pipefd[2]; //одной хватит, тк в каждом процессе клонируется
	
	
}

void	just_cmd(char **env)
{
	int		pid;
	int		res;
	char	*argv[3] = {"cd", "srcs", NULL};
	// char	*sh_argv[2] = {"minishell", NULL};
	
	pid = fork();
	if (pid == -1) 
		return ;
	if (pid == 0)
	{
		// res = execve("./minishell", sh_argv, NULL); //сперва искать в текущей директории
		res = execve("/usr/bin/cd", argv, env);
		if (res == -1)
		{
			ft_putstr_fd("Execve error", 2);
			return ;
		}
	}
	else
	{
		wait(NULL); //waitpid(pid, NULL, 0); //в процессе родителе директория не меняется
		
		char	cwd[999];
		if (getcwd(cwd, 999))
		{
			ft_putstr_fd("[just_cmd] getcwd: ", 1);
			ft_putstr_fd(cwd, 1);
			ft_putstr_fd("\n", 1);
		}
	}
}

int	redirect_out(char **env)
{
	int		pid;
	int		res;
	// char	*argv[2] = {"pwd", NULL};
	char	*argv[3] = {"cd", "srcs/", NULL};

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{ //если файл существует: c APPEND - дозапись, O_TRUNC - перезапись
	// с O_WRONLY | O_CREAT - запись в начало файла (новые данные перезатирают старые на длину новых)
	//у Толи > - O_WRONLY | O_CREAT | O_TRUNC  +
		 // >> - O_WRONLY | O_CREAT | O_APPEND +
		int fd = open("test_file2.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644); //0644 = default: rw-r–r– //O_TRUNC?
		if (fd == -1)
		{
			ft_putstr_fd("Open error: ", 2); ft_putstr_fd(strerror(errno), 2); ft_putstr_fd("\n", 2);
			return (-3);
		}	
		int fdd = dup2(fd, 1); // dup2(fd, STDOUT_FILENO); //fdd = 1
		if (fdd == -1)
		{
			ft_putstr_fd(strerror(errno), 2); ft_putstr_fd("\n", 2);
			return (-4);
		}
			
		ft_putstr_fd("before close(fd)\n", 1); printf("\n\n\nfdd %d\n\n", fdd); //printf не выводит сообщения в файл
		close(fd);
		// ft_putstr_fd("before execve\n", 1); printf("[printf] before execve\n\n");
		// res = execve("/bin/pwd", argv, NULL); 
		res = execve("/usr/bin/cd", argv, env);
		if (res == -1)
		{
			ft_putstr_fd("Execve error: could not find programm to execute", 2);
			ft_putstr_fd(strerror(errno), 2); ft_putstr_fd("\n", 2);
			return (-2);
		}
		printf("\nSUCCESS"); //эта строка вообще не выполняется, тк the successful execve call has no process to return to
		//current process overlay
	}
	else
	{
		int	w_status;
		waitpid(pid, &w_status, 0);
		if (WIFEXITED(w_status))
		{
			int w_code = WEXITSTATUS(w_status);
			if (w_code == 0)
				printf("\nSUCCESS after waitpid\n\n");
			else
				printf("FAILURE with wait_status_code %d\n", w_code);
			char	cwd[999];
			if (getcwd(cwd, 999))
			{
				ft_putstr_fd("getcwd: ", 1);
				ft_putstr_fd(cwd, 1);
				ft_putstr_fd("\n", 1);
			}
		}
	}
	return (0);
}

int	redirect_in()
{
	int		pid;
	char	*argv[1] = {NULL};

	pid = fork();
	if (pid < 0)
		return (-1);

	if (pid == 0)
	{
		int fd = open("srcs/test_stdin1", O_RDONLY, 0644); // int fd = open("test_stdin", O_RDONLY, 0644);
		if (fd == -1)
		{
			ft_putstr_fd(strerror(errno), 2); 
			ft_putstr_fd("\n", 2);
			exit(-3);
		}
		int fdd = dup2(fd, 0); //fdd = 0
		if (fdd == -1)
		{
			ft_putstr_fd(strerror(errno), 2); ft_putstr_fd("\n", 2);
			exit(-4);
		}
		close(fd);
		int res = execve("/bin/cat", argv, NULL); //имитирую работу команды cat без параметров, в терминале ждет заполнения STDIN, тут должен считать из файла
		if (res == -1)
		{
			ft_putstr_fd("Execve error: could not find programm to execute", 2);
			ft_putstr_fd(strerror(errno), 2); ft_putstr_fd("\n", 2);
			return (-2); //exit(-2);
		}
	}
	else
	{
		int	w_status;
		waitpid(pid, &w_status, 0);
		if (WIFEXITED(w_status))
		{
			int w_code = WEXITSTATUS(w_status); //переменной-статусу присваивать w_code
			if (w_code == 0 )
				ft_putstr_fd("\nSUCCESS after waitpid\n", 1);
			else
				ft_putstr_fd("\nFAILURE with wait_status_code\n", 2);
			printf("w_status=%d,  w_code %d\n", w_status, w_code);
			
		}
	}
	return (0);
}

int	pipe_test(char **env)
{
	int		pipefd[2];
	char	*argv_left[6] = {"echo", "a", "b", "c", "done", NULL};
	char	*argv_right[2] = {"wc", NULL};

	if (pipe(pipefd) == -1)
	{
		ft_putstr_fd(strerror(errno), 2); ft_putstr_fd("\n", 2);
		return (-2);
	}

	int pid1 = fork();
	if (pid1 < 0)
		return (-1);
	if (pid1 == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO); //теперь 1 будет указывать на write end пайпа
		close(pipefd[0]);
		close(pipefd[1]);
		execve("/bin/echo", argv_left, env);
	}
	

	int pid2 = fork();
	if (pid2 < 0)
		return (-1);
	if (pid2 == 0)
	{
		dup2(pipefd[0], STDIN_FILENO); //теперь 0 будет указывать на read end пайпа
		close(pipefd[0]);
		close(pipefd[1]);
		execve("/usr/bin/wc", argv_right, env);
	}
	close(pipefd[1]); //close(pipefd[0]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);

	return (0);
}

int	just_relative_cmd()
{
	int		pid;
	char	*argv[1] = {NULL};

	pid = fork();
	if (pid == 0)
	{
		int res = execve("/program", argv, NULL); //nEXECVE ERROR
		// execve("./program", argv, NULL); //program в той же директории, что и этот исполняемый файл
		// execve("../program", argv, NULL); //program в родительской директории относительно директории исполняемого файла

		if (res < 0)
		{
			printf("\nEXECVE FAILURE code = %d", res);
			ft_putstr_fd("bash: No such file or directory\n", 2);
			exit (127);
		}
			
	}
	else
	{
		int	w_status;
		waitpid(pid, &w_status, 0);
		if (WIFEXITED(w_status))
		{
			int w_code = WEXITSTATUS(w_status); //переменной-статусу присваивать w_code
			if (w_code == 0 )
				ft_putstr_fd("\nSUCCESS after waitpid\n", 1);
			else
				ft_putstr_fd("\nFAILURE with wait_status_code\n", 2);
			printf("w_status=%d,  w_code %d\n", w_status, w_code);
			
		}
	}
	return (0);
}

// gcc srcs/tests.c srcs/libft/ft_putstr_fd.c srcs/libft/ft_strlen.c -I includes/ && ./a.out && cat test_file2.txt && rm test_file2.txt
// gcc srcs/tests.c srcs/libft/ft_putstr_fd.c srcs/libft/ft_strlen.c -I includes/ && ./a.out
int	main(int argc, char **argv, char **env)
{
	// just_cmd(env);
	// redirect_out(env);
	// redirect_in();
	pipe_();
	pipe_test(env);
	// just_relative_cmd();
	
	many_pipes();
	return (0);
}






















/*
	./push_swap 8 5 4 7 | ./checher 8 5 4 7
*/

void	test1_left(int *pipefd, char **argv)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execve("/home/balamosh/school21/42_push_swap/push_swap", argv, NULL);
	}
	else
		waitpid(pid, NULL, 0);
}

void	test1_right(int *pipefd, char **argv)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execve("/home/balamosh/school21/42_push_swap/checker", argv, NULL);
	}
	else
	{
		close(pipefd[0]);
		close(pipefd[1]);
		waitpid(pid, NULL, 0);
	}
}

void	test1()
{
	int		pipefd[2];
	char	*argv[6] = {"push_swap", "8", "5", "4", "7", NULL};

	pipe(pipefd);
	test1_left(pipefd, argv);
	test1_right(pipefd, argv);
}

/*
	./checker 8 5 4 7 < cat ans.txt | wc -l
*/

/*
void	test2_checker(int in, int out, char **argv)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		dup_check(in, STDIN_FILENO);
		dup_check(out, STDOUT_FILENO);
		close_check(in);
		close_check(out);
		execve("/home/balamosh/school21/42_push_swap/checker", argv, NULL);
	}
	else
	{
		close_check(in);
		close_check(out);
		waitpid(pid, NULL, 0);
	}
}

void	test2_cat(int in, int out, char **argv)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		dup_check(in, STDIN_FILENO);
		dup_check(out, STDOUT_FILENO);
		close_check(in);
		close_check(out);
		execve("/usr/bin/cat", argv, NULL);
	}
	else
	{
		close_check(in);
		close_check(out);
		waitpid(pid, NULL, 0);
	}
}

void	test2_wc(int in, int out, char **argv)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		dup_check(in, STDIN_FILENO);
		dup_check(out, STDOUT_FILENO);
		close_check(in);
		close_check(out);
		execve("/usr/bin/wc", argv, NULL);
	}
	else
	{
		close_check(in);
		close_check(out);
		waitpid(pid, NULL, 0);
	}
}


void	test2()
{
	int		pipefd_1[2];
	int		pipefd_2[2];
	char	*argv_checker[] = {"checker", "8", "5", "4", "7", NULL};
	char	*argv_cat[] = {"cat", "ans.txt", NULL};
	char	*argv_wc[] = {"wc", "-l", NULL};

	pipe(pipefd_1);
	pipe(pipefd_2);
	test2_cat(0, pipefd_1[1], argv_cat);
	test2_checker(pipefd_1[0], pipefd_2[1], argv_checker);
	test2_wc(pipefd_2[0], 1, argv_wc);
}
*/


/*
	./push_swap 8 5 4 7 | wc -l > ans.txt
*/
/*
void	test3(int in, int out, char **argv)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		dup_check(in, STDIN_FILENO);
		dup_check(out, STDOUT_FILENO);
		close_check(in);
		close_check(out);
		execve("/usr/bin/echo", argv, NULL);
	}
	else
	{
		close_check(in);
		close_check(out);
		waitpid(pid, NULL, 0);
	}
}

*/