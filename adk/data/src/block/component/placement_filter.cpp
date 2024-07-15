#include "block/component/placement_filter.h"

#include "utility/logger.h"

namespace adk {
	nlohmann::json::object_t ComponentBlockPlacementFilterCondition::Generate() {
		nlohmann::json::object_t output;

		if (allowed_faces_.empty() && block_filter_.empty())
			throw std::runtime_error("ComponentPlacementFilterCondition - At least one condition must be provided.");

		auto& allowed_faces = output["allowed_faces"];
		auto& block_filter = output["block_filter"];

		if (!allowed_faces_.empty()) {
			nlohmann::json temp;
			for (const auto& face : allowed_faces_)
				allowed_faces.push_back(BlockFacesToString(face));
		}
		if (!block_filter_.empty()) {
			nlohmann::json temp;
			for (const auto& block : block_filter_) {
				if (std::holds_alternative<std::string>(block))
					block_filter.push_back(std::get<std::string>(block));
				else
					block_filter.push_back(std::get<BlockDescriptor>(block));
			}
		}

		return output;
	}
	ComponentBlockPlacementFilterCondition& ComponentBlockPlacementFilterCondition::AddAllowedFaces(BlockFaces face) {
		allowed_faces_.push_back(face);

		return *this;
	}
	ComponentBlockPlacementFilterCondition& ComponentBlockPlacementFilterCondition::AddBlockFilter(std::string block) {
		block_filter_.push_back(block);

		return *this;
	}
	ComponentBlockPlacementFilterCondition& ComponentBlockPlacementFilterCondition::AddBlockFilter(BlockDescriptor block) {
		block_filter_.push_back(block);

		return *this;
	}

	nlohmann::json::object_t ComponentBlockPlacementFilter::Generate() {
		nlohmann::json::object_t output = { {"minecraft:placement_filter", {{"conditions", nlohmann::json::array()}}} };
		for (auto& condition : value_)
			output["minecraft:placement_filter"]["conditions"].push_back(condition.Generate());

		return output;
	}
	std::string ComponentBlockPlacementFilter::GetType() { return "minecraft:placement_filter"; }
	ComponentBlockPlacementFilter& ComponentBlockPlacementFilter::AddCondition(ComponentBlockPlacementFilterCondition condition) {
		value_.push_back(condition);

		return *this;
	}
} // namespace adk