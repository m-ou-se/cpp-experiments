#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

int main() {
	std::vector<int> v{5, 2, 10, 30, 6, 21};
	std::vector<std::thread> t;
	for (int x : v) t.emplace_back([x]{
		std::this_thread::sleep_for(std::chrono::milliseconds(x*10));
		std::cout << x << std::endl;
	});
	for (auto & i : t) i.join();
}
