#include "list.hpp"
#include "bidirectional_iterator.hpp"
#include "const_bidirectional_iterator.hpp"
#include "reverse_iterator.hpp"
#include "const_reverse_iterator.hpp"
#include <iostream>

void testConstructorDefault()
{
	std::string testName = "List.List default";
	ft::list<int> l1;
	ft::list<char> l2;
	ft::list<char*> l3;
	ft::list<char**> l4;
	ft::list< ft::list<char**> > l5;
	assert(l1.size() == 0);
	assert(l2.size() == 0);
	assert(l3.size() == 0);
	assert(l4.size() == 0);
	assert(l5.size() == 0);
	assert(l1.empty());
	assert(l2.empty());
	assert(l3.empty());
	assert(l4.empty());
	assert(l5.empty());
	assert(l1.max_size() > 0);
}

void testConstructorFill()
{
	std::string testName = "List.List fill";

	ft::list<int> l1(5);
	assert(l1.size() == 5);
	assert(l1.front() == int());
	assert(l1.back() == int());
	for (ft::list<int>::iterator it = l1.begin(); it != l1.end(); ++it)
		assert(*it == int());

	ft::list<char> l2(3);
	assert(l2.size() == 3);
	assert(l2.front() == char());
	assert(l2.back() == char());
	for (ft::list<char>::iterator it = l2.begin(); it != l2.end(); ++it)
		assert(*it == char());

	ft::list<float> l3(4, 42.42f);
	assert(l3.size() == 4);
	assert(l3.front() == 42.42f);
	assert(l3.back() == 42.42f);
	for (ft::list<float>::iterator it = l3.begin(); it != l3.end(); ++it)
		assert(*it == 42.42f);
}

void testConstructorRange()
{
	std::string testName = "List.List range";

	size_t i;
	int         arr1[5] = {1, 2, 3, 4, 5};
	std::string arr2[3] = {"bonjour", "je", "suis"};
	float       arr3[5] = {1.2, 2.3, 3.4, 4.5, 5.6};

	ft::list<int> l1(arr1, arr1 + 5);
	assert(l1.size() == 5);
	assert(l1.front() == 1);
	assert(l1.back() == 5);
	i = 0;
	for (ft::list<int>::iterator it = l1.begin(); it != l1.end(); ++it)
		assert(*it == arr1[i++]);

	ft::list<std::string> l2(arr2, arr2 + 3);
	assert(l2.size() == 3);
	assert(l2.front() == "bonjour");
	assert(l2.back() == "suis");
	i = 0;
	for (ft::list<std::string>::iterator it = l2.begin(); it != l2.end(); ++it)
		assert(*it == arr2[i++]);


	ft::list<float> l3(arr3, arr3 + 5);
	assert(l3.size() == 5);
	assert(l3.front() == 1.2f);
	assert(l3.back() == 5.6f);
	i = 0;
	for (ft::list<float>::iterator it = l3.begin(); it != l3.end(); ++it)
		assert(*it == arr3[i++]);

	ft::list<int> l4(arr1 + 1, arr1 + 4);
	assert(l4.size() == 3);
	assert(l4.front() == 2);
	assert(l4.back() == 4);
	i = 0;
	for (ft::list<int>::iterator it = l4.begin(); it != l4.end(); ++it)
		assert(*it == arr1[1 + i++]);
}

void testOperatorAssign()
{
	std::string testName = "List.operator=";

	size_t           i;
	int              arr1[5] = {1, 2, 3, 4, 5};
	float            arr3[5] = {1.2, 2.3, 3.4, 4.5, 5.6};
	ft::list<int>    l1_copied;
	ft::list<char>   l2_copied(3);
	ft::list<float>  l3_copied(4, 42.42f);
	ft::list<float>  l4_copied(arr3, arr3 + 5);
	ft::list<int>    l5_copied(arr1 + 1, arr1 + 4);

	ft::list<int>    l1;
	ft::list<char>   l2;
	ft::list<float>  l3;
	ft::list<float>  l4;
	ft::list<int>    l5;

	l1 = l1_copied;
	l2 = l2_copied;
	l3 = l3_copied;
	l4 = l4_copied;
	l5 = l5_copied;

	assert(l1.size() == 0);
	assert(l1.empty());

	assert(l2.size() == 3);
	assert(l2.front() == char());
	assert(l2.back() == char());
	for (ft::list<char>::iterator it = l2.begin(); it != l2.end(); ++it)
		assert(*it == char());

	assert(l3.size() == 4);
	assert(l3.front() == 42.42f);
	assert(l3.back() == 42.42f);
	for (ft::list<float>::iterator it = l3.begin(); it != l3.end(); ++it)
		assert(*it == 42.42f);

	assert(l4.size() == 5);
	assert(l4.front() == 1.2f);
	assert(l4.back() == 5.6f);
	i = 0;
	for (ft::list<float>::iterator it = l4.begin(); it != l4.end(); ++it)
		assert(*it == arr3[i++]);

	assert(l5.size() == 3);
	assert(l5.front() == 2);
	assert(l5.back() == 4);
	i = 0;
	for (ft::list<int>::iterator it = l5.begin(); it != l5.end(); ++it)
		assert(*it == arr1[1 + i++]);
}


void testConstructorCopy()
{
	std::string testName = "List.List copy";

	size_t           i;
	int              arr1[5] = {1, 2, 3, 4, 5};
	float            arr3[5] = {1.2, 2.3, 3.4, 4.5, 5.6};
	ft::list<int> l1_copied;
	ft::list<char>   l2_copied(3);
	ft::list<float>  l3_copied(4, 42.42f);
	ft::list<float>  l4_copied(arr3, arr3 + 5);
	ft::list<int>    l5_copied(arr1 + 1, arr1 + 4);

	ft::list<int>    l1(l1_copied);
	ft::list<char>   l2(l2_copied);
	ft::list<float>  l3(l3_copied);
	ft::list<float>  l4(l4_copied);
	ft::list<int>    l5(l5_copied);

	assert(l1.size() == 0);
	assert(l1.empty());

	assert(l2.size() == 3);
	assert(l2.front() == char());
	assert(l2.back() == char());
	for (ft::list<char>::iterator it = l2.begin(); it != l2.end(); ++it)
		assert(*it == char());

	assert(l3.size() == 4);
	assert(l3.front() == 42.42f);
	assert(l3.back() == 42.42f);
	for (ft::list<float>::iterator it = l3.begin(); it != l3.end(); ++it)
		assert(*it == 42.42f);

	assert(l4.size() == 5);
	assert(l4.front() == 1.2f);
	assert(l4.back() == 5.6f);
	i = 0;
	for (ft::list<float>::iterator it = l4.begin(); it != l4.end(); ++it)
		assert(*it == arr3[i++]);

	assert(l5.size() == 3);
	assert(l5.front() == 2);
	assert(l5.back() == 4);
	i = 0;
	for (ft::list<int>::iterator it = l5.begin(); it != l5.end(); ++it)
		assert(*it == arr1[1 + i++]);
}

int main()
{
	std::string tests[] = {"List.List default", "List.List fill", "List.List range", "List.operator=", "List.List copy"};
	void (*ptr[])() =
	{
			&testConstructorFill,
			&testConstructorRange,
			&testConstructorDefault,
			&testOperatorAssign,
			&testConstructorCopy
	};

	for (size_t i = 0; i < 5; ++i)
	{
		ptr[i];
		std::cout << tests[i] << " is ok!" << std::endl;
	}
	return (0);
}