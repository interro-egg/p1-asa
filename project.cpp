#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

typedef struct p1_item { // problem 1 item
	long long value;
	long long prev; // prev is the index of the previous item on the previous pile
	long long sum;
} p1_item;

// Returns the index (starting from the end) of the first item whose value is greater than or equal to newItem's value, or -1 if none is found
long long reverse_binary_search(std::vector<p1_item> &pile, std::size_t start, std::size_t end, long long newNum)
{
	if (pile[start].value < newNum) {
		return -1;
	}
	std::size_t mid = (start + end) / 2;
	while (start < end) {
		if (mid == start && end > start) {
			if (pile[end].value >= newNum) {
				return end;
			} else {
				return start;
			}
		}
		if (pile[mid].value >= newNum) {
			start = mid;
		} else {
			end = mid - 1;
		}
		mid = (start + end) / 2;
	}
	return start;
}

long long get_sum(std::vector<std::vector<p1_item>> &piles, std::size_t i, long long newNum)
{
	if (i == 0) {
		return (piles.empty() ? 0 : piles[0].back().sum) + 1;
	}
	// vv wouldn't work because end() > begin() and can't compare item directly
	// std::vector<long long>::iterator lo = std::lower_bound(piles[i].end(), piles[i].begin(), newItem);
	long long lo_i = reverse_binary_search(piles[i - 1], 0, piles[i - 1].size() - 1, newNum);
	long long gteSum = lo_i == -1 ? 0 : piles[i - 1][lo_i].sum;
	long long topSum = i + 1 <= piles.size() ? piles[i].back().sum : 0;
	return piles[i - 1].back().sum - gteSum + topSum;
}

std::string problem1()
{
	std::vector<std::vector<p1_item>> piles;
	std::vector<long long> lastItems;
	long long number;

	while (std::cin >> number) {
		std::vector<long long>::iterator up = std::upper_bound(lastItems.begin(), lastItems.end(), number);
		std::size_t i = up - lastItems.begin();
		if (lastItems.empty() || (up == lastItems.end() && lastItems.back() < number)) { // number is bigger than all lastItems
			// create new pile
			long long prev = i > 0 ? piles[i - 1].size() - 1 : -1;
			piles.push_back({{number, prev, get_sum(piles, i, number)}});
			lastItems.push_back(number);
		} else {
			// add to 'up' pile
			if (up == lastItems.end() || (i > 0 && lastItems[i - 1] == number)) // number is equal to lastItems.back() (previous if statement failed so this is the only option)
				i--;															// upper_bound returns the first element that is greater than number, so we need to check if previous pile's top is equal than number
			long long prev = i > 0 ? piles[i - 1].size() - 1 : -1;
			piles[i].push_back({number, prev, get_sum(piles, i, number)});
			lastItems[i] = number;
		}
	}
	// for (auto pile : piles) {
	// 	std::cout << "Pile: ";
	// 	for (auto p1_item : pile) {
	// 		std::cout << "[ " << p1_item.value << " (sum=" << p1_item.sum << ")] ";
	// 	}
	// 	std::cout << std::endl;
	// }

	return std::to_string(piles.size()) + ' ' + std::to_string(piles.back().back().sum) + '\n';
}

std::string problem2()
{
	std::vector<std::vector<long long>> matrix;
	std::vector<long long> x, y;
	std::string xStr, yStr;
	std::unordered_map<long long, bool> map;
	long long number, maxSize, max = 0;

	std::getline(std::cin, xStr);
	std::getline(std::cin, yStr);
	std::istringstream xSs(xStr);
	std::istringstream ySs(yStr);

	while (xSs >> number) {
		x.push_back(number);
		map[number] = true;
	}

	while (ySs >> number) {
		if (map[number]) {
			y.push_back(number);
		}
	}

	std::vector<long long> tracker(y.size(), 0); // O(n)

	for (std::size_t i = 0; i < x.size(); i++) {
		maxSize = 0;
		for (std::size_t j = 0; j < y.size(); j++) {
			if (x[i] > y[j]) {
				maxSize = std::max(tracker[j], maxSize);
			} else if (x[i] == y[j]) {
				tracker[j] = std::max(tracker[j], maxSize + 1);
				if (tracker[j] > max) {
					max = tracker[j];
				}
			}
		}
	}

	return std::to_string(max) + '\n';
}

int main()
{
	int problem;
	std::cin >> problem;
	getchar(); // skip newline after problem number
	switch (problem) {
	case 1:
		std::cout << problem1();
		break;
	case 2:
		std::cout << problem2();
		break;
	default:
		std::cout << "Invalid problem number" << std::endl;
		break;
	}
}
