static int	ft_isspace(char c)
{
	return ('\t' == c || '\n' == c || '\v' == c
		|| '\f' == c || '\r' == c || ' ' == c);
}

static void	skip_spaces(char *str, int *pos)
{
	while (str[*pos] && ft_isspace(str[*pos]))
		++*pos;
}

static int	get_num(char *str, int *pos)
{
	long int	num;

	num = 0;
	while (str[*pos] && str[*pos] >= '0' && str[*pos] <= '9')
	{
		num = num * 10 + (str[*pos] - '0');
		++*pos;
	}
	return (num);
}

static int	get_sign(char *str, int *pos)
{
	int	sign;

	sign = 1;
	while (str[*pos] && (str[*pos] == '+' || str[*pos] == '-'))
	{
		if (str[*pos] == '-')
			sign = -sign;
		++*pos;
	}
	return (sign);
}

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	num;

	i = 0;
	skip_spaces(str, &i);
	sign = get_sign(str, &i);
	num = get_num(str, &i);
	return (sign * num);
}