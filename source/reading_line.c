/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:04:46 by mfrasson          #+#    #+#             */
/*   Updated: 2021/11/30 17:13:29 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char    *strcopy(char *src, char *dst)
{
    int i;

    i = 0;
    while (src[i])
    {
        dst[i] = src[i];
        i++;
    }
    return (dst);
}

char    *create_prompt(char *chars)
{
    char *prompt;

    strcopy(chars, prompt);
    return (prompt);
}

int main(void)
{
    HIST_ENTRY *history;
    char *line_read = (char *)NULL;
    char *prompt;

    prompt = create_prompt("️‍🔥 > ");
    line_read = readline(prompt);

    if (line_read && *line_read)
        add_history(line_read);

    printf("line_read: %s\n", line_read);

    history = history_get(1);

    printf("history: %s\n", history->line);
    return (0);
}
