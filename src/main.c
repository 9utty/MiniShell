/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 11:49:35 by gulee             #+#    #+#             */
/*   Updated: 2022/09/12 20:47:49 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_bool	not_big_shell(char **envp, t_env **env, int argc, char **argv)
{
	(void) argc;
	(void) argv;
	get_global_data()->exitcode = 0;
	printf("\033[32m ****     **            **     *  * ******      **");
	printf("\033[32m      ********  *  *           **               **  **\n");
	printf("\033[32m/**/**   /**           /**    /* /*/*////**    /**");
	printf("\033[32m     **//////**/* /*          /**              /** /**\n");
	printf("\033[32m/**//**  /**  ******  ******  /  / /*   /**    /**");
	printf("\033[32m    **      // /  /     ******/**       *****  /** /**\n");
	printf("\033[32m/** //** /** **////**///**/        /******     /**");
	printf("\033[32m   /**                 **     /******  **   ** /** /**\n");
	printf("\033[32m/**  //**/**/**   /**  /**         /*//// **   /**");
	printf("\033[32m   /**    *****       //***** /**///**/******* /** /**\n");
	printf("\033[32m/**   //****/**   /**  /**         /*    /** **/**");
	printf("\033[32m **//**  ////**        /////**/**  /**/**////  /** /**\n");
	printf("\033[32m/**    //***//******   //**        /******* /**/**");
	printf("\033[32m/** //********         ****** /**  /**//****** *** ***\n");
	printf("\033[32m//      ///  //////     //         ///////  // // ");
	printf("\033[32m//   ////////         //////  //   //  ////// /// /// \n");
	printf("\n                                                          ");
	printf("                   \033[32mMake by    jinkim2 && gulee\n");
	return (init_env_list(envp, env));
}

static char	*get_input(char *input, t_env *env)
{
	const char	prompt[] = "\033[32mMinishell>>$\033[0m ";

	while (1)
	{
		if (input)
			free(input);
		input = readline(prompt);
		if (!input)
		{
			printf("\033[32mMinishell>>$\033[0;31m exit\n\033[0m");
			exit(get_global_data()->exitcode);
		}
		else if (input[0] != '\0')
		{
			add_history(input);
			return (expander(lexer(input), env));
		}
	}
}

static void	norm_main(t_hdoc **hdoc_file)
{
	init_signals();
	del_hdoc_file(&(*hdoc_file));
}

int	main(int argc, char **argv, char **envp)
{
	t_hdoc	*hdoc_files;
	t_node	*cmds;
	char	*input;
	t_env	*env;
	int		index;

	index = 0;
	input = NULL;
	hdoc_files = NULL;
	if (not_big_shell(envp, &env, argc, argv) == FALSE_E)
		return (1);
	while (1)
	{
		norm_main(&hdoc_files);
		if (index++ > 0)
			del_cmd_list(&cmds);
		input = get_input(input, env);
		if (!input)
			continue ;
		cmds = parser(input, env);
		if (!cmds || heredoc(cmds, &hdoc_files, env) == -1)
			continue ;
		execute(&cmds, &env);
	}
	return (0);
}
