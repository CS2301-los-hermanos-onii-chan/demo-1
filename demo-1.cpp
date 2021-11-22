#include <iostream>
#include <vector>

int magic()
{
	int m = 0;

	for(size_t i = 0; i < sizeof(m)*8; i+=2)
	{
		m |= (1 << i);
	}

	return m;
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

std::vector<bool> read_and_append()
{
	std::vector<bool> v = read();

	for(size_t i = 0; i < sizeof(int)*8-1; i++)
		v.push_back(0);

	return v;
}

int vector2remainder(size_t start, const std::vector<bool>& v)
{
	int remainder = 0;

	for(size_t i = start; i < v.size(); i++)
	{
		remainder |=  (1 << (v.size()-1-i)) & v[i];
	}

	return remainder;
}

bool can_divide(size_t start, const std::vector<bool>& v)
{
	return v.size()-start > sizeof(int)*8-1;
}

size_t divide(size_t start, std::vector<bool>& v, int divisor)
{
	for(size_t i = 0; i < sizeof(int)*8; i++)
	{
		bool d_digit = divisor & (1 << (sizeof(int)*8-1-i));
		v.at(start+i) = v.at(start+i) != d_digit;
	}

	while(v.at(start) == false)
	{
		start++;
	}

	return start;
}

int crc_remainder()
{
	int divisor = magic();
	size_t start = 0;
	std::vector<bool> v = read_and_append();

	while(can_divide(start, v))
	{
		start = divide(start, v, divisor);
	}

	return vector2remainder(start, v);
}

int main()
{
	std::cout << crc_remainder() << '\n';
}
