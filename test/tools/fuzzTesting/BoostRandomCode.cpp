/*
	This file is part of cpp-ethereum.

	cpp-ethereum is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	cpp-ethereum is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with cpp-ethereum.  If not, see <http://www.gnu.org/licenses/>.
*/
/** @file BoostRandomCode.cpp
 * @date 2017
 */

#include <string>
#include <random>
#include <test/tools/fuzzTesting/BoostRandomCode.h>

namespace dev
{
namespace test
{

u256 BoostRandomCode::randomUniInt(u256 const& _minVal, u256 const& _maxVal)
{
	assert(_minVal <= _maxVal);
	refreshSeed();
	std::uniform_int_distribution<uint64_t> uint64Dist{0, std::numeric_limits<uint64_t>::max()};
	u256 value = _minVal + (u256)uint64Dist(gen) % (_maxVal - _minVal);
	return value;
}

void BoostRandomCode::refreshSeed()
{
	if (Options::get().randomTestSeed == 0)
	{
		auto now = std::chrono::steady_clock::now().time_since_epoch();
		auto timeSinceEpoch = std::chrono::duration_cast<std::chrono::nanoseconds>(now).count();
		gen.seed(static_cast<unsigned int>(timeSinceEpoch));
	}
	else
		gen.seed(Options::get().randomTestSeed);
}

uint8_t BoostRandomCode::weightedOpcode(std::vector<int>& _weights)
{
	refreshSeed();
	DescreteDistrib opCodeProbability = DescreteDistrib{_weights.begin(), _weights.end()};
	return opCodeProbability(gen);
}

}
}
