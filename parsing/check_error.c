#include "../includes/cub3d.h"

int check_error_r(char *line, int *c, t_global *global)
{
    int i;
    int nb_args;
    char *str;

    i = -1;
    nb_args = 1;
    trim(&str, line, "R ");
    while (str[++i])
        if ((str[i] < '0' && str[i] > '9') && str[i] != ' ')
            return (fprintf(stderr, "Error\n-R caractere indesirable\n"));
    i = 0;
    while (str[i])
    {
        if (str[i] == ' ')
        {
            while (str[i] && str[i] == ' ')
                i++;
            nb_args++;
        }
        i++;
    }
    if (nb_args != 2)
        return (fprintf(stderr, "Error\n-R pas le bon nombre de parametre\n"));
    fill_xy(str, &global->psing, c);
    return (0);
}

int check_error_fc(char *line, int *param, t_global *global, int c)
{
    int i;
    char *str;
    int nb_coma;

    i = -1;
    if (c == 'F')
        trim(&str, line, "F ");
    else
        trim(&str, line, "C ");
    while (str[++i])
        if (!(str[i] >= '0' && str[i] <= '9') && str[i] != ',')
            return (fprintf(stderr, "Error\n-%c caractere indesirable\n", c));
    i = 0;
    if (str[0] == ',' || str[len(str) - 1] == ',')
        return (fprintf(stderr, "Error\n-%c virgule au debout ou a la fin du parametre\n", c));
    nb_coma = nb_virgule(str);
    if (nb_coma != 3)
    {
        if (nb_coma < 3)
            return (fprintf(stderr, "Error\n-%c pas assez d'args\n", c));
        else
            return (fprintf(stderr, "Error\n-%c trop d'args\n", c));
    }
    fill_fc(str, &global->psing, param, c);
    return (0);
}

int check_error_texture(char *line, t_global *global, int c)
{
    int i;
    char *str;

    i = 0;
    if (c == 'N')
        trim(&str, line, "NO ");
    else if (c == 'S')
        trim(&str, line, "SO ");
    else if (c == 'W')
        trim(&str, line, "WE ");
    else
        trim(&str, line, "EA ");
    if (!str[i])
        return (fprintf(stderr, "Error\n texture %c pas assez d'args", c));
    while (str[i])
        if (str[i++] == ' ')
            return (fprintf(stderr, "Error\n texture %c trop d'args\n", c));
    if (cmp(&str[len(str) - 4], ".xpm"))
        return (fprintf(stderr, "Error\n texture %c n'est pas .xmp comme extention\n", c));
    fill_texture(str, &global->psing, c);
    return (0);
}

int check_error_sprite(char *line, t_global *global)
{
    int i;
    char *str;

    i = 0;
    trim(&str, line, "S ");
    if (!str[i])
        return (fprintf(stderr, "Error\n pas assez d'args pour le chemin des sprites"));
    while (str[i])
        if (str[i++] == ' ')
            return (fprintf(stderr, "Error\ntrop d'args pour le chemin sprites\n"));
    if (cmp(&str[len(str) - 4], ".xpm"))
        return (fprintf(stderr, "Error\n chemin pour les sprites n'a pas .xmp comme extention\n"));
    global->psing.parse.s = str;
    global->psing.parse.nb_pfill++;
    return (0);
}

int check_char_map(t_global *global)
{
    int i;
    int j;

    i = 0;
    while (global->psing.parse.map[i])
    {
        j = 0;
        while (global->psing.parse.map[i][j])
        {
            if (global->psing.parse.map[i][j] != ' ' && global->psing.parse.map[i][j] != '0' &&
            global->psing.parse.map[i][j] != '1' && global->psing.parse.map[i][j] != '2' && global->psing.parse.map[i][j] != 'N' &&
            global->psing.parse.map[i][j] != 'W' && global->psing.parse.map[i][j] != 'S' && global->psing.parse.map[i][j] != 'E')
                return (fprintf(stderr, "Error\n ligne %d, charatere %d, un %c se balade", i, j, global->psing.parse.map[i][j]));
            j++;
        }
        i++;
    }
    return (0);
}

int	check_hole(char **map)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '3' && (!find(map[i][j + 1])
			|| !find(map[i][j - 1])
			|| !find(map[i + 1][j]) || !find(map[i - 1][j])))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int check_spawn(t_global *global)
{
    int i;
    int j;
    int spawn;

    i = 0;
    spawn = 0;
    while (global->psing.parse.map[i])
    {
        j = 0;
        while (global->psing.parse.map[i][j])
        {
            if (global->psing.parse.map[i][j] == 'N' || global->psing.parse.map[i][j] == 'S'
            || global->psing.parse.map[i][j] == 'W' || global->psing.parse.map[i][j] == 'E')
            {
                global->psing.value.x = j;
                global->psing.value.y = i;
                spawn++;
            }
            j++;
        }
        i++;
    }
    if (spawn != 1)
        return (fprintf(stderr, "Error\n il y a %d point de spawn\n", spawn));
    return (0);
}

int     propagation(int x, int y, char **map, int stop)
{
    int    x_max;

    x_max = 0;
    while (map[x_max + 1])
        x_max++;
    if (x == x_max || x == 0 || !map[x][y + 1] || !map[x][y] || y == 0)
        return (1);
    if (!stop)
    {
        map[x][y] = '3';
        if (map[x][y + 1] == '0' || map[x][y + 1] == '2')
            propagation(x, y + 1, map, stop);
        if (map[x][y - 1] == '0' || map[x][y - 1] == '2')
            propagation(x, y - 1, map, stop);
        if (map[x + 1][y] == '0' || map[x + 1][y] == '2')
            propagation(x + 1, y, map, stop);
        if (map[x - 1][y] == '0' || map[x - 1][y] == '2')
            propagation(x - 1, y, map, stop);
    }
    if (map[x][y] == ' ' || map[x + 1][y] == ' ' || map[x - 1][y] == ' '
    || map[x][y + 1] == ' ' || map[x][y - 1] == ' ')
        stop = 1;
    return (check_hole(map));
}

int check_error_map(t_global *global)
{
    char **str;

    if (check_char_map(global))
        return (1);
    if (check_spawn(global))
        return (1);
    str = str_ds_dup(global->psing.parse.map);
    str[global->psing.value.y][global->psing.value.x] = '0';
    if (propagation(global->psing.value.y, global->psing.value.x, str, 0))
        return (fprintf(stderr, "Error\n la map accessible a un trou\n"));
    free_ds(str);
    return (0);
}