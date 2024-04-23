#pragma once

#include <vector>
#include <memory>
#include <string>

class Page {
public:
    Page() : data("") {} // 初始时页面为空
    std::string data;
};

class Block {
public:
    Block(int pagesPerBlock);
    ~Block();

    bool write(int pageNum, const std::string& data);  // 在特定页写入数据
    std::string read(int pageNum) const;               // 从特定页读取数据
    void erase();                                      // 擦除整个块

private:
    std::vector<std::unique_ptr<Page>> pages;
};
