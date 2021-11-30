/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:04:46 by mfrasson          #+#    #+#             */
/*   Updated: 2021/11/30 17:36:03 by mfrasson         ###   ########.fr       */
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
    HIST_ENTRY *history;    // this type comes from history.h
    char *line_read = (char *)NULL;
    char *prompt;

    // prompt will store the string passed to create_prompt
    prompt = create_prompt("️‍🔥 > ");
    // line_read stores the input line
    line_read = readline(prompt);

    // stores line in history
    if (line_read && *line_read)
        add_history(line_read);

    printf("\nline_read: %s\n", line_read);

    // gets line history by index, starts in 1
    history = history_get(1);

    printf("\nhistory: %s\n\n", history->line);
    return (0);
}
