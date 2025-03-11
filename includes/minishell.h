/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:28:08 by jaimesan          #+#    #+#             */
/*   Updated: 2025/01/23 15:05:09 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _GNU_SOURCE

# include "../libft/includes/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <termios.h>

typedef enum s_quote_type
{
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
}	t_quote_type;

typedef struct s_quote
{
	int	single_quote;
	int	double_quote;
	int	escape;
	int	print;
	int	expansion;
}	t_quote;

typedef struct s_token
{
	char			**cmd;
	char			*path;
	char			*input_redir;
	char			*output_redir;
	char			*input_file;
	char			*output_file;
	char			*delimeter;
	char			*pipe;
	struct s_token	*next;
	int				is_builtin;
	int				complete;
	int				newline;
	int				expansion;
	int				access;
}	t_token;

typedef struct s_mini
{
	char			*input;
	char			**mini_cmds;
	char			**env;
	char			*log_name;
	char			*sesion_name;
	char			*full_name;
	char			*path;
	char			*env_name;
	char			*oldpath;
	char			*full_path;
	t_token			**commands;
	t_quote_type	*quote_types;
	t_quote_type	q;
	char			*name_clr;
	char			*pwd_clr;
	int				original_stdin;
	int				original_stdout;
	int				infile;
	int				outfile;
	int				cmd_count;
	int				pipes_i;
	int				i;
	int				oldpwd_off;
	int				**pipes;
	pid_t			*pids;
}	t_mini;

extern int	g_status;
//------------------------------------------------------------------MAIN
int				main(int argc, char **argv, char **envp);
int				main_commands(t_mini *mini);
void			init_struct(t_mini *mini, char **env);
//----------------------------------------------------------------SIGNALS
void			exit_codes(void);
void			exit_command(t_mini *mini, t_token *token);
void			handle_sigint(int signal);
void			handle_sigquit(int signal);
void			setup_signals(void);
//--------------------------------------------------------------------ENV
void			get_env_name(t_mini *mini);
void			get_session_name(t_mini *mini);
void			dup_env(t_mini *mini, char **env);
char			*join_env_name(t_mini *mini);
//----------------------------------------------------------------SETCOLOUR
void			set_colour(t_mini *m, t_token *t);
//----------------------------------------------------------------CD
void			cd(t_mini *mini, t_token *token);
void			save_oldpath(t_mini *mini, char *oldpath);
char			*check_per(t_mini *mini, t_token *token, char *path);
int				ft_chdir(char *path);
char			*handle_tilde_error(char *cleaned_cmd);
char			*handle_dash_option(t_mini *mini, char *cleaned_cmd);
char			*handle_general_path(t_mini *mini, t_token *token,
					char *cleaned_cmd);
char			*resolve_cd_path(t_mini *mini, t_token *token);
void			save_oldpwd(t_mini *mini, char *oldpath);
//----------------------------------------------------------------ENV
void			print_env(t_mini *mini);
//----------------------------------------------------------------HISTORY
void			print_history(void);
//----------------------------------------------------------------EXPORT
void			export(t_mini *mini, t_token *token);
void			new_export(t_mini *mini, t_token *token, int n);
int				export_exists(t_mini *mini, t_token *token, int n);
int				check_valid_export(t_token *token, int n);
void			sort_export(t_mini *mini);
//----------------------------------------------------------------UNSET
void			unset(t_token *token, t_mini *mini);
char			*find_env_variable(char **env, const char *key);
char			**ft_new_env(t_mini *mini, char *str, char **new_env);
//----------------------------------------------------------------ECHO
void			echo(t_token *token);
char			*parse_string(t_token *token, int n);
//----------------------------------------------------------------PWD
void			print_pwd(t_mini *mini);
//--------------------------------------------------------VARIABLE EXPANSION
char			*expand_variable(t_mini *mini, char *str);
char			*get_var_value(t_mini *mini, char *var_name);
char			*process_regular_char(char *res, char current_char, int *k);
char			*add_var_value(t_mini *mini, char *res, char *var_name);
char			*extract_var_name(char *str, int *i);
//-------------------------------------------------------PROCESS COMMANDS
void			process_commands(t_mini *mini);
void			process_commands2(t_mini *mini, int i, int j, int k);
void			handle_end_cmd(char **cmd_list, char **cmd, int *k, int *j);
char			*append_char_cmd(char *cmd, char c, int *k);
void			handle_redirections(t_mini *mini, char **cmd, int *i, int *j);
//-------------------------------------------------------TOKENIZE COMMANDS
int				tokenize_commands(t_mini *mini, char **cmds, t_token *cur);
char			**allocate_new_cmds(t_token *token, char **cmds,
					int *old_len, int *new_len);
int				tokenize_cmds(t_token *token, char **cmds);
int				tokenize_pipes(t_token *token, char **cmds);
int				tokenize_redirections(t_token *token,
					char **cmds, t_mini *mini);
int				tokenize_redirections_utils(t_token *token,
					char **cmds, t_mini *mini);
//-------------------------------------------------------QUOTATIONS COMMANDS
int				check_quotation(t_mini *mini);
char			*process_expansion(t_mini *mini, t_quote *q, char *cmd, int *i);
char			*process_quotes(t_mini *mini, t_quote *q, char *cmd, char *res);
char			*remove_quotes(t_mini *mini, t_quote *q, char *cmd);
int				process_token(t_mini *mini, t_quote *q, t_token *token);
void			init_quotes(t_quote *q);
//-------------------------------------------------------EXECUTE COMMANDS
void			execve_commands(t_mini *mini, t_token *token);
void			execute_commands(t_mini *mini);
void			execute_pipes(t_mini *mini, t_token *token);
void			single_command(t_mini *mini, t_token *token);
void			child_processing(t_mini *mini, t_token *token);
void			close_or_free_pipes(t_mini *mini, int mod);
void			fork_commands(t_mini *mini, t_token *token);
void			set_redirections(t_mini *mini, t_token *token);
void			set_redirections2(t_mini *mini, t_token *token);
int				count_commands(t_mini *mini);
void			command_setup(t_mini *mini);
int				count_commands(t_mini *mini);
void			builtin_commands(t_mini *mini, t_token *token);
void			ft_tokenadd_back(t_mini *mini, t_token *token);
t_token			*ft_newtoken(t_token *token);
void			get_quotes(t_quote *q, int c, int c2);
int				here_doc(t_mini *mini, t_token *token);
void			reset_fds(t_mini *mini, int mod);
//-------------------------------------------------------------------UTILS
void			free_main(t_mini *mini);
void			free_mini(t_mini *mini);
void			free_commands(t_mini *mini);
void			free_commands2(t_token *token);
void			error(t_mini *mini, char c);
int				is_builtin(char *cmd);
int				is_redirect(char *cmd);
int				is_input_redirect(char *cmd);
int				is_output_redirect(char *cmd);
int				count_commands(t_mini *mini);
t_quote_type	get_quote(t_quote_type quote, char c);
int				is_del(char cmd);
void			ft_check_path(t_token *token, t_mini *mini);
char			*find_path(t_mini *mini, char *path);
char			*resolve_cd_path(t_mini *mini, t_token *token);
char			*check_per(t_mini *mini, t_token *token, char *path);
int				check_valid_var(char *var_name);
void			save_shlvl(t_mini *mini);

#endif
