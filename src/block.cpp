#include "block.h"

Block::Block(int pagesPerBlock) {
    for (int i = 0; i < pagesPerBlock; ++i) {
        pages.push_back(std::make_unique<Page>());
    }
}

Block::~Block() {
    // 自动释放资源
}

bool Block::write(int pageNum, const std::string& data) {
    if (pageNum < pages.size()) {
        pages[pageNum]->data = data;
        return true;
    }
    return false;
}

std::string Block::read(int pageNum) const {
    if (pageNum < pages.size()) {
        return pages[pageNum]->data;
    }
    return "";
}

void Block::erase() {
    for (auto& page : pages) {
        page->data.clear();
    }
}
