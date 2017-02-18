#include <iostream>

class Foo {
	int secret = 123;
	int secret2 = 456;
};

#define make_getter(C, MT, M) \
	template<MT C::*mem> \
	class getter_helper_##M { \
		friend MT & get_##M(C & f) { return f.*mem; } \
	}; \
	template class getter_helper_##M<&C::M>; \
	MT & get_##M(C & f);

make_getter(Foo, int, secret)
make_getter(Foo, int, secret2)

int main() {
	Foo f;
	std::cout << get_secret(f) << std::endl;
	std::cout << get_secret2(f) << std::endl;
}
