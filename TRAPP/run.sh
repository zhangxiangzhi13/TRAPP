#!/bin/bash

# 编译程序
g++ -O3 -march=native  readfile.cpp -o readfile

# 检查编译是否成功
if [ $? -eq 0 ]; then
    echo "Compilation successful. Running program..."
    # 运行程序
    ./readfile > output.txt 
else
    echo "Compilation failed."
fi
