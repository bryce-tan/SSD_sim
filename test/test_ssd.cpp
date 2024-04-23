#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"
#include "ssd.h"

TEST_CASE("SSD Write and Read Operations", "[SSD]") {
    SSD mySSD(10, 16);  // 假设我们有10个块，每个块16页

    // 测试写入和读取
    std::string data = "test data";
    mySSD.write(1, data);  // 写入数据到LBA 1
    REQUIRE(mySSD.read(1) == data);  // 读取LBA 1并验证数据

    // 测试写入不同的数据到相同的LBA，观察映射更新
    std::string newData = "new data";
    mySSD.write(1, newData);
    REQUIRE(mySSD.read(1) == newData);  // 确保新数据被读取

    // 测试擦除
    mySSD.format();  // 格式化SSD
    REQUIRE(mySSD.read(1) == "");  // 确认数据被擦除
}
