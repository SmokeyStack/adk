#pragma once

#include <variant>

#include "component.h"
#include "utility/shared_construct.h"

namespace adk {
	/**
	 * @brief The condition for the "minecraft:placement_filter" component
	 */
	class ComponentBlockPlacementFilterCondition {
	public:
		ComponentBlockPlacementFilterCondition() {}
		~ComponentBlockPlacementFilterCondition() {}
		nlohmann::json::object_t Generate();

		/**
		 * @brief Add a face to the allowed faces list
		 * @param face A BlockFaces enum
		 * @return ComponentBlockPlacementFilterCondition&
		 */
		ComponentBlockPlacementFilterCondition& AddAllowedFaces(BlockFaces face);

		/**
		 * @brief Add a block to the block filter list
		 * @param block The identifier of the block
		 * @return ComponentBlockPlacementFilterCondition&
		 */
		ComponentBlockPlacementFilterCondition& AddBlockFilter(std::string block);

		/**
		 * @brief Add a block to the block filter list
		 * @param block The block descriptor
		 * @return ComponentBlockPlacementFilterCondition&
		 */
		ComponentBlockPlacementFilterCondition& AddBlockFilter(BlockDescriptor block);
	private:
		std::vector<BlockFaces> allowed_faces_;
		std::vector<std::variant<std::string, BlockDescriptor>> block_filter_;
	};
	
	/**
	 * @brief "minecraft:placement_filter" component
	 * Sets rules for under what conditions the block can be placed or survive.
	 */
	class ComponentBlockPlacementFilter : public Component {
	public:
		ComponentBlockPlacementFilter() {}
		~ComponentBlockPlacementFilter() {}
		nlohmann::json::object_t Generate() override;
		std::string GetType() override;

		/**
		 * @brief The "condition" key for the "minecraft:placement_filter" component
		 * @param condition A ComponentBlockPlacementFilterCondition object
		 * @return ComponentBlockPlacementFilter&
		 */
		ComponentBlockPlacementFilter& AddCondition(ComponentBlockPlacementFilterCondition condition);
	private:
		std::vector<ComponentBlockPlacementFilterCondition> value_;
	};
} // namespace adk