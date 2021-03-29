#pragma once

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
	ResourceHolder();
	//template<typename Parameter>
	bool load(const ID&, const std::string&);//,const Parameter&);
	std::optional<std::reference_wrapper<const Resource>> get(const ID&) const;
	~ResourceHolder();
private:
	std::map<ID, std::unique_ptr<Resource>> resourceMap;
};

#include "ResourceHolder.inl" //implementation

