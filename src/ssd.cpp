#include "ssd.h"

SSD::SSD(int numBlocks, int pagesPerBlock) : ftl(numBlocks, pagesPerBlock), pagesPerBlock(pagesPerBlock) {
    for (int i = 0; i < numBlocks; ++i) {
        blocks.push_back(Block(pagesPerBlock));
    }
}

SSD::~SSD() {
    // 资源自动释放
}

void SSD::write(int lba, const std::string& data) {
    int newPPA = ftl.allocatePage(lba);
    int blockIndex = newPPA / pagesPerBlock;
    int pageIndex = newPPA % pagesPerBlock;
    blocks[blockIndex].write(pageIndex, data);
}

std::string SSD::read(int lba) {
    int ppa = ftl.translateLBAtoPPA(lba);
    if (ppa == -1) return "";
    int blockIndex = ppa / pagesPerBlock;
    int pageIndex = ppa % pagesPerBlock;
    return blocks[blockIndex].read(pageIndex);
}

void SSD::format() {
    for (auto& block : blocks) {
        block.erase();
    }
    ftl = FTL(blocks.size(), pagesPerBlock);
}
