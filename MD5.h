#pragma once


#include <array>
#include <vector>
#include <cstdint>
#include <string>
#include <iostream>
#include <bitset>
#include <math.h>
#include <iomanip>

using namespace std;

namespace MD5_context {
	array<uint32_t, 4> result = {
		0x67452301,
		0xefcdab89,
		0x98badcfe,
		0x10325476
	};

	uint32_t AA = result[0], BB = result[1], CC = result[2], DD = result[3];

	vector<uint32_t> _32word_array = {};

	array<uint32_t, 64> md5_constants = { {
		0xd76aa478,0xe8c7b756,0x242070db,0xc1bdceee,0xf57c0faf,0x4787c62a,
		0xa8304613,0xfd469501,0x698098d8,0x8b44f7af,0xffff5bb1,0x895cd7be,
		0x6b901122,0xfd987193,0xa679438e,0x49b40821,0xf61e2562,0xc040b340,
		0x265e5a51,0xe9b6c7aa,0xd62f105d,0x02441453,0xd8a1e681,0xe7d3fbc8,
		0x21e1cde6,0xc33707d6,0xf4d50d87,0x455a14ed,0xa9e3e905,0xfcefa3f8,
		0x676f02d9,0x8d2a4c8a,0xfffa3942,0x8771f681,0x6d9d6122,0xfde5380c,
		0xa4beea44,0x4bdecfa9,0xf6bb4b60,0xbebfbc70,0x289b7ec6,0xeaa127fa,
		0xd4ef3085,0x04881d05,0xd9d4d039,0xe6db99e5,0x1fa27cf8,0xc4ac5665,
		0xf4292244,0x432aff97,0xab9423a7,0xfc93a039,0x655b59c3,0x8f0ccc92,
		0xffeff47d,0x85845dd1,0x6fa87e4f,0xfe2ce6e0,0xa3014314,0x4e0811a1,
		0xf7537e82,0xbd3af235,0x2ad7d2bb,0xeb86d391
	} };

	array<int, 64> md5_shifts_indexes = { {
		7,12,17,22,7,12,17,22,7,12,17,22,7,12,17,22,5,9,14,20,5,9,14,20,
		5,9,14,20,5,9,14,20,4,11,16,23,4,11,16,23,4,11,16,23,4,11,16,23,
		6,10,15,21,6,10,15,21,6,10,15,21,6,10,15,21
	} };

	array<int, 64> md5_array_indexes = { {
		0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
		1,6,11,0,5,10,15,4,9,14,3,8,13,2,7,12,
		5,7,11,14,1,4,7,10,13,0,3,6,9,12,15,2,
		0,7,14,5,12,3,10,1,8,15,6,13,4,11,2,9
	} };

	void LoadString(string str) {
		uint32_t _32word = 0;
		for (int i = 0; i < str.size(); i++) {
			if (i % 4 == 3) {
				_32word = (_32word << 8) | str[i];
				_32word_array.push_back(_32word);
				_32word = 0;
			}
			else _32word = (_32word << 8) | str[i];
		}
	}

	void Align() {
		_32word_array.push_back(0x80000000);
		while ((_32word_array.size() * 32) % 512 < 448) {
			_32word_array.push_back(0x0);
		}
	}

	void AddLineLength(uint64_t length) {
		_32word_array.push_back(length & 0xffffffff);
		_32word_array.push_back((length >> 32) & 0xffffffff);
	}

	uint32_t function_F(uint32_t x, uint32_t y, uint32_t z) {
		return x ^ (x & (y ^ z));
	}

	uint32_t function_G(uint32_t x, uint32_t y, uint32_t z) {
		return y ^ (x & (x ^ y));
	}

	uint32_t function_H(uint32_t x, uint32_t y, uint32_t z) {
		return  x ^ y ^ z;
	}

	uint32_t function_I(uint32_t x, uint32_t y, uint32_t z) {
		return y ^ (x | ~z);
	}

	array<decltype(function_F)*, 4> functions = { {
		function_F,
		function_G,
		function_H,
		function_I
	} };

	void MainLoop() {
		for (int block_i = 0; block_i < _32word_array.size() / 16; block_i++) {
			for (int phase = 0; phase < 4; phase++) {
				for (int round = 0; round < 16; round++) {
					AA = AA + (*functions[phase])(BB, CC, DD);
					AA = AA + _32word_array[block_i * 16 + md5_array_indexes[phase * 16 + round]];
					AA = AA + md5_constants[phase * 16 + round];
					for (int s = 0; s < md5_shifts_indexes[phase * 16 + round]; s++) {
						AA = (AA << 1) | (AA >> 31);
					}
					uint32_t tmp = AA;
					AA = DD;
					DD = CC;
					CC = BB;
					BB = tmp;
				}
			}

			result[0] += AA;
			result[1] += BB;
			result[2] += CC;
			result[3] += DD;
		}
	}
}



void MD5_starter(string line) {
	MD5_context::LoadString(line);
	MD5_context::Align();
	MD5_context::AddLineLength(line.length());
	MD5_context::MainLoop();

	cout << hex;
	cout << setfill('0') << setw(8) << MD5_context::result[0];
	cout << setfill('0') << setw(8) << MD5_context::result[1];
	cout << setfill('0') << setw(8) << MD5_context::result[2];
	cout << setfill('0') << setw(8) << MD5_context::result[3];
	cout << endl;
}
