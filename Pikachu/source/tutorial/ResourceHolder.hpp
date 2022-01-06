#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <cassert>
#include <optional>
#include <exception>
#include <string>
#include <string_view>

template<typename Resource, typename ID>
class ResourceHolder
{
public:
	using refResource = std::reference_wrapper<const Resource>;
public:
	ResourceHolder() = default;
	~ResourceHolder() = default;
public:
	bool load(const ID& name, const std::string& path);
	std::optional<refResource> get(const ID& name) const;
private:
	std::map<ID, std::unique_ptr<Resource>> m_resourceMap;
};

#include "ResourceHolder.inl" //implementation

