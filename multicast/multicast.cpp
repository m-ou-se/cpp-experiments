#include <iostream>

template<typename...> struct static_multicast_;

template<typename Head, typename... Tail>
struct static_multicast_<Head, Tail...> {
	template<typename T> static Head cast(T x) {
		return static_cast<Head>(static_multicast_<Tail...>::cast(x));
	}
};

template<typename Head>
struct static_multicast_<Head> {
	template<typename T> static Head cast(T x) {
		return static_cast<Head>(x);
	}
};

template<typename Head, typename... Tail, typename T>
Head static_multicast(T x) {
	return static_multicast_<Head, Tail...>::cast(x);
}

struct X { X(std::string) {} };
struct Y { Y(X) {} };
struct Z { Z(Y) {} };

int main() {
	Z z = static_multicast<Z, Y, X>("test");
}
