
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <numeric>

using Line = std::vector<std::string>;
using Table = std::vector<std::vector<double>>;

Line DEVICES{
    "PC",                           // Компьютер
    "Laptop",                       // Ноутбук
    "Tabloid",                      // Планшет
    "Smartphone",                   // Смартфон
};

Line METRICS{
    "Price",                        // Цена
    "Mainten.",                  // Стоимость обслуживания
    "Volume",                       // Объем памяти
    "Display",                      // Размер экрана
};

// Для задания 1

// Оценка альтернатив
Table table1{
    {2, 3, 7, 7},
    {2, 5, 7, 5},
    {3, 6, 3, 3},
    {5, 7, 3, 1},
};

// Минимум коэффициенты

// Для задания 2

Table table2{
    {2, 3, 7, 7},
    {2, 5, 7, 5},
    {3, 6, 3, 3},
    {5, 7, 3, 1},
};

// Для задания 3

Table table3{
    {2, 3, 7, 7},
    {2, 5, 7, 5},
    {3, 6, 3, 3},
    {5, 7, 3, 1},
};

Table expert3{
    {0.0, 1.0, 0.5, 1.0},
    {0.0, 0.0, 0.0, 0.0},
    {0.5, 1.0, 0.0, 0.5},
    {0.0, 1.0, 0.5, 0.0},
};

// Для задания 4

// По цене
Table pairCompare41{
    {1.00, 1.00, 1. / 2, 1. / 3},
    {1.00, 1.00, 1. / 2, 1. / 4},
    {2.00, 2.00, 1.00, 2.00},
    {3.00, 4.00, 1. / 2, 1.00},
};

// По стоимости обслуживания
Table pairCompare42{
    {1.00, 2.00, 2.00, 3.00},
    {1. / 2, 1.00, 1. / 2, 1. / 2},
    {1. / 2, 2.00, 1.00, 2.00},
    {1. / 3, 2.00, 1. / 2, 1.00},
};

// По объему памяти
Table pairCompare43{
    {1.00, 1.00, 3.00, 3.00},
    {1.00, 1.00, 3.00, 3.00},
    {1. / 3, 1. / 3, 1.00, 1.00},
    {1. / 3, 1. / 3, 1.00, 1.00},
};

// По размеру экрана
Table pairCompare44{
    {1.00, 2.00, 4.00, 7.00},
    {1. / 2, 1.00, 3.00, 5.00},
    {1. / 4, 1. / 3, 1.00, 3.00},
    {1. / 7, 1. / 5, 1. / 3, 1.00},
};

// По приоритету
Table pairCompare45{
    {1.00, 2.00, 1. / 5, 1. / 6},
    {1. / 2, 1.00, 1. / 5, 1. / 7},
    {5.00, 5.00, 1.00, 1. / 2},
    {6.00, 7.00, 2.00, 1.00},
};

void printTable(const Line &rowNames, const Line &columnNames, const Table &content)
{
    std::cout << "| `````````` | ";
    for (const std::string &name: columnNames) {
        std::cout << std::setw(10) << name << " | ";
    }
    std::cout << "\n+ ";
    for (size_t i = 0; i <= columnNames.size(); ++i) {
        std::cout << "---------- + ";
    }
    
    for (size_t i = 0; i < rowNames.size(); ++i) {
        auto &row = content[i];
        std::cout << "\n| " << std::setw(10) << rowNames[i] << " | ";
        
        for (double j : row) {
            std::cout << std::setw(10) << j << " | ";
        }
        std::cout << "\n+ ";
        for (size_t j = 0; j <= columnNames.size(); ++j) {
            std::cout << "---------- + ";
        }
    }
    
    std::cout << std::endl;
}

auto getTableColumnMax(const Table &content, size_t column)
{
    auto max = content[0][column];
    
    for (const auto &row : content) {
        if (max < row[column]) {
            max = row[column];
        }
    }
    return max;
}

auto getTableColumnMin(const Table &content, size_t column)
{
    auto min = content[0][column];
    
    for (const auto &row : content) {
        if (min > row[column]) {
            min = row[column];
        }
    }
    return min;
}

std::vector<double> printTableTask4(const Line &rowNames, const Line &columnNames, const Table &content)
{
    std::vector<double> rowSum{0, 0, 0, 0};
    for (size_t i = 0; i < content.size(); ++i) {
        for (size_t j = 0; j < content[i].size(); ++j) {
            rowSum[i] += content[i][j];
        }
    }
    
    std::vector<double> rowSumNormalized = rowSum;
    double sum = std::accumulate(rowSum.begin(), rowSum.end(), 0.);
    for (auto &value : rowSumNormalized) {
        value /= sum;
    }
    
    std::vector<double> columnSum{0, 0, 0, 0};
    for (auto &row : content) {
        for (size_t i = 0; i < row.size(); ++i) {
            columnSum[i] += row[i];
        }
    }
    
    std::vector<double> eigenvalues{0, 0, 0, 0};
    for (size_t i = 0; i < columnSum.size(); ++i) {
        eigenvalues[i] = columnSum[i] * rowSumNormalized[i];
    }
    
    double os = ((std::accumulate(eigenvalues.begin(), eigenvalues.end(), 0.) - 4) / 3) / 0.9;
    
    Table newTable{
        {content[0][0], content[0][1], content[0][2], content[0][3], rowSum[0], rowSumNormalized[0], eigenvalues[0]},
        {content[1][0], content[1][1], content[1][2], content[1][3], rowSum[1], rowSumNormalized[1], eigenvalues[1]},
        {content[2][0], content[2][1], content[2][2], content[2][3], rowSum[2], rowSumNormalized[2], eigenvalues[2]},
        {content[3][0], content[3][1], content[3][2], content[3][3], rowSum[3], rowSumNormalized[3], eigenvalues[3]},
    };
    
    printTable(rowNames, {columnNames[0], columnNames[1], columnNames[2], columnNames[3], "sum", "n. sum", "eigen"}, newTable);
    std::cout << "OC: " << os;
    
    return rowSumNormalized;
}

int main()
{
    std::cout << "TASK 1\n\n";
    
    std::cout << "    Task 1 table\n";
    printTable(DEVICES, METRICS, table1);
    
    std::cout << "Big criteria: Volume\n";
    
    double minPrice = 0;              // Дешевизна (по условию) (принимается любая цена)
    double maxMaintenance = 0.5;        // Стоимость обслуживания
    double minDisplay = 0.4;
    
    std::cout << "Min price coefficient: " << minPrice << "\n";
    std::cout << "Max miantenance coefficient: " << maxMaintenance << "\n";
    std::cout << "Min display coefficient: " << minDisplay << "\n";
    
    for (size_t column: {0, 1, 3}) {
        double max = getTableColumnMax(table1, column);
        double min = getTableColumnMin(table1, column);
        
        for (auto &row : table1) {
            row[column] = (row[column] - min) / (max - min);
        }
    }
    
    std::cout << "\n    Task 1 table normalized\n";
    printTable(DEVICES, METRICS, table1);
    
    for (auto &row : table1) {
        row[0] = row[0] >= minPrice;
    }
    for (auto &row : table1) {
        row[1] = row[1] <= maxMaintenance;
    }
    for (auto &row : table1) {
        row[3] = row[3] >= minDisplay;
    }
    
    std::cout << "\n    Task 1 table binary\n";
    printTable(DEVICES, METRICS, table1);
    
    std::cout << "\nTask 1 result: ";
    for (size_t i = 0; i < DEVICES.size(); ++i) {
        if (table1[i][0] == 1 && table1[i][1] == 1 && table1[i][3] == 1) {
            std::cout << DEVICES[i] << ", ";
        }
    }
    
    std::cout << "\n\n\nTASK 2\n\n";
    std::cout << "    Task 2 table\n";
    printTable(DEVICES, METRICS, table2);
    
    std::cout << "Big criteria: Price, Display\n";
    std::cout << "Distance: Manhetten\n";
    
    double minDistance = 99999999;
    std::string minDeviceName;
    
    std::cout << "Copy (yotx.ru): \n    (10;10) ";
    for (size_t i = 0; i < DEVICES.size(); ++i) {
        std::cout << "(" << table2[i][0] << ";" << table2[i][3] << ") ";
        
        double distance = (10 - table2[i][0]) + (10 - table2[i][3]);
        if (minDistance > distance) {
            minDistance = distance;
            minDeviceName = DEVICES[i];
        }
    }
    std::cout << "\n\nTask 2 result: " << minDeviceName << " (" << minDistance << ")";
    
    std::cout << "\n\n\nTASK 3\n\n";
    std::cout << "\n    Task 3 table\n";
    printTable(DEVICES, METRICS, table3);
    
    std::vector<double> columnSum{0, 0, 0, 0};
    for (auto &row : table3) {
        for (size_t i = 0; i < row.size(); ++i) {
            columnSum[i] += row[i];
        }
    }
    
    for (auto &row : table3) {
        for (size_t i = 0; i < row.size(); ++i) {
            row[i] /= columnSum[i];
        }
    }
    
    std::cout << "\n    Task 3 table normalized\n";
    printTable(DEVICES, METRICS, table3);
    
    std::cout << "\n    Task 3 expert\n";
    printTable(METRICS, METRICS, expert3);
    
    std::vector<double> expertSum3{0, 0, 0, 0};
    double expertSumSum = 0;
    for (size_t i = 0; i < expert3.size(); ++i) {
        for (const auto &value: expert3[i]) {
            expertSum3[i] += value;
            expertSumSum += value;
        }
    }
    
    std::cout << "\n    Task 3 expert vector normalized\n";
    for (const auto &row: expertSum3) {
        std::cout << row / expertSumSum << "\n";
    }
    
    std::vector<double> result3{0, 0, 0, 0};
    for (size_t i = 0; i < table3.size(); ++i) {
        for (size_t j = 0; j < table3[i].size(); ++j) {
            result3[i] += table3[i][j] * expertSum3[j];
        }
    }
    
    double optValue = -9999999;
    std::string optDeviceName;
    
    std::cout << "\n    Task 3 result vector\n";
    for (size_t i = 0; i < result3.size(); ++i) {
        std::cout << result3[i] << "\n";
        if (optValue < result3[i]) {
            optValue = result3[i];
            optDeviceName = DEVICES[i];
        }
    }
    
    std::cout << "\n    Task 3 result: " << optDeviceName;
    
    std::cout << "\n\n\nTASK 4\n\n";
    
    std::cout << "\n\nBy price\n";
    auto sum1 = printTableTask4(DEVICES, DEVICES, pairCompare41);
    std::cout << "\n\nBy maintenance\n";
    auto sum2 = printTableTask4(DEVICES, DEVICES, pairCompare42);
    std::cout << "\n\nBy volume\n";
    auto sum3 = printTableTask4(DEVICES, DEVICES, pairCompare43);
    std::cout << "\n\nBy display\n";
    auto sum4 = printTableTask4(DEVICES, DEVICES, pairCompare44);
    std::cout << "\n\nBy criterias\n";
    auto sum5 = printTableTask4(METRICS, METRICS, pairCompare45);
    
    Table left{
        {sum1[0], sum2[0], sum3[0], sum4[0]},
        {sum1[1], sum2[1], sum3[1], sum4[1]},
        {sum1[2], sum2[2], sum3[2], sum4[2]},
        {sum1[3], sum2[3], sum3[3], sum4[3]},
    };
    
    std::vector<double> result4{0, 0, 0, 0};
    for (size_t i = 0; i < left.size(); ++i) {
        for (size_t j = 0; j < left[i].size(); ++j) {
            result4[i] += left[i][j] * sum5[j];
        }
    }
    
    double optValue4 = -9999999;
    std::string optDeviceName4;
    
    std::cout << "\n\n    Task 4 result vector\n";
    for (size_t i = 0; i < result4.size(); ++i) {
        std::cout << result4[i] << "\n";
        if (optValue4 < result4[i]) {
            optValue4 = result4[i];
            optDeviceName4 = DEVICES[i];
        }
    }
    
    std::cout << "\n    Task 4 result: " << optDeviceName;
    std::cout <<std::endl;
}

