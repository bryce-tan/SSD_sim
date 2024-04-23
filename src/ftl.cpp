#include "ftl.h"
#include <limits>
#include <algorithm>
#include <numeric> 

FTL::FTL(int numBlocks, int pagesPerBlock)
    : numBlocks(numBlocks), pagesPerBlock(pagesPerBlock), pageValid(numBlocks * pagesPerBlock, true) {
    blockEraseCounts.resize(numBlocks, 0);
    for (int i = 0; i < numBlocks * pagesPerBlock; ++i) {
        freePages.insert(i); // 初始化所有页面为可用
    }
}

int FTL::allocatePage(int lba) {
    int newPPA = findLeastWornBlock(); // 使用磨损均衡选择PPA
    if (newPPA == -1) {
        throw std::runtime_error("No free pages available in any block.");
    }
    updateMapping(lba, newPPA);
    return newPPA;
}

int FTL::findLeastWornBlock() {
    // 从具有最少擦除次数的块开始，找一个包含空闲页的块
    std::vector<int> eraseCountSortedIndices(numBlocks);
    std::iota(eraseCountSortedIndices.begin(), eraseCountSortedIndices.end(), 0);
    std::sort(eraseCountSortedIndices.begin(), eraseCountSortedIndices.end(), [this](int a, int b) {
        return blockEraseCounts[a] < blockEraseCounts[b];
    });

    for (int blockIndex : eraseCountSortedIndices) {
        int startPPA = blockIndex * pagesPerBlock;
        for (int i = 0; i < pagesPerBlock; i++) {
            int ppa = startPPA + i;
            if (freePages.find(ppa) != freePages.end()) {
                freePages.erase(ppa);
                blockEraseCounts[blockIndex]++;
                return ppa;
            }
        }
    }

    return -1; // 所有块都没有空闲页面
}

void FTL::updateMapping(int lba, int newPPA) {
    if (lbaToPpaMap.find(lba) != lbaToPpaMap.end()) {
        int oldPPA = lbaToPpaMap[lba];
        pageValid[oldPPA] = false; // 标记旧页面为无效
        freePages.insert(oldPPA); // 可以重新加入到空闲页面集合，等待垃圾回收
    }
    lbaToPpaMap[lba] = newPPA;
    pageValid[newPPA] = true; // 标记新页面为有效
}

int FTL::translateLBAtoPPA(int lba) {
    auto it = lbaToPpaMap.find(lba);
    if (it != lbaToPpaMap.end() && pageValid[it->second]) {
        return it->second;
    }
    return -1; // 如果没有有效映射，返回-1
}

