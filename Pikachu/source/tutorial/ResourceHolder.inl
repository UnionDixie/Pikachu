#include "ResourceHolder.hpp"

template<typename Resource, typename ID>
inline ResourceHolder<Resource, ID>::ResourceHolder()
{
}

template<typename Resource, typename ID>
//template<typename Parameter>
inline bool ResourceHolder<Resource, ID>::load(const ID& name, const std::string& path)//, const Parameter& sec)
{
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(path)) {
		//assert(0 && "error load");
		/*throw std::runtime_error("TextureHolder::load - Failed to load "
			+ name);*/
	}
	auto&& ok = resourceMap.try_emplace(name, std::move(resource)).second;
	if (!ok) {//condt and action
		//throw std::logic_error("Error try_emplace");
	}
	return ok;
}

template<typename Resource, typename ID>
inline std::optional<std::reference_wrapper<const Resource>> ResourceHolder<Resource, ID>::get(const ID& name) const
{
	if (auto&& found = resourceMap.find(name); found != resourceMap.end()) {
		return { *found->second };
	}
	return std::nullopt;
	//return std::optional<std::reference_wrapper<const Resource>>();
}

template<typename Resource, typename ID>
inline ResourceHolder<Resource, ID>::~ResourceHolder()
{
}