/////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author Kuba Sejdak
/// @copyright BSD 2-Clause License
///
/// Copyright (c) 2020-2020, Kuba Sejdak <kuba.sejdak@gmail.com>
/// All rights reserved.
///
/// Redistribution and use in source and binary forms, with or without
/// modification, are permitted provided that the following conditions are met:
///
/// 1. Redistributions of source code must retain the above copyright notice, this
///    list of conditions and the following disclaimer.
///
/// 2. Redistributions in binary form must reproduce the above copyright notice,
///    this list of conditions and the following disclaimer in the documentation
///    and/or other materials provided with the distribution.
///
/// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
/// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
/// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
/// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
/// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
/// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
/// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
/// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
/// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
/// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
///
/////////////////////////////////////////////////////////////////////////////////////

#include <osal/sleep.h>
#include <osal/sleep.hpp>
#include <osal/timestamp.h>
#include <osal/timestamp.hpp>

#include <catch2/catch.hpp>

TEST_CASE("Check C timestamp values after multiple delays in ms", "[c][unit][timestamp]")
{
    std::uint64_t delayMs{};

    SECTION("Delay 500ms")
    {
        constexpr std::uint64_t cDelayMs = 500;
        delayMs = cDelayMs;
    }

    SECTION("Delay 1ms")
    {
        constexpr std::uint64_t cDelayMs = 1;
        delayMs = cDelayMs;
    }

    SECTION("Delay 0ms")
    {
        constexpr std::uint64_t cDelayMs = 0;
        delayMs = cDelayMs;
    }

    auto now1 = osalTimestampMs();
    osalSleepMs(delayMs);
    auto now2 = osalTimestampMs();
    const auto cDelay2Ms = 2 * delayMs;
    osalSleepMs(cDelay2Ms);
    auto now3 = osalTimestampMs();

    constexpr std::uint64_t cMarginMs = 50;
    REQUIRE(now2 >= now1);
    REQUIRE((now2 - now1) >= delayMs);
    REQUIRE((now2 - now1) <= (delayMs + cMarginMs));
    REQUIRE(now3 >= now2);
    REQUIRE(now3 >= now1);
    REQUIRE((now3 - now2) >= cDelay2Ms);
    REQUIRE((now3 - now2) <= (cDelay2Ms + cMarginMs));
    REQUIRE((now3 - now1) >= (cDelay2Ms + delayMs));
    REQUIRE((now3 - now1) <= (cDelay2Ms + delayMs + 2 * cMarginMs));
}

TEST_CASE("Check C timestamp values after multiple delays in us", "[c][unit][timestamp]")
{
    std::uint64_t delayMs{};

    SECTION("Delay 500ms")
    {
        constexpr std::uint64_t cDelayMs = 500;
        delayMs = cDelayMs;
    }

    SECTION("Delay 1ms")
    {
        constexpr std::uint64_t cDelayMs = 1;
        delayMs = cDelayMs;
    }

    SECTION("Delay 0ms")
    {
        constexpr std::uint64_t cDelayMs = 0;
        delayMs = cDelayMs;
    }

    auto now1 = osalTimestampUs();
    osalSleepMs(delayMs);
    auto now2 = osalTimestampUs();
    const auto cDelay2Ms = 2 * delayMs;
    osalSleepMs(cDelay2Ms);
    auto now3 = osalTimestampUs();

    const std::uint64_t cMarginMs = 50;
    REQUIRE(now2 >= now1);
    REQUIRE((now2 - now1) >= osalMsToUs(delayMs));
    REQUIRE((now2 - now1) <= osalMsToUs(delayMs + cMarginMs));
    REQUIRE(now3 >= now2);
    REQUIRE(now3 >= now1);
    REQUIRE((now3 - now2) >= osalMsToUs(cDelay2Ms));
    REQUIRE((now3 - now2) <= osalMsToUs(cDelay2Ms + cMarginMs));
    REQUIRE((now3 - now1) >= osalMsToUs(cDelay2Ms + delayMs));
    REQUIRE((now3 - now1) <= osalMsToUs(cDelay2Ms + delayMs + 2 * cMarginMs));
}

TEST_CASE("Check C timestamp values after multiple delays in ns", "[c][unit][timestamp]")
{
    std::uint64_t delayMs{};

    SECTION("Delay 500ms")
    {
        constexpr std::uint64_t cDelayMs = 500;
        delayMs = cDelayMs;
    }

    SECTION("Delay 1ms")
    {
        constexpr std::uint64_t cDelayMs = 1;
        delayMs = cDelayMs;
    }

    SECTION("Delay 0ms")
    {
        constexpr std::uint64_t cDelayMs = 0;
        delayMs = cDelayMs;
    }

    auto now1 = osalTimestampNs();
    osalSleepMs(delayMs);
    auto now2 = osalTimestampNs();
    const auto cDelay2Ms = 2 * delayMs;
    osalSleepMs(cDelay2Ms);
    auto now3 = osalTimestampNs();

    const std::uint64_t cMarginMs = 50;
    REQUIRE(now2 >= now1);
    REQUIRE((now2 - now1) >= osalMsToNs(delayMs));
    REQUIRE((now2 - now1) <= osalMsToNs(delayMs + cMarginMs));
    REQUIRE(now3 >= now2);
    REQUIRE(now3 >= now1);
    REQUIRE((now3 - now2) >= osalMsToNs(cDelay2Ms));
    REQUIRE((now3 - now2) <= osalMsToNs(cDelay2Ms + cMarginMs));
    REQUIRE((now3 - now1) >= osalMsToNs(cDelay2Ms + delayMs));
    REQUIRE((now3 - now1) <= osalMsToNs(cDelay2Ms + delayMs + 2 * cMarginMs));
}

TEST_CASE("Check C++ timestamp values after multiple delays", "[cpp][unit][timestamp]")
{
    std::chrono::milliseconds delay{};

    SECTION("Delay 1ms")
    {
        constexpr auto cDelay = 1ms;
        delay = cDelay;
    }

    SECTION("Delay 500ms")
    {
        constexpr auto cDelay = 500ms;
        delay = cDelay;
    }

    SECTION("Delay 0ms")
    {
        constexpr auto cDelay = 0ms;
        delay = cDelay;
    }

    SECTION("Delay 1s")
    {
        constexpr auto cDelay = 1s;
        delay = cDelay;
    }

    auto now1 = osal::timestamp();
    osal::sleep(delay);
    auto now2 = osal::timestamp();
    const auto cDelay2 = 2 * delay;
    osal::sleep(cDelay2);
    auto now3 = osal::timestamp();

    constexpr auto cMargin = 50ms;
    REQUIRE(now2 >= now1);
    REQUIRE((now2 - now1) >= delay);
    REQUIRE((now2 - now1) <= (delay + cMargin));
    REQUIRE(now3 >= now2);
    REQUIRE(now3 >= now1);
    REQUIRE((now3 - now2) >= cDelay2);
    REQUIRE((now3 - now2) <= (cDelay2 + cMargin));
    REQUIRE((now3 - now1) >= (cDelay2 + delay));
    REQUIRE((now3 - now1) <= (cDelay2 + delay + 2 * cMargin));
}
