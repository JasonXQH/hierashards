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
/** @file Guards.h
 * @author Gav Wood <i@gavwood.com>
 * @date 2014
 */

#pragma once

#include <atomic>
#include <condition_variable>
#include <mutex>
#pragma warning(push)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include <boost/thread.hpp>
#pragma warning(pop)
#pragma GCC diagnostic pop

namespace dev
{
using Mutex = std::mutex;
using RecursiveMutex = std::recursive_mutex;
using SharedMutex = boost::shared_mutex;
//
/*
 * lock_guard 对象通常用于管理某个锁(Lock)对象
   mutex对象传入之后,会被当前线程锁住,look_guard被析构之后,所管理的mutex对象会自动解锁
 * */

using Guard = std::lock_guard<std::mutex>;
using UniqueGuard = std::unique_lock<std::mutex>;
using RecursiveGuard = std::lock_guard<std::recursive_mutex>;
using ReadGuard = boost::shared_lock<boost::shared_mutex>;
using UpgradableGuard = boost::upgrade_lock<boost::shared_mutex>;
using UpgradeGuard = boost::upgrade_to_unique_lock<boost::shared_mutex>;
using WriteGuard = boost::unique_lock<boost::shared_mutex>;

template <class GuardType, class MutexType>
struct GenericGuardBool : GuardType
{
    GenericGuardBool(MutexType& _m) : GuardType(_m) {}
    bool b = true;
};
template <class MutexType>
struct GenericUnguardBool
{
    GenericUnguardBool(MutexType& _m) : m(_m) { m.unlock(); }
    ~GenericUnguardBool() { m.lock(); }
    bool b = true;
    MutexType& m;
};

/** @brief Simple block guard.
 * The expression/block following is guarded though the given mutex.
 * Usage:
 * @code
 * Mutex m;
 * unsigned d;
 * ...
 * ETH_(m) d = 1;
 * ...
 * ETH_(m) { for (auto d = 10; d > 0; --d) foo(d); d = 0; }
 * @endcode
 *
 * There are several variants of this basic mechanism for different Mutex types and Guards.
 *
 * There is also the UNGUARD variant which allows an unguarded expression/block to exist within a
 * guarded expression. eg:
 *
 * @code
 * Mutex m;
 * int d;
 * ...
 * ETH_GUARDED(m)
 * {
 *   for (auto d = 50; d > 25; --d)
 *     foo(d);
 *   ETH_UNGUARDED(m)
 *     bar();
 *   for (; d > 0; --d)
 *     foo(d);
 * }
 * @endcode
 */

#define DEV_GUARDED(MUTEX) \
    for (GenericGuardBool<Guard, Mutex> __eth_l(MUTEX); __eth_l.b; __eth_l.b = false)
#define DEV_READ_GUARDED(MUTEX) \
    for (GenericGuardBool<ReadGuard, SharedMutex> __eth_l(MUTEX); __eth_l.b; __eth_l.b = false)
#define DEV_WRITE_GUARDED(MUTEX) \
    for (GenericGuardBool<WriteGuard, SharedMutex> __eth_l(MUTEX); __eth_l.b; __eth_l.b = false)
#define DEV_RECURSIVE_GUARDED(MUTEX)                                                 \
    for (GenericGuardBool<RecursiveGuard, RecursiveMutex> __eth_l(MUTEX); __eth_l.b; \
         __eth_l.b = false)
}  // namespace dev
