#pragma once

#include "block.h"
#include "ftl.h"
#include <vector>
#include <string>

class SSD {
public:
    SSD(int numBlocks, int pagesPerBlock);  // 初始化SSD的块和页面
    ~SSD();

    void write(int lba, const std::string& data);  // 写数据到逻辑地址
    std::string read(int lba);                     // 从逻辑地址读数据
    void format();                                 // 格式化SSD

private:
    std::vector<Block> blocks;
    FTL ftl;
    int pagesPerBlock;
};
