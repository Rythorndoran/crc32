#pragma once
#include <cstdint>

template <typename T, T val>
struct force_constexpr
{
	static constexpr T value = val;
	constexpr operator T() const noexcept {
		return value;
	}
};

// compile-time crc32 helper function
constexpr uint32_t crc32_impl(const char* data, size_t length) {
	uint32_t remainder = 0xffffffff;
	for (size_t i = 0; i < length; ++i) {
		remainder ^= data[i];
		for (int j = 0; j < 8; ++j) {
			if (remainder & 1) {
				remainder = (remainder >> 1) ^ 0xEDB88320UL;
			}
			else {
				remainder >>= 1;
			}
		}
	}
	return ~remainder;
}

// compile-time crc32
template <size_t N> constexpr uint32_t crc32(const char(&str)[N]) {
	return crc32_impl(str, N - 1);
}

// compile-time crc32 helper function
constexpr uint32_t crc32_impl(const wchar_t* data, size_t length) {
	uint32_t remainder = 0xffffffff;
	for (size_t i = 0; i < length; ++i) {

		//low 8bits
		remainder ^= static_cast<uint8_t>((data[i] & 0xFF));
		for (int j = 0; j < 8; ++j) {
			if (remainder & 1) {
				remainder = (remainder >> 1) ^ 0xEDB88320UL;
			}
			else {
				remainder >>= 1;
			}
		}

		//high 8bits
		remainder ^= static_cast<uint8_t>(((data[i] >> 8) & 0xFF));
		for (int j = 0; j < 8; ++j) {
			if (remainder & 1) {
				remainder = (remainder >> 1) ^ 0xEDB88320UL;
			}
			else {
				remainder >>= 1;
			}
		}

	}
	return ~remainder;
}

// compile-time crc32
template <size_t N>
constexpr std::uint32_t crc32(const wchar_t(&str)[N]) {
	return crc32_impl(str, N - 1);
}

#define _crc32(_x) force_constexpr<uint32_t,crc32(_x)>::value