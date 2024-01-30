#pragma once
#include "config.h"
#include "ObjectCreator.h"
#include "CachePolicy.h"
#include "SizePolicy.h"
#include "ErrorPolicy.h"

#include <stdexcept>
#include <memory>

template <typename... Policies>
std::unique_ptr < ICreator > ErrorPolicyHandler(const config& conf) {
	if (conf.errorPolicy == "NoError") return std::make_unique< Creator<Policies..., NoErrorPolicy> >();
	else if (conf.errorPolicy == "RE") return std::make_unique< Creator<Policies..., ThrowREPolicy> >();
	else if (conf.errorPolicy == "Warning") return std::make_unique< Creator<Policies..., WarningPolicy> >();
	else throw std::runtime_error("Incorrect Error Policy");
}
template <typename... Policies>
std::unique_ptr < ICreator > CachePolicyHandler(const config& conf) {
	if (conf.cachePolicy == "LRU") return ErrorPolicyHandler<Policies...,LRUPolicy>(conf);
	else if (conf.cachePolicy == "FIFO") return ErrorPolicyHandler<Policies...,FIFOPolicy>(conf);
	else if (conf.cachePolicy == "None") return ErrorPolicyHandler<Policies...,NoCachePolicy>(conf);
	else throw std::runtime_error("Incorrect Cache Policy");
}
template <typename... Policies>
std::unique_ptr < ICreator > SizePolicyHandler(const config& conf) {
	if (conf.sizePolicy == "Fixed") return CachePolicyHandler<Policies...,FixedSizePolicy>(conf);
	else if (conf.sizePolicy == "One") return CachePolicyHandler<Policies...,OneElementPolicy>(conf);
	else if (conf.sizePolicy == "Dynamic") return CachePolicyHandler<Policies...,DynamicSizePolicy>(conf);
	else throw std::runtime_error("Incorrect Size Policy");
}

std::unique_ptr < ICreator > create(const config& conf) {
	return SizePolicyHandler<>(conf);
}
