// C++ curry function.
// foo(1,2,3) == curry(foo)(1)(2)(3)
//
// Made by Mara Bos <m-ou.se@m-ou.se>

#include <iostream>

template<typename function_t, typename... parameters>
class is_callable_with_parameters {
	template<typename F> static decltype(std::declval<F>()(std::declval<parameters>()...)) test(int) noexcept;
	template<typename> static void test(...);
public:
	static constexpr bool value = noexcept(test<function_t>(0));
	using return_type = decltype(test<function_t>(0));
};

template<typename function_t, typename captured_parameter_t>
struct function_with_captured_parameter {
	function_t function;
	captured_parameter_t captured_parameter;
	function_with_captured_parameter(function_t function, captured_parameter_t captured_parameter)
		: function(function), captured_parameter(captured_parameter) {}
	template<typename... parameters_t>
	decltype(function(captured_parameter, std::declval<parameters_t>()...))
	operator () (parameters_t... parameters) {
		return function(captured_parameter, parameters...);
	}
};

template<typename function_t>
class curried_function {
	function_t function;
	template<typename... parameters_t>
	decltype(function(std::declval<parameters_t>()...))
	call(parameters_t... parameters) {
		function(parameters...);
	}
public:
	curried_function(function_t function) : function(function) {}
	template<typename parameter_t>
	decltype(function(std::declval<parameter_t>()))
	operator () (parameter_t parameter) {
		return function(parameter);
	}
	template<typename parameter_t>
	typename std::enable_if<
		!is_callable_with_parameters<function_t, parameter_t>::value,
		curried_function<function_with_captured_parameter<function_t, parameter_t>>
	>::type
	operator () (parameter_t parameter) {
		return function_with_captured_parameter<function_t, parameter_t>{function, parameter};
	}
};

template<typename function_t>
curried_function<function_t> curry(function_t function) {
	return function;
}

int f(int a) { return a + 1; }
int g(int a, int b) { return a + b + 1; }
int h(int a, int b, int c) { return a + b + c + 1; }

int main() {
	std::cout << curry(f)(1)       << std::endl;
	std::cout << curry(g)(1)(2)    << std::endl;
	std::cout << curry(h)(1)(2)(3) << std::endl;
	auto h0 = curry(h);
	auto h1 = h0(1);
	auto h2 = h1(2);
	std::cout << h2(3) << std::endl;
}
