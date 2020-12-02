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

vector<ptopoint> readfromfile::file2pto(const char *filename)
{
    vector<ptopoint> tmp;
    FILE *file = checkfile(filename);
    double temp[5];
    while (~fscanf(file, "%lf%lf%lf%lf%lf", &temp[0], &temp[1], &temp[2], &temp[3], &temp[4]))
    {
        for (int i = 1; i < 5; i++)
            temp[i] /= 1000000; // 单位由微米转为米
        tmp.push_back(ptopoint(temp));
    }
    cout << "像对坐标读入完成，共读入" << tmp.size() << "个数据" << endl;
    fclose(file);
    return tmp;
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

vector<checkpt> readfromfile::file2chk(const char *filename)
{
    vector<checkpt> tmp;
    FILE *file = checkfile(filename);
    double temp[4];
    while (~fscanf(file, "%lf%lf%lf%lf", &temp[0], &temp[1], &temp[2], &temp[3]))
    {
        tmp.push_back(checkpt(temp));
    }
    cout << "检查点坐标读入完成，共读入" << tmp.size() << "个数据" << endl;
    fclose(file);
    return tmp;
}