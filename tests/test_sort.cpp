#include <gtest/gtest.h>
#include "Sorter.h"
#include <fstream>

void writeToFile(const std::string& path, const std::vector<int>& data) {
    std::ofstream out(path);
    for (int val : data) {
        out << val << "\n";
    }
}

std::vector<int> readFromFile(const std::string& path) {
    std::ifstream in(path);
    std::vector<int> result;
    int value;
    while (in >> value) result.push_back(value);
    return result;
}

TEST(SorterTest, SortsCorrectly) {
    std::string input = "test_input.txt";
    std::string output = "test_output.txt";
    std::vector<int> data = {5, 2, 9, 1, 7};
    std::vector<int> expected = {1, 2, 5, 7, 9};

    writeToFile(input, data);

    Sorter sorter(3);
    sorter.sort(input, output);

    std::vector<int> result = readFromFile(output);
    EXPECT_EQ(result, expected);
}

TEST(SorterTest, EmptyFile) {
    std::string input = "empty_input.txt";
    std::string output = "empty_output.txt";

    writeToFile(input, {});

    Sorter sorter(2);
    sorter.sort(input, output);

    std::vector<int> result = readFromFile(output);
    EXPECT_TRUE(result.empty());
}

TEST(SorterTest, AlreadySorted) {
    std::string input = "sorted_input.txt";
    std::string output = "sorted_output.txt";

    std::vector<int> data = {1, 2, 3, 4, 5};
    writeToFile(input, data);

    Sorter sorter(2);
    sorter.sort(input, output);

    std::vector<int> result = readFromFile(output);
    EXPECT_EQ(result, data);
}

TEST(SorterTest, ReverseSorted) {
    std::string input = "reverse_input.txt";
    std::string output = "reverse_output.txt";

    std::vector<int> data = {9, 7, 5, 3, 1};
    std::vector<int> expected = {1, 3, 5, 7, 9};

    writeToFile(input, data);

    Sorter sorter(3);
    sorter.sort(input, output);

    std::vector<int> result = readFromFile(output);
    EXPECT_EQ(result, expected);
}

TEST(SorterTest, WithDuplicates) {
    std::string input = "duplicates_input.txt";
    std::string output = "duplicates_output.txt";

    std::vector<int> data = {5, 1, 5, 3, 1};
    std::vector<int> expected = {1, 1, 3, 5, 5};

    writeToFile(input, data);

    Sorter sorter(2);
    sorter.sort(input, output);

    std::vector<int> result = readFromFile(output);
    EXPECT_EQ(result, expected);
}
TEST(SorterTest, NonexistentInputFile) {
    std::string input = "file_that_does_not_exist.txt";
    std::string output = "output.txt";

    Sorter sorter(3);

    EXPECT_THROW({
        sorter.sort(input, output);
    }, std::runtime_error);
}

TEST(SorterTest, InvalidDataInFile) {
    std::string input = "bad_data.txt";
    std::string output = "output.txt";

    std::ofstream out(input);
    out << "100\n200\nabc\n300\n";
    out.close();

    Sorter sorter(2);

    EXPECT_THROW({
        sorter.sort(input, output);
    }, std::runtime_error);
}
