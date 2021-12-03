#include <iostream>
#include <vector>

#define DIV_SIZE 8

// El valor que será añadido a los datos
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

// Al final de los datos se agrega un valor.
std::vector<bool> read_and_append(int remainder)
{
	std::vector<bool> v = read();

	for(size_t i = 0; i < DIV_SIZE-1; i++)
		v.push_back(remainder & (1 << (DIV_SIZE-1-1-i)));

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

// El input puede ser dividido hasta que ya no haya ningún 0 en los datos originales.
bool can_divide(size_t start, const std::vector<bool>& v)
{
	return v.size()-start > DIV_SIZE-1;
}

// v es dividido y shifteado hasta el primer 1.
size_t divide(size_t start, std::vector<bool>& v, const std::vector<bool>& divisor)
{
	for(size_t i = 0; i < DIV_SIZE; i++)
	{
		v.at(start+i) = v.at(start+i) != divisor.at(i);
	}

	while(start < v.size() && v.at(start) == false)
	{
		start++;
	}

	return start;
}

/// Divide la secuencia de bit v por un número y obtiene el residuo.
int crc_remainder(int remainder = 0)
{
	size_t start = 0;
	std::vector<bool> divisor = magic();
	std::vector<bool> v = read_and_append(remainder);

	while(can_divide(start, v))
	{
		start = divide(start, v, divisor);
	}

	return vector2remainder(v);
}

int main(int argc, char *argv[])
{
	// Si el residuo es diferente a 0, entonces los datos no son los mismos.
	if(argc == 2)
		exit(crc_remainder(atoi(argv[1])) == 0 ? EXIT_SUCCESS : EXIT_FAILURE);

	std::cout << crc_remainder() << '\n';
}
