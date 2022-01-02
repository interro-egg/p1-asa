#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

typedef struct item {
	long long value;
	long long prev; // prev is the index of the previous item on the previous pile
	long long sum;
} item;

// Returns the index (starting from the end) of the first item whose value is greater than or equal to newItem's value, or -1 if none is found
std::size_t reverse_binary_search(std::vector<item> pile, std::size_t start, std::size_t end, long long newNum)
{
	if (pile[start].value < newNum) {
		return -1;
	}
	std::size_t mid = (start + end) / 2;
	while (start < end && mid > start) {
		if (pile[mid].value >= newNum) {
			start = mid;
		} else {
			end = mid - 1;
		}
		mid = (start + end) / 2;
	}
	return start;
}

long long get_sum(std::vector<std::vector<item>> piles, std::size_t i, long long newNum)
{
	if (i == 0) {
		return (piles.empty() ? 0 : piles[0].back().sum) + 1;
	}
	// vv wouldn't work because end() > begin() and can't compare item directly
	//std::vector<long long>::iterator lo = std::lower_bound(piles[i].end(), piles[i].begin(), newItem);
	std::size_t lo_i = reverse_binary_search(piles[i - 1], 0, piles[i - 1].size() - 1, newNum);
	long long gteSum = lo_i == -1 ? 0 : piles[i - 1][lo_i].sum;
	long long topSum = i + 1 <= piles.size() ? piles[i].back().sum : 0;
	return piles[i - 1].back().sum - gteSum + topSum;
}

std::string problem1()
{
	std::vector<std::vector<item>> piles;
	std::vector<long long> lastItems;
	char c;
	long long number, sum;

	while (std::cin >> number) {
		std::vector<long long>::iterator up = std::upper_bound(lastItems.begin(), lastItems.end(), number);
		std::size_t i = up - lastItems.begin();
		if (lastItems.empty() || (up == lastItems.end() && lastItems.back() < number)) { //number is bigger than all lastItems
			// create new pile
			long long prev = i > 0 ? piles[i - 1].size() - 1 : -1;
			piles.push_back({{number, prev, get_sum(piles, i, number)}});
			lastItems.push_back(number);
		} else {
			// add to 'up' pile
			if (up == lastItems.end()) // number is equal to lastItems.back() (previous if statement failed so this is the only option)
				i--;
			long long prev = i > 0 ? piles[i - 1].size() - 1 : -1;
			piles[i].push_back({number, prev, get_sum(piles, i, number)});
			lastItems[i] = number;
		}
	}
	// for (auto pile : piles) {
	// 	std::cout << "Pile: ";
	// 	for (auto item : pile) {
	// 		std::cout << "[ " << item.value << " (sum=" << item.sum << ")] ";
	// 	}
	// 	std::cout << std::endl;
	// }

	return std::to_string(piles.size()) + ' ' + std::to_string(piles.back().back().sum) + '\n';
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
