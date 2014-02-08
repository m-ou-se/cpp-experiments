#include <array>
#include <iostream>
#include <map>
#include <string>

#define MAGIC_ENUM_ADD_END(...) MAGIC_ENUM_ADD_END2(__VA_ARGS__)
#define MAGIC_ENUM_ADD_END2(...) __VA_ARGS__ ## _END

#define MAGIC_ENUM(name, list) \
	enum name { MAGIC_ENUM_ADD_END(MAGIC_ENUM_1 list) name##_size }; \
	std::array<std::string, name##_size> name##_names {{ MAGIC_ENUM_ADD_END(MAGIC_ENUM_NAMES_1 list) }}; \
	std::map<std::string, name> name##_values { MAGIC_ENUM_ADD_END(MAGIC_ENUM_VALUES_1 list) };

#define MAGIC_ENUM_1(name) name, MAGIC_ENUM_2
#define MAGIC_ENUM_2(name) name, MAGIC_ENUM_1
#define MAGIC_ENUM_1_END
#define MAGIC_ENUM_2_END

#define MAGIC_ENUM_NAMES_1(name) #name, MAGIC_ENUM_NAMES_2
#define MAGIC_ENUM_NAMES_2(name) #name, MAGIC_ENUM_NAMES_1
#define MAGIC_ENUM_NAMES_1_END
#define MAGIC_ENUM_NAMES_2_END

#define MAGIC_ENUM_VALUES_1(name) {#name, name}, MAGIC_ENUM_VALUES_2
#define MAGIC_ENUM_VALUES_2(name) {#name, name}, MAGIC_ENUM_VALUES_1
#define MAGIC_ENUM_VALUES_1_END
#define MAGIC_ENUM_VALUES_2_END

// With the above definitions, this

MAGIC_ENUM(my_enum,
	(first)
	(second)
	(third)
	(fourth)
	(fifth)
)

// expands to:
/*

enum my_enum {
	first, second, third, fourth, fifth, my_enum_size
};

std::array<std::string, my_enum_size> my_enum_names {
	"first", "second", "third", "fourth", "fifth",
};

std::map<std::string, my_enum> my_enum_values {
	{"first", first}, {"second", second}, {"third", third},
	{"fourth", fourth}, {"fifth", fifth},
};

*/

int main() {
	my_enum x = my_enum_values["first"];
	if (x == first) std::cout << my_enum_names[x] << std::endl;
}
