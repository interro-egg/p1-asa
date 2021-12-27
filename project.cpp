#include <iostream>
#include <string>
#include <vector>

typedef struct item {
	long long value;
	long long prev; //prev is the index of the previous item on the previous pile
} item;

// chama com fun(piles, piles.size() - 1, inf OU primeiro da ultima pile)
long long fun(std::vector<std::vector<item>> piles, long long pile_i, std::vector<long long> so_far)
{
	long long sum = 0;
	// if (pile_i == 0) {
	// 	std::cout << "<(leaf), ";
	// 	for (long long i = 0; i < so_far.size(); i++) {
	// 		std::cout << so_far[i] << ", ";
	// 	}
	// 	std::cout << ">\n";
	// 	return piles[pile_i].size() - ;
	// }
	for (long long i = 0; i < piles[pile_i].size(); i++) {
		if (so_far.size() != 0 && piles[pile_i][i].value > so_far[0])
			continue;
		if (pile_i == 0) {
			return piles[0].size() - i;
		}
		std::vector<long long> new_so_far = {piles[pile_i][i].value};
		for (long long j = 0; j < so_far.size(); j++) {
			new_so_far.push_back(so_far[j]);
		}
		sum += fun(piles, pile_i - 1, new_so_far);
	}
	return sum;
}

std::string problem1()
{
	std::vector<std::vector<item>> piles;
	char c;
	int number;
	while (std::cin >> number) {
		bool placed = false;
		for (int i = 0; i < piles.size(); i++) {
			if (piles[i].back().value >= number) {
				long long prev = i > 0 ? piles[i - 1].size() - 1 : -1;
				piles[i].push_back({number, prev});
				placed = true;
				break;
			}
		}
		if (!placed) {
			long long prev = piles.size() > 0 ? piles.back().size() - 1 : -1;
			piles.push_back({{number, prev}});
		}
	}
	std::cout << piles.size() << std::endl;
	std::cout << fun(piles, piles.size() - 1, {} /*piles.back()[0].value*/) << std::endl;
	return "what";
}

std::string problem2()
{
	std::string s = "Hello World!";
	return s;
}

int main()
{
	int problem;
	std::cin >> problem;
	switch (problem) {
	case 1:
		std::cout << problem1() << std::endl;
		break;
	case 2:
		std::cout << problem2() << std::endl;
		break;
	default:
		std::cout << "Invalid problem number" << std::endl;
		break;
	}
}
