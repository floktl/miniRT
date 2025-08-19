#include "../libft.h"

double ft_atof(const char *str)
{
	double result = 0.0;
	double sign = 1.0;
	int i = 0;
	// Skip whitespace
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	// Handle sign
	if (str[i] == '-')
	{
		sign = -1.0;
		i++;
	}
	else if (str[i] == '+')
		i++;
	// Parse integer part
	while (ft_isdigit(str[i]))
	{
		result = result * 10.0 + (str[i] - '0');
		i++;
	}
	// Parse decimal part
	if (str[i] == '.')
	{
		i++;
		double fraction = 0.1;
		while (ft_isdigit(str[i]))
		{
			result += (str[i] - '0') * fraction;
			fraction *= 0.1;
			i++;
		}
	}
	return (result * sign);
}
