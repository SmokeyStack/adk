#pragma once

#include <variant>

#include "component.h"
#include "utility/shared_construct.h"

namespace adk {
	class ComponentBlockPlacementFilterCondition {
	public:
		ComponentBlockPlacementFilterCondition() {}
		~ComponentBlockPlacementFilterCondition() {}
		nlohmann::json::object_t Generate();
		ComponentBlockPlacementFilterCondition& AddAllowedFaces(BlockFaces face);
		ComponentBlockPlacementFilterCondition& AddBlockFilter(std::string block);
		ComponentBlockPlacementFilterCondition& AddBlockFilter(BlockDescriptor block);
	private:
		std::vector<BlockFaces> allowed_faces_;
		std::vector<std::variant<std::string, BlockDescriptor>> block_filter_;
	};
	
	class ComponentBlockPlacementFilter : public Component {
	public:
		ComponentBlockPlacementFilter() {}
		~ComponentBlockPlacementFilter() {}
		nlohmann::json::object_t Generate() override;
		std::string GetType() override;
		ComponentBlockPlacementFilter& AddCondition(ComponentBlockPlacementFilterCondition condition);
	private:
		std::vector<ComponentBlockPlacementFilterCondition> value_;
	};
} // namespace adk