#!/bin/bash
SOURCE_FILE1="file1.c"
SOURCE_FILE2="file2.c"
EXECUTABLE1="file1"
EXECUTABLE2="file2"

gcc -o $EXECUTABLE1 $SOURCE_FILE1

if [ $? -eq 0 ]; then
    echo "Компиляция программы 1 успешно завершена."
else
    echo "Ошибка компиляции программы 1."
    exit 1
fi

gcc -o $EXECUTABLE2 $SOURCE_FILE2

if [ $? -eq 0 ]; then
    echo "Компиляция программы 2 успешно завершена."
else
    echo "Ошибка компиляции программы 2."
    exit 1
fi

./$EXECUTABLE2 arg1 arg2 arg3

if [ $? -eq 0 ]; then
    echo "Программа 2 завершена."
else
    echo "Программа 2 завершилась с ошибкой."
fi
