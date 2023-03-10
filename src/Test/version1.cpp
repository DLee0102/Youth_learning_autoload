#include <OpenXLSX.hpp>
#include <iostream>
#include <string>


int main() {
    std::string class_;
    std::string grade_;
    std::string obj_;

    std::cout << "请输入要处理的年级（输入示例：21）：" << std::endl;
    std::cin >> grade_;
    std::cout << "请输入要处理的班级（输入示例：1）：" << std::endl;
    std::cin >> class_;
    obj_ = grade_ + "级" + class_ + "班团支部";

    std::string total_path = "./软件学院2021级青年大学习学习情况记录.xlsx";
    OpenXLSX::XLDocument doc_total;
    doc_total.open(total_path);
    auto wks_total = doc_total.workbook().worksheet(obj_);

    std::vector<OpenXLSX::XLCellValue> readValues_total;

    int col_length = 0;

    std::string temp_path = "./学习用户明细.xlsx";

    OpenXLSX::XLDocument doc_temp;
    doc_temp.open(temp_path);
    auto wks = doc_temp.workbook().sheet(1).get<OpenXLSX::XLWorksheet>();

    std::vector<OpenXLSX::XLCellValue> readValues;

    int temp_length = 0;
    int total_length = 2;
    for (auto& row : wks.rows()) {
        readValues = row.values();
        if (readValues.size() == 0) {
            break;
        }
        temp_length++;
    }

    for (auto& row_m : wks_total.rows(3, OpenXLSX::MAX_ROWS)) {
        readValues_total = row_m.values();
        if (readValues_total.size() == 0) {
            break;
        }
        total_length++;
    }

    total_length--;

    std::vector<OpenXLSX::XLCellValue> writeValues(total_length - 2);
    for (int i = 0; i < total_length - 2; i++) {
        writeValues[i] = 0;
    }

    for (auto& row : wks.rows(2, temp_length)) {
        readValues = row.values();
        if (readValues.size() != 0) {

            int index = 0;
            for (auto &row_m : wks_total.rows(3, total_length)) {
                readValues_total = row_m.values();
                col_length = readValues_total.size();
                std::cout << col_length << std::endl;
                
                if (readValues_total.size() != 0) {
                    std::cout << readValues[0] << " " << readValues_total[2] << std::endl;
                    if (readValues[0].get<std::string>().compare(readValues_total[2].get<std::string>()) == 0) {
                        writeValues[index] = 1; 
                    }
                }
                index++;
            }
        }
    }

    std::cout << writeValues.size() << std::endl;
    for (int i = 0; i < writeValues.size(); i++) {
        wks_total.cell(3 + i, col_length + 1).value() = writeValues[i];
        std::cout << writeValues[i] << std::endl;
    }
    

    doc_temp.save();
    doc_temp.close();

    doc_total.save();
    doc_total.close();

    return 0;
}