#include "readfromfile.h"
using namespace std;

inline FILE *readfromfile::checkfile(const char *filename)
{
    FILE *file;
    try
    {
        file = fopen(filename, "r");
        if (file == NULL)
            throw 0;
    }
    catch (...)
    {
        cout << filename << "读入异常" << endl;
        exit(0);
    } // 读入错误抛出
    return file;
}



vector<control_pt> readfromfile::file2con(const char *filename)
{
    vector<control_pt> tmp;
    FILE *file = checkfile(filename);
    double temp[4];
    while (~fscanf(file, "%lf%lf%lf%lf", &temp[0], &temp[1], &temp[2], &temp[3]))
    {
        tmp.push_back(control_pt(temp));
    }
    cout << "控制点坐标读入完成，共读入" << tmp.size() << "个数据" << endl;
    fclose(file);
    return tmp;
}

