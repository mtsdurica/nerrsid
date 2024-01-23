#pragma once

#include <random>

#define UINT_CHANGEABLE uint8_t // Changeable data type if needed to generate larger maps than 0-255

namespace Util
{
	constexpr int GAME_RESOLUTION_WIDTH = 1600;
	constexpr int GAME_RESOLUTION_HEIGHT = 720;// Max base room height
	constexpr int MAX_X = 40; // Max base room width
	constexpr int MAX_Y = (GAME_RESOLUTION_HEIGHT / 16);
	constexpr int PSEUDO_ROOM_SIZE = 4;  // Pseudo max room size

	inline UINT_CHANGEABLE RandomChangeableIntInRange(const UINT_CHANGEABLE minNum, const UINT_CHANGEABLE maxNum)
	{
		static std::random_device randomDevice;
		static std::mt19937 randomNumberGenerator(randomDevice());
		std::uniform_int_distribution<std::mt19937::result_type> uniformDistribution(minNum, maxNum);
		return static_cast<UINT_CHANGEABLE>(uniformDistribution(randomNumberGenerator));
	}

	inline int RandomIntInRange(const int minNum, const int maxNum)
	{
		static std::random_device randomDevice;
		static std::mt19937 randomNumberGenerator(randomDevice());
		std::uniform_int_distribution<std::mt19937::result_type> uniformDistribution(minNum, maxNum);
		return static_cast<int>(uniformDistribution(randomNumberGenerator));
	}
}