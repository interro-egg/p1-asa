#include <iostream>
#include <string>
#include <vector>

typedef struct item {
	long long value;
	long long prev; //prev is the index of the previous item on the previous pile
} item;

// call this with: fun(piles, piles.size() - 1, piles.back().front())
//! THIS IS WRONG!: it counts the leaves in the piles graph WITH NO REGARD for the
//! order of the actual input array
long long fun(std::vector<std::vector<item>> piles, long long pile_i, item caller)
{
	long long sum = 0;
	for (long long i = 0; i < piles[pile_i].size(); i++) {
		if (piles[pile_i][i].value > caller.value) {
			continue;
		}
		if (pile_i == 0) {
			return piles[0].size() - i;
		}
		sum += fun(piles, pile_i - 1, piles[pile_i][i]);
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
	std::cout << fun(piles, piles.size() - 1, piles.back().front()) << std::endl;
	return "what";
}

std::string problem2()
{
	return "Not implemented";
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
