// TEST(ItemTest, ToolItem) {
//     const std::string MODID = "custom_namespace";
//     Registry<Item> mod(MODID);

//     auto list_of_blocks = std::multimap<int, std::string>{};
//     list_of_blocks.insert(std::make_pair(5, "grass"));
//     list_of_blocks.insert(std::make_pair(5, "dirt"));
//     list_of_blocks.insert(std::make_pair(10, "obsidian"));
//     list_of_blocks.insert(std::make_pair(5, "sand"));
//     list_of_blocks.insert(std::make_pair(4, "log"));

//     mod.subscribe("basic_tool", new ToolItem(ItemProperty::Property(), 100,
//     100,
//                                              100, list_of_blocks));

//     bool basic = compareFiles("../../test/files/basic_tool.json",
//                               "./BP/items/basic_tool.json");

//     EXPECT_EQ(true, basic) << "ToolItem is not working as expected";
// }