#include <iostream>
#include <vector>
#include <algorithm>

using floors = std::vector<std::pair<size_t, size_t>>;

size_t n, c, p, t;
floors fls;

bool check(size_t count) {
	if (count == 0) return true;
	size_t sum = 0;
	floors fs;
	for (size_t i = 0; i < fls.size(); i++) {
		sum += fls[i].first;
		fs.push_back(fls[i]);
		if (sum >= count) break;
	}
	//std::cout << "size: " << fs.size() << '\n';
	fs[fs.size() - 1].first -= sum - count;
	size_t time = 0;

	size_t index = fs.size() - 1;
	size_t r = c;

	while (true) {
		size_t a = fs[index].first;
		//std::cout << "index: " << index << '\n';
		//std::cout << "time: " << time << '\n';
		//std::cout << "r: " << r << '\n';
		//std::cout << "a: " << a << '\n';
		if (a < r) {
			//std::cout << "a < r\n";
			fs[index].first = 0;
			r -= a;
			if (index == 0) {
				time += 2 * p * fs[index].second;
				break;
			}
			time += 2 * p * (fs[index].second - fs[index - 1].second);
			index--;
		}
		else if (a == r) {
			//std::cout << "a == r\n";
			fs[index].first = 0;
			r = c;
			time += 2 * p * fs[index].second;
			if (index == 0) break;
			index--;
		}
		else {
			if (r != c) {
				//std::cout << "a > r\n";
				fs[index].first -= r;
				r = c;
				time += 2 * p * fs[index].second;
			}
			else {
				//std::cout << "a > c\n";
				fs[index].first = a % c;
				r = c;
				time += 2 * p * (a / c) * fs[index].second;
				if (a % c == 0) {
					if (index == 0) break;
					index--;
				}
			}
		}
	}

	return time <= t;
}

size_t binary_search(size_t left, size_t right) {
	while (right - left > 1) {
		size_t middle = (right + left) / 2;
		if (check(middle)) {
			left = middle;
		}
		else {
			right = middle;
		}
	}
	return left;
}

int main() {
	std::cin >> n >> c >> p >> t;
	size_t sum = 0;
	for (size_t i = 0; i < n; i++) {
		size_t a;
		std::cin >> a;
		sum += a;
		if (a > 0) {
			fls.push_back({ a, i + 1 });
		}
	}
	//std::cout << "check: " << check(11) << '\n';
	std::cout << binary_search(0, sum + 1);
	return 0;
}
