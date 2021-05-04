#include "../includes/cub3d.h"


int    fill_xy(char *str, t_psing *psing, int *c)
{
    int i;

    i = 0;
    while (str[i] && str[i] != ' ')
        psing->value.rx = psing->value.rx * 10 + str[i++] - '0';
    if (psing->value.rx == 0)
        return (fprintf(stderr, "Error\n resolution x non valide\n"));
    while (str[i] && str[i] == ' ')
        i++;
    while (str[i])
        psing->value.ry = psing->value.ry * 10 + str[i++] - '0';
    if (psing->value.ry == 0)
        return (fprintf(stderr, "Error\n resolution y non valide\n"));
    psing->parse.nb_pfill++;
    (*c)++;
    free(str);
    return (0);
}

void    fill_f(char *str,t_psing *psing)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (str[i])
    {
        if (str[i] >= '0' && str[i] <= '9')
            psing->value.floor[j] = psing->value.floor[j] * 10 + str[i++] - '0';
        else
        {
            j++;
            i++;
        }
    }
    j = 0;
    while (j < 3)
        if (psing->value.floor[j++] > 255)
            psing->value.floor[j - 1] = 255;
}

void    fill_c(char *str,t_psing *psing)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (str[i])
    {
        if (str[i] >= '0' && str[i] <= '9')
            psing->value.sky[j] = psing->value.sky[j] * 10 + str[i++] - '0';
        else
        {
            j++;
            i++;
        }
    }
    j = 0;
    while (j < 3)
        if (psing->value.sky[j++] > 255)
            psing->value.sky[j - 1] = 255;
}

void    fill_fc(char *str, t_psing *psing, int *param, int c)
{
    if (c == 'F')
    {
        fill_f(str, psing);
    }
    else
    {
        fill_c(str, psing);
    }
    psing->parse.nb_pfill++;
    (*param)++;
    free(str);
}

void    fill_texture(char *str, t_psing *psing, int c)
{
    if (c == 'N')
        psing->parse.no = str;
    else if (c == 'S')
        psing->parse.so = str;
    else if (c == 'W')
        psing->parse.we = str;
    else
        psing->parse.ea = str;
    psing->parse.nb_pfill++;
}

int fill_map(t_psing *psing)
{
    int i;
    int j;
    int nb_map;
    t_file *tmp;

    i = 0;
    nb_map = lst_size(psing->file, psing);
    if (!nb_map)
        return (fprintf(stderr, "Error\n la map n'existe pas\n"));
    if (!(psing->parse.map = malloc(sizeof(char *) * (nb_map + 1))))
        return (fprintf(stderr, "Error\n malloc fail\n"));
    while(psing->file)
    {
        j = 0;
        if (!(psing->parse.map[i] = malloc(sizeof(char) * (psing->parse.len_map + 1))))
            return (fprintf(stderr, "Error\n malloc fail\n"));
        while (psing->file->line[j])
        {
            psing->parse.map[i][j] = psing->file->line[j];
            j++;
        }
        while (j < psing->parse.len_map)
            psing->parse.map[i][j++] = ' ';
        psing->parse.map[i][j] = 0;
        tmp = psing->file;
        psing->file = psing->file->next;
        free(tmp);
        i++;
    }  
    psing->parse.map[i] = 0;

    return (0);
}