/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsymond <qsymond@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 13:42:17 by qsymond           #+#    #+#             */
/*   Updated: 2021/01/26 23:49:19 by qsymond          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_containers.hpp"
#include <deque>
int main()
{
	int (*func[])(void) = {
		&list_test,
		&map_test,
		&queue_test,
		&stack_test,
		&vector_test,
		&deque_test
	};
	std::cout << "PROJECT >> FT_CONTAINERS" << std::endl;
	std::cout << "Выберите тестируемый контейнер" << std::endl;
	std::cout << "1 - list" << std::endl;
	std::cout << "2 - map" << std::endl;
	std::cout << "3 - queue" << std::endl;
	std::cout << "4 - stack" << std::endl;
	std::cout << "5 - vector" << std::endl;
	std::cout << "6 - deque" << std::endl;
	int n;
	scanf("%d", &n);
	if (n < 1 || n > 6)
	{
		std::cout << "Error\n";
		return 0;
	}
	else
	{
		func[n - 1]();
	}
	return (0);
}