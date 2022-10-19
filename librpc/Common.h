/**
 * @CopyRight:
 * FISCO-BCOS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * FISCO-BCOS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with FISCO-BCOS.  If not, see <http:www.gnu.org/licenses/>
 * (c) 2016-2018 fisco-dev contributors.
 *
 * @file Common.h
 * @author: caryliao
 * @date 2018-11-6
 */

#pragma once

#include <map>
#include <string>
#include <vector>
#include <libdevcore/FixedHash.h>
#define INVALIDNUMBER -1
#define RPC_LOG(LEVEL) LOG(LEVEL) << "[RPC]"

namespace dev
{
namespace rpc
{
    
extern std::vector<dev::h256> subcrosstxhash; // 记录所有待处理的跨片子交易hash
extern std::map<dev::h256, int> txhash2sourceshardid; // txhash - > sourceshardid
extern std::map<dev::h256, int> txhash2messageid; // txhash - > messageid
extern std::map<dev::h256, std::string> txhash2readwriteset; // txhash - > readwriteset
extern std::map<dev::h256, std::string> innertxhash2readwriteset; // txhash - > readwriteset

struct transaction_info
{
    long int type; // 交易类型, 0 为片内交易, 1 为跨片子交易
	long int source_shard_id;
	long int destin_shard_id;
	long unsigned message_id;
    long int readwritesetnum;
	dev::h256 sub_tx_hash;
	std::string cross_tx_hash;
	std::string readwrite_key; 
};

extern std::map<dev::h256, transaction_info> corsstxhash2transaction_info;

///< RPCExceptionCode
enum RPCExceptionType : int
{
    Success = 0,
    PermissionDenied = -40012,
    OverQPSLimit = -40011,
    IncompleteInitialization = -40010,
    InvalidRequest = -40009,
    InvalidSystemConfig = -40008,
    NoView = -40007,
    CallFrom = -40006,
    TransactionIndex = -40005,
    BlockNumberT = -40004,
    BlockHash = -40003,
    JsonParse = -40002,
    GroupID = -40001,
};
extern std::map<int, std::string> RPCMsg;
}  // namespace rpc
std::string compress(const std::string& _data);
std::string decompress(const std::string& _data);
std::string base64Encode(const std::string& _data);
std::string base64Decode(const std::string& _data);
}  // namespace dev
