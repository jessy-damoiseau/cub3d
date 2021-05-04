#include "../includes/gnl.h"
#include "../includes/cub3d.h"

int check_file2(char *arg)
{
    int fd;
   // char str[33];

    if ((fd = open(arg, O_RDONLY)) < 0)
    {
        close(fd);
        return (fprintf(stderr, "Error\n open fouare\n"));
    }
    //--------//
    //--------//
    //--------//
    close(fd);
    return (0);
}

int check_file(int ac, char **av, int *i)
{
    if (ac == 3)
    {
        if (cmp(av[1], "--save"))
            return (fprintf(stderr, "Error\n movais paramettre\n"));
        else
            *i = 2;
    }
    if (ac < 2 && ac > 3)
    {
        if (ac < 2)
            fprintf(stderr, "Error\n pas assez d'args\n");
        else
            fprintf(stderr, "Error\n trop d'args\n");
        return (1);
    }
    if (cmp(&av[*i][len(av[*i] - 4)], ".cub"))
        return (fprintf(stderr, "Error\n fichier sans extention .cub\n"));
    return (check_file2(av[(*i)]));
}

int fill_and_checkerror(t_global *global, t_psing *psing)
{
    t_file *tmp;
    int i;

    while (psing->parse.nb_pfill != 8)
    {
        i = 0;
        if (psing->file->line[0] == 'R' && psing->file->line[1] == ' ' && !psing->parse.r)
        {
                i++;
                if (check_error_r(psing->file->line, &psing->parse.r, global))
                    return (1);
        }
        else if (psing->file->line[0] == 'R' && psing->file->line[1] == ' ' && psing->parse.r)
            return (fprintf(stderr, "Error\nparametre R en double\n"));

        if (psing->file->line[0] == 'F' && psing->file->line[1] == ' ' && !psing->parse.f)
        {
            i++;
            if (check_error_fc(psing->file->line, &psing->parse.f, global, 'F'))
                return (1);
        }
        else if (psing->file->line[0] == 'F' && psing->file->line[1] == ' ' && psing->parse.f)
            return (fprintf(stderr, "Error\nparametre F en double\n"));

        if (psing->file->line[0] == 'C' && psing->file->line[1] == ' ' && !psing->parse.c)
        {
            i++;
            if (check_error_fc(psing->file->line, &psing->parse.c, global, 'C'))
                return (1);
        }
        else if (psing->file->line[0] == 'C' && psing->file->line[1] == ' ' && psing->parse.c)
            return (fprintf(stderr, "Error\nparametre C en double\n"));

        if (psing->file->line[0] == 'N' && psing->file->line[1] == 'O' && psing->file->line[2] == ' ' && !psing->parse.no)
        {
            i++;
            if (check_error_texture(psing->file->line, global, 'N'))
                return (1);
        }
        else if (psing->file->line[0] == 'N' && psing->file->line[1] == 'O' && psing->file->line[2] == ' ' && psing->parse.no)
            return (fprintf(stderr, "Error\nparametre NO en double\n"));

        if (psing->file->line[0] == 'S' && psing->file->line[1] == 'O' && psing->file->line[2] == ' ' && !psing->parse.so)
        {
            i++;
            if (check_error_texture(psing->file->line, global, 'S'))
                return (1);
        }
        else if (psing->file->line[0] == 'S' && psing->file->line[1] == 'O' && psing->file->line[2] == ' ' && psing->parse.so)
            return (fprintf(stderr, "Error\nparametre SO en double\n"));

        if (psing->file->line[0] == 'W' && psing->file->line[1] == 'E' && psing->file->line[2] == ' ' && !psing->parse.we)
        {
            i++;
            if (check_error_texture(psing->file->line, global, 'W'))
                return (1);
        }
        else if (psing->file->line[0] == 'W' && psing->file->line[1] == 'E' && psing->file->line[2] == ' ' && psing->parse.we)
            return (fprintf(stderr, "Error\nparametre WE en double\n"));

        if (psing->file->line[0] == 'E' && psing->file->line[1] == 'A' && psing->file->line[2] == ' ' && !psing->parse.ea)
        {
            i++;
            if (check_error_texture(psing->file->line, global, 'E'))
                return (1);
        }
        else if (psing->file->line[0] == 'E' && psing->file->line[1] == 'A' && psing->file->line[2] == ' ' && psing->parse.ea)
            return (fprintf(stderr, "Error\nparametr EA en double\n"));

        if (psing->file->line[0] == 'S' && psing->file->line[1] == ' ' && !psing->parse.s)
        {
            i++;
            if (check_error_sprite(psing->file->line, global))
                return (1);
        }
        else if (psing->file->line[0] == 'S' && psing->file->line[1] == ' ' && psing->parse.s)
            return (fprintf(stderr, "Error\nparametre S en double\n"));

        if (!i && psing->file->line && psing->parse.nb_pfill < 8)
            return (fprintf(stderr, "Error\n mauvais parametre\n"));
        tmp = psing->file;
        psing->file = psing->file->next;
        free(tmp);
    }
    while (!psing->file->line[0])
    {
        tmp = psing->file;
        psing->file = psing->file->next;
    }
    fill_map(psing);
    if (check_error_map(global))
        return (1);
    return (0);
}

int parse(int ac, char **av, t_global *global, t_psing *psing)
{
    int i;
    int fd;
    char *line;

    line = 0;
    psing->file = 0;
    i = 1;
    (void)ac;
    init_parse(global);
    //if (check_file(ac , av, &i))
    //    return (1);
    fd = open(av[i], O_RDONLY);
    while (gnl(fd, &line) == 1)
        lstadd_back(&psing->file, lstnew(line));
    lstadd_back(&psing->file, lstnew(line));
    if (lst_size(psing->file, psing) < 1)
        return (fprintf(stderr, "Error\nfichier vide\n"));
    if (fill_and_checkerror(global, psing))
        return (1);
    return (0);
}

void    init_parse(t_global *global)
{
    int i;

    i = 0;
    global->psing.parse.r = 0;
    global->psing.parse.no = 0;
    global->psing.parse.so = 0;
    global->psing.parse.we = 0;
    global->psing.parse.ea = 0;
    global->psing.parse.s = 0;
    global->psing.parse.f = 0;
    global->psing.parse.c = 0;
    global->psing.parse.map = 0;
    global->psing.parse.nb_pfill = 0;
    global->psing.value.rx = 0;
    global->psing.value.ry = 0;
    global->psing.value.save = 0;
    global->psing.parse.len_map = 0;
    while (i < 3)
    {
        global->psing.value.floor[i] = 0;
        global->psing.value.sky[i++] = 0;
    }
}

void	clear_parse(t_parse *parse)
{
	if (parse->s)
		free(parse->s);
	if (parse->no)
		free(parse->no);
	if (parse->so)
		free(parse->so);
	if (parse->ea)
		free(parse->ea);
	if (parse->we)
		free(parse->we);
	if (parse->map)
		free_ds(parse->map);
}