#include <iostream>
#include <vector>

#define DIV_SIZE 8

std::vector<bool> magic()
{
	std::vector<bool> v;

	for(size_t i = 0; i < DIV_SIZE; i++)
	{
		v.push_back(!(i & 1));
	}

	return v;
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

int vector2remainder(const std::vector<bool>& v)
{
	int remainder = 0;

	for(size_t i = v.size()-1-(DIV_SIZE-1); i < v.size(); i++)
	{
		remainder |=  v[i] ? (1 << (v.size()-1-i)) : 0;
	}

	return remainder;
}

bool can_divide(size_t start, const std::vector<bool>& v)
{
	return v.size()-start > DIV_SIZE-1;
}

size_t divide(size_t start, std::vector<bool>& v, const std::vector<bool>& divisor)
{
	for(size_t i = 0; i < DIV_SIZE; i++)
	{
		v.at(start+i) = v.at(start+i) != divisor.at(i);
	}

	while(v.at(start) == false)
	{
		start++;
	}

	return start;
}

int crc_remainder()
{
	size_t start = 0;
	std::vector<bool> divisor = magic();
	std::vector<bool> v = read_and_append();

	while(can_divide(start, v))
	{
		start = divide(start, v, divisor);
	}

	return vector2remainder(v);
}

int main()
{
	std::cout << crc_remainder() << '\n';
}
