// include/ftl.h
#pragma once

#include <unordered_map>
#include <vector>
#include <set>

class FTL {
public:
    FTL(int numBlocks, int pagesPerBlock);
    int allocatePage(int lba); // 分配新页面给LBA
    void updateMapping(int lba, int newPPA); //更新LBA到PPA的映射
    int translateLBAtoPPA(int lba); // 查PPA表
    void write(int lba, const std::string& data);

private:
    std::unordered_map<int, int> lbaToPpaMap; // 映射表：逻辑块地址到物理页地址
    std::vector<bool> pageValid;              // 页面有效性标记
    std::set<int> freePages;               // 可用页列表
    std::vector<int> blockEraseCounts;        // 每个块的擦除次数，用于磨损均衡
    int numBlocks;
    int pagesPerBlock;
    int findLeastWornBlock();                      // 找到一个可用的物理页
};
