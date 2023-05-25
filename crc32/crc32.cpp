// crc32.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "crc32.hpp"
int main()
{
	printf("0x%x\n", _crc32("Hello World!"));
	return 0;
}

