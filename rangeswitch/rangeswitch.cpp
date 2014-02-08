#include <iostream>
#include <utility>

template<typename Value>
void range_switch_(bool, Value const &) {}

template<typename Value, typename F, typename... Rest>
void range_switch_(bool fell_through, Value const & value, Value const & l, Value const & h, F && f, Rest &&... rest) {
	if (fell_through || (value >= l && value < h)) {
		fell_through = f();
	}
	range_switch_(fell_through, value, std::forward<Rest>(rest)...);
}

template<typename... T>
void range_switch(T &&... x) {
	range_switch_(false, std::forward<T>(x)...);
}

#define range_switch(value) range_switch(value range_switch_body
#define range_switch_body(body) range_switch_add_end(range_switch_case body));
#define range_switch_case(begin, end) ,begin, end, range_switch_case_body
#define range_switch_case_body(...) [&]()->bool{do{__VA_ARGS__ return true;}while(false);return false;} range_switch_case
#define range_switch_add_end(...) range_switch_add_end_2(__VA_ARGS__)
#define range_switch_add_end_2(...) __VA_ARGS__##_end
#define range_switch_case_end

int main() {
	range_switch(5)(
		( 4,  9)( std::cout << "hello" << std::endl; )
		(14, 20)( std::cout << "world" << std::endl; break; )
		(30, 40)( std::cout << "asdf!" << std::endl; break; )
	)
}

// Prints:
//   hello
//   world
