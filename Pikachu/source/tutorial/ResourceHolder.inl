#include "ResourceHolder.hpp"

template<typename Resource, typename ID>
inline bool ResourceHolder<Resource, ID>::load(const ID& name, const std::string& path)
{
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(path))
		std::cout << "TextureHolder::load - Failed to load ";

	auto [ptr, ok] = resourceMap.try_emplace(name, std::move(resource));
	if (!ok)
		std::cout << "Error try_emplace";

	return ok;
}


template<typename Resource, typename ID>
inline std::optional<std::reference_wrapper<const Resource>> ResourceHolder<Resource, ID>::get(const ID& name) const
{
	if (auto&& found = resourceMap.find(name); found != resourceMap.end())
		return *found->second;
	
	return std::nullopt;
}