#pragma once
#include <iostream>
#include <vector>
#include <string>

void mkDir(const std::string& dirPath);
int removeDir(const std::string& path);

bool checkExist(const std::string& Path);

int countFile(const std::string& dirPath, const std::string& filter);
int countDir(const std::string& dirPath);

void getAllFiles(const std::string& path, const std::string& filenameExtension, std::vector<std::string>& files);
void myGetAllFiles(std::string& path, std::vector<std::string>& dirs);
void getAllDirs(const std::string& path, std::vector<std::string>& dirs);

void copyAllJpg(const std::string& sourcePath, const std::string& targetPath);
void copyAllJpg_FromTxt(const std::string& txtPath, const std::string& targetPath, const std::string& newTxtPath);
void copyAllModel(const std::string& sourcePath, const std::string& targetPath);

void newCopyFile(const char* src, const char* target);


#include <fstream>
#include <direct.h>
#include <io.h>
#include <windows.h>

// 创建文件夹
void mkDir(const std::string& dirPath)
{
    _mkdir(dirPath.c_str());
}

// 重命名
// rename movefile...

// 删除该文件夹，包括其中所有的文件和文件夹
int removeDir(const std::string& path)
{
    long long hFile = 0;
    struct _finddatai64_t fileinfo;
    std::string p;
    if ((hFile = _findfirsti64(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
    {
        do
        {
            // 如果是目录,迭代之
            // 如果不是,直接删除
            if ((fileinfo.attrib & _A_SUBDIR))
            {
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                {
                    removeDir(p.assign(path).append("\\").append(fileinfo.name));
                }
            }
            else
            {
                remove((p.assign(path).append("\\").append(fileinfo.name)).c_str());
            }
        } while (_findnexti64(hFile, &fileinfo) == 0);

        _findclose(hFile);
    }

    return _rmdir(path.c_str());
}

// 检查文件，目录是否存在
bool checkExist(const std::string& Path)
{
    if ((_access(Path.c_str(), 0)) != -1)
    {
        return true;
    }
    else
    {
        return false;
    }

}

// 计算dirPath路径下filter（如：*.jpg）文件的数量
int countFile(const std::string& dirPath, const std::string& filter)
{
    HANDLE hFind;
    WIN32_FIND_DATAA dataFind;
    BOOL bMoreFiles = TRUE;
    int iCount = 0;

    std::string temp = dirPath;
    temp += "\\";
    temp += filter;

    hFind = FindFirstFileA(temp.c_str(), &dataFind);
    while (hFind != INVALID_HANDLE_VALUE && bMoreFiles == TRUE)
    {
        //判断是否是文件 
        if (dataFind.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
        {
            iCount++;
        }
        bMoreFiles = FindNextFileA(hFind, &dataFind);
    }
    FindClose(hFind);

    return iCount;
}

// 计算dirPath路径下文件夹的数量
int countDir(const std::string& dirPath)
{
    int iCount = 0;
    long long hFile = 0;
    struct _finddatai64_t fileinfo;
    std::string p;
    if ((hFile = _findfirsti64(p.assign(dirPath).append("\\*").c_str(), &fileinfo)) != -1)
    {
        do
        {
            if ((fileinfo.attrib & _A_SUBDIR))
            {
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                {
                    ++iCount;
                }
            }
        } while (_findnexti64(hFile, &fileinfo) == 0);
        _findclose(hFile);
    }
    return iCount;
}

// 得到path路径下所有指定扩展名（如：.mp4）的文件名全称 
void getAllFiles(const std::string& path, const std::string& filenameExtension, std::vector<std::string>& files)
{
    if (!checkExist(path))
        return;
    long long hFile = 0;
    struct _finddatai64_t fileinfo;
    std::string p;
    if ((hFile = _findfirsti64(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
    {
        do
        {
            // 如果是目录,迭代之
            // 如果不是,加入列表
            if ((fileinfo.attrib & _A_SUBDIR))
            {
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                    getAllFiles(p.assign(path).append("\\").append(fileinfo.name), filenameExtension, files);
            }
            else
            {
                if (p.assign(fileinfo.name).find(filenameExtension) != -1)
                    files.push_back(p.assign(path).append("\\").append(fileinfo.name));
            }
        } while (_findnexti64(hFile, &fileinfo) == 0);

        _findclose(hFile);
    }
}

void myGetAllFiles(std::string &inPath,std::vector<std::string>& dirs)
{  
    //用于查找的句柄
    long long handle;
    std::string p;
    struct _finddatai64_t fileinfo;
    //第一次查找
    std::string temp(inPath);
    handle = _findfirsti64(temp.append("\\*.jpg").c_str(), &fileinfo);
    if (handle == -1)
        return;
    do
    {
        //找到的文件的文件名
        dirs.push_back(p.assign(inPath).append("\\").append(fileinfo.name));

    } while (!_findnexti64(handle, &fileinfo));

    _findclose(handle);
}


void getAllDirs(const std::string& path, std::vector<std::string>& dirs)
{
    if (!checkExist(path))
        return;
    long long hFile = 0;
    struct _finddatai64_t fileinfo;
    std::string p;
    if ((hFile = _findfirsti64(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
    {
        do
        {
            // 如果是目录, 添加到容器并迭代之        
            if ((fileinfo.attrib & _A_SUBDIR))
            {
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                {
                    dirs.push_back(p.assign(path).append("\\").append(fileinfo.name));
                    getAllDirs(p.assign(path).append("\\").append(fileinfo.name), dirs);
                }
            }
        } while (_findnexti64(hFile, &fileinfo) == 0);

        _findclose(hFile);
    }
}

void copyAllJpg(const std::string& sourcePath, const std::string& targetPath)
{
    std::vector<std::string> vec;
    int existNum = countFile(targetPath, "*.jpg");
    char jpgCount_name[32];

    getAllFiles(sourcePath, ".jpg", vec);
    for (std::string::size_type i = 0; i < vec.size(); i++)
    {
        ++existNum;
        _itoa_s(existNum, jpgCount_name, 10);
        std::string saveJpgPath = targetPath;
        saveJpgPath += "\\";
        saveJpgPath += jpgCount_name;
        saveJpgPath += ".jpg";
        // false: 覆盖目标
        CopyFileA(vec[i].c_str(), saveJpgPath.c_str(), false);
    }
}

// 读取复制 txt 中图片，同时在目标目录下追加新的 txt
void copyAllJpg_FromTxt(const std::string& txtPath, const std::string& targetPath, const std::string& newTxtPath)
{
    std::vector<std::string> Jpg_List;
    std::ifstream if1(txtPath);
    while (!if1.eof())
    {
        std::string s;
        getline(if1, s);
        if (s == "")
            continue;
        Jpg_List.push_back(s);
        if (if1.eof())
            break;
    }
    if1.close();
    if1.clear();

    int existNum = countFile(targetPath, "*.jpg");
    char jpgCount_name[32];
    std::ofstream oftxt(newTxtPath, std::ios::app);
    if (!oftxt)
        return;
    for (std::string::size_type i = 0; i < Jpg_List.size(); i++)
    {
        ++existNum;
        _itoa(existNum, jpgCount_name, 10);
        std::string jpgName;
        jpgName.assign(jpgCount_name);
        if (jpgName.length() < 10)
        {
            jpgName.insert(0, 10 - jpgName.length(), '0');
        }
        std::string saveJpgPath = targetPath;
        saveJpgPath += "\\";
        saveJpgPath += jpgName;
        saveJpgPath += ".jpg";
        // false: 覆盖目标
        CopyFileA(Jpg_List[i].c_str(), saveJpgPath.c_str(), false);
        oftxt << saveJpgPath << std::endl;
    }
    oftxt.close();
}

void copyAllModel(const std::string& sourcePath, const std::string& targetPath)
{
    std::vector<std::string> vec;
    int existNum = countFile(targetPath, "*.model");
    char jpgCount_name[32];

    getAllFiles(sourcePath, ".model", vec);
    for (std::string::size_type i = 0; i < vec.size(); i++)
    {
        ++existNum;
        _itoa(existNum, jpgCount_name, 10);
        std::string saveJpgPath = targetPath;
        saveJpgPath += "\\";
        saveJpgPath += jpgCount_name;
        saveJpgPath += ".model";
        // false: 覆盖目标
        CopyFileA(vec[i].c_str(), saveJpgPath.c_str(), false);
    }
}

void newCopyFile(const char* src, const char* target)
{
    CopyFileA(src, target, false);
}
