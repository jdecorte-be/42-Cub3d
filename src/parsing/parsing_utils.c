#include "../../inc/cub3d.h"

int	isspawn(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	isdoor(char c)
{
	if (c == 'D')
		return (1);
	return (0);
}

int	isitem(char c)
{
	if (c == '2')
		return (1);
	return (0);
}

int	inmap(char c)
{
	if (c == '0' || isitem(c) || isspawn(c) || isdoor(c))
		return (1);
	return (0);
}

int	ismap(char c)
{
	if (c == '1' || isspawn(c) || inmap(c))
		return (1);
	return (0);
}
