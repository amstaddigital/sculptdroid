// Copyright Amstad Digital 2019


#include "SculptUtils.h"

SculptUtils::SculptUtils()
{
}

SculptUtils::~SculptUtils()
{
}

int32 SculptUtils::NextHighestPowerOfTwo(int32 Value)
{
	Value--;
	// Not super familiar with bit shifting so I guess this works?
	for (int32 i = 0; i < 32; i <<= 1)
	{
		Value = Value | Value >> i;
	}
	return Value + 1;
}
