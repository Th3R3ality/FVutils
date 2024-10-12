#include "Color.h"

Color Color::hex2rgba(const char* hex)
{
	Color res;

	size_t len = strlen(hex);

	if (len < 8)
		res.a = 1;

	size_t at = 0;

	if (hex[0] == '#')
		at = 1;

	constexpr auto char2hex = [](char c) -> int {
		int res = 0;

		if (c >= '0' && c <= '9')
			return (res = c - '0');

		if (c >= 'a' && c <= 'f')
			c = c - ('a' - 'A');

		res = (c - 'A') + 10;

		return res;
		};

	constexpr auto hex2f = [](const char* hex) -> float {
		float out = 0;

		out = (out * 0x10) + char2hex(hex[0]);
		out = (out * 0x10) + char2hex(hex[1]);

		return out / static_cast<float>(0xff);
		};

	res.r = hex2f(hex + at); at += 2;
	res.g = hex2f(hex + at); at += 2;
	res.b = hex2f(hex + at); at += 2;
	if (at < len)
		res.a = hex2f(hex + at);

	return res;
}
