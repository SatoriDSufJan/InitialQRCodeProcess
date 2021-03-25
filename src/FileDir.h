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

// �����ļ���
void mkDir(const std::string& dirPath)
{
    _mkdir(dirPath.c_str());
}

// ������
// rename movefile...

// ɾ�����ļ��У������������е��ļ����ļ���
int removeDir(const std::string& path)
{
    long long hFile = 0;
    struct _finddatai64_t fileinfo;
    std::string p;
    if ((hFile = _findfirsti64(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
    {
        do
        {
            // �����Ŀ¼,����֮
            // �������,ֱ��ɾ��
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

// ����ļ���Ŀ¼�Ƿ����
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

// ����dirPath·����filter���磺*.jpg���ļ�������
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
        //�ж��Ƿ����ļ� 
        if (dataFind.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
        {
            iCount++;
        }
        bMoreFiles = FindNextFileA(hFind, &dataFind);
    }
    FindClose(hFind);

    return iCount;
}

// ����dirPath·�����ļ��е�����
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

// �õ�path·��������ָ����չ�����磺.mp4�����ļ���ȫ�� 
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
            // �����Ŀ¼,����֮
            // �������,�����б�
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
    //���ڲ��ҵľ��
    long long handle;
    std::string p;
    struct _finddatai64_t fileinfo;
    //��һ�β���
    std::string temp(inPath);
    handle = _findfirsti64(temp.append("\\*.jpg").c_str(), &fileinfo);
    if (handle == -1)
        return;
    do
    {
        //�ҵ����ļ����ļ���
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
            // �����Ŀ¼, ��ӵ�����������֮        
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
        // false: ����Ŀ��
        CopyFileA(vec[i].c_str(), saveJpgPath.c_str(), false);
    }
}

// ��ȡ���� txt ��ͼƬ��ͬʱ��Ŀ��Ŀ¼��׷���µ� txt
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
        // false: ����Ŀ��
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
        // false: ����Ŀ��
        CopyFileA(vec[i].c_str(), saveJpgPath.c_str(), false);
    }
}

void newCopyFile(const char* src, const char* target)
{
    CopyFileA(src, target, false);
}
