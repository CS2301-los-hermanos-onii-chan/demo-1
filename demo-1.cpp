#include <iostream>
#include <vector>

int magic()
{
	int m = 0;

	for(size_t i = 0; i < sizeof(m); i+=2)
	{
		m |= (1 << i);
	}

	return m;
}

int crc_remainder()
{
	int divisor = magic();

	return 0;
}

std::vector<bool> read()
{
	int c;
	std::vector<bool> v;

	while((c = getchar()) != -1)
	{
		for(size_t i = 0; i < 8; i++)
		{
			v.push_back(c & (1 << (7 - i)));
		}
	}

	return v;
}

int main()
{

	std::cout << "Hello world\n";
}
