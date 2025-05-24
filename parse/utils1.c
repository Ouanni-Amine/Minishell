#include "minishell.h"

// char	*ft_strdup(const char *s1)
// {
// 	int		i;
// 	char	*p;

// 	p = (char *) malloc((ft_strlen(s1) + 1) * sizeof(char));
// 	if (!p)
// 		return (NULL);
// 	i = 0;
// 	while (s1[i])
// 	{
// 		p[i] = s1[i];
// 		i++;
// 	}
// 	p[i] = '\0';
// 	return (p);
// }

// static int	ft_check(int sign)
// {
// 	if (sign > 0)
// 		return (-1);
// 	return (0);
// }

// static int	fcount(int n)
// {
// 	int	b;
// 	int	count;

// 	b = 0;
// 	count = 0;
// 	if (n <= 0)
// 	{
// 		n = -n;
// 		count++;
// 	}
// 	b = n;
// 	while (b != 0)
// 	{
// 		b = b / 10;
// 		count++;
// 	}
// 	return (count);
// }

// static char	*myfunction1(char *p, int count, int n)
// {
// 	p[0] = '-';
// 	while (count-- > 1)
// 	{
// 		p[count] = (n % 10) + '0';
// 		n /= 10;
// 	}
// 	return (p);
// }

// static char	*myfunction2(char *p, int count, int n)
// {
// 	while (count-- > 0)
// 	{
// 		p[count] = (n % 10) + '0';
// 		n /= 10;
// 	}
// 	return (p);
// }

// char	*ft_itoa(int n)
// {
// 	int		count;
// 	char	*p;

// 	count = fcount(n);
// 	p = (char *) malloc((count + 1) * sizeof(char));
// 	if (!p)
// 		return (NULL);
// 	p[count] = '\0';
// 	if (n == -2147483648)
// 	{
// 		p[--count] = '8';
// 		n = -(n / 10);
// 		myfunction1(p, count, n);
// 	}
// 	else if (n == 0)
// 		p[0] = 0 + '0';
// 	else if (n >= 0)
// 		myfunction2(p, count, n);
// 	else if (n < 0)
// 	{
// 		n = -n;
// 		myfunction1(p, count, n);
// 	}
// 	return (p);
// }

// char	*ft_strchr(const char *s, int c)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		if ((unsigned char)s[i] == (unsigned char ) c)
// 			return ((char *)(s + i));
// 		i++;
// 	}
// 	if ((unsigned char )c == '\0')
// 		return ((char *)(s + i));
// 	return (NULL);
// }

// int	ft_isdigit(int c)
// {
// 	if (c >= 48 && c <= 57)
// 		return (1);
// 	return (0);
// }

// int	ft_atoi(const char *str)
// {
// 	int					i;
// 	int					sign;
// 	int long long		solve;

// 	i = 0;
// 	solve = 0;
// 	sign = 1;
// 	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
// 		i++;
// 	if (str[i] == '-' || str[i] == '+')
// 	{
// 		if (str[i] == '-')
// 			sign = -1;
// 		i++;
// 	}
// 	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
// 	{
// 		if (solve > (((9223372036854775807) - (str[i] - '0')) / 10))
// 			return (ft_check(sign));
// 		solve = solve * 10 + str[i] - '0';
// 		i++;
// 	}
// 	return (solve * sign);
// }

// static char	*ft_null(char const *s1, char const *s2)
// {
// 	if (!s1 && !s2)
// 		return (NULL);
// 	if (!s1)
// 		return (ft_strdup(s2));
// 	if (!s2)
// 		return (ft_strdup(s1));
// 	return (NULL);
// }

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	int		i;
// 	int		j;
// 	char	*p;

// 	i = 0;
// 	j = 0;
// 	if (!s1 || !s2)
// 		return (ft_null(s1, s2));
// 	p = (char *) malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
// 	if (!p)
// 		return (NULL);
// 	while (s1[i])
// 	{
// 		p[i] = s1[i];
// 		i++;
// 	}
// 	while (s2[j])
// 	{
// 		p[i + j] = s2[j];
// 		j++;
// 	}
// 	p[i + j] = 0;
// 	return (p);
// }


size_t ft_count_str_with_space(char *str)
{
	size_t i = 0;
	size_t count = 0;
	while (str[i])
	{
		if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i + 1] == '<'))
			(count+=4, i+=2);
		else if (str[i] == '>' || str[i] == '<' || str[i] == '|')
			(count+=3, i++);
		else
			(count++,i++);
	}
	return (count);
}

int	ft_check_if_inside_cotes(char *str, size_t i)
{
	size_t len;
	size_t cool_double;
	size_t cool_single;

	len = 0;
	cool_double = 0;
	cool_single = 0;
	while (len <= i)
	{
		if (str[i] == '\"')
			cool_double++;
		else if (str[i] == '\'')
			cool_single++;
		len++;
	}
	if (cool_double == 0 && cool_single == 0)
		return (0);
	if (cool_double % 2 != 0 || cool_single % 2 != 0)
		return (1);
	return (0);
}

char *ft_make_str_with_space(char *str)
{
	size_t len = ft_count_str_with_space(str);
	size_t i = 0;
	size_t j = 0;
	char *new_str = (char *) malloc(sizeof(char) * (len + 1));
	while (str[i])
	{
		if (str[i] == '>' && str[i + 1] == '>' && ft_check_if_inside_cotes(str, i))
			(new_str[j++] = ' ', new_str[j++] = '>', new_str[j++] = '>', new_str[j++] = ' ', i+=2);
		else if (str[i] == '<' && str[i + 1] == '<' && ft_check_if_inside_cotes(str, i))
			(new_str[j++] = ' ', new_str[j++] = '<', new_str[j++] = '<', new_str[j++] = ' ', i+=2);
		else if (str[i] == '>' && ft_check_if_inside_cotes(str, i))
			(new_str[j++] = ' ', new_str[j++] = '>', new_str[j++] = ' ', i++);
		else if (str[i] == '<' && ft_check_if_inside_cotes(str, i))
			(new_str[j++] = ' ', new_str[j++] = '<', new_str[j++] = ' ', i++);
		else if (str[i] == '|' && ft_check_if_inside_cotes(str, i))
			(new_str[j++] = ' ', new_str[j++] = '|', new_str[j++] = ' ', i++);
		else
			(new_str[j++] = str[i],i++);
	}
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

char *ft_make_str_with_org_space(char *str)
{
	size_t len = ft_strlen(str);
	size_t i = 0;
	char *new_str = (char *) malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if (str[i] >= 9 && str[i] <= 13)
			new_str[i] = ' ';
		else
			new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char *ft_make_space(char *str)
{
	char *old_str = ft_make_str_with_org_space(str);
	char *new_str = ft_make_str_with_space(old_str);
	// printf ("%s\n",new_str);
	return (new_str);
}
