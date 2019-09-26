// Copyright Amstad Digital 2019

#pragma once

#include "CoreMinimal.h"





class SCULPTDROID_API SculptUtils
{
public:
	SculptUtils();
	~SculptUtils();


	UPROPERTY()
		float Scale = 100.0f;

	UPROPERTY()
		int32 TagFlag = 1;

	UPROPERTY()
		int32 SculptFlag = 1;

	UPROPERTY()
		int32 StateFlag = 1;

	UPROPERTY()
		uint32 TriIndex = 4294967295;


	static int32 NextHighestPowerOfTwo(int32 Value);



	template<typename T>
	static void TidyArray(TArray<T> TheArray)
	{
		TheArray.Sort(SortFunction());
		int32 Len = TheArray.Num();
		int32 i = 0;
		int32 j = 0;

		for (i = 1; i < len; i++)
		{
			if (TheArray[j] != TheArray[i])
			{
				TheArray[j++] = TheArray[i];
			}
		}

		if (i > 1)
		{
			TheArray.AddDefaulted(j + 1);
		}
	}

	template<typename T>
	static bool IsPowerOf2(const T& Value)
	{
		return Value != 0 && (Value & (Value - 1)) == 0;
	}

	
private:

	template<typename T>
	static bool SortFunction(T A, T B)
	{
		return A - B;
	}
	
};
