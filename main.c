#include "philo.h"

t_vars *vars(void)
{
	static t_vars init;

	return (&init);
}

void	check_arguments(char **argv)
{
	vars()->n_philo = ft_atoi(argv[1]);
	vars()->ttdie = ft_atoi(argv[2]);
	vars()->tteat = ft_atoi(argv[3]);
	vars()->ttsleep = ft_atoi(argv[4]);
	if (vars()->n_philo < 1 || vars()->ttdie < 1 || vars()->tteat < 1 || vars()->ttsleep < 1)
		printf("INVALID INPUT\nAll values must be positives");
	
}

int	main(int argc, char *argv[])
{
	t_philo philo[200];
	if (argc != 5)
		return (printf("4 arguments required.\n ./philo x x x x\n"));
	check_arguments(argv);
	set_table(philo);	
}