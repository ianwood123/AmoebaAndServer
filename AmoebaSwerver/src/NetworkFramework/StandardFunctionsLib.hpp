#define _usingStandardFunctionsLib_
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <conio.h>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <deque>
#include <sstream>
#include <tchar.h>
#include <ctime>
#include <typeinfo>
#include <process.h>
#include <exception>
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x501
#endif
#include <ws2tcpip.h>
#include <windows.h>

#define sleep(long) Sleep(long)
#define nanoSleep(long) usleep(long)

using namespace std;

string toLower(string in)
{
    string ret = "";
    for (int i = 0; i < in.length(); i++)
    {
        char c = in[i];
        c = tolower(c);
        ret += c;
    }
    return ret;
}

char toLower(char in)
{
    return tolower(in);
}

string toString (char in[])
{
    stringstream s;
    s << in;
    return s.str();
}

string toString (long in)
{
    stringstream s;
    s << in;
    return s.str();
}

string toString (int in)
{
    stringstream s;
    s << in;
    return s.str();
}

string toString (double in)
{
    stringstream s;
    s << in;
    return s.str();
}

int toInt(string in)
{
    return atoi((char*)in.c_str());
}

long toLong(string in)
{
    return atol((char*)in.c_str());
}

double toDouble(string in)
{
    return atof((char*)in.c_str());
}

float toFloat(string in)
{
    return atof((char*)in.c_str());
}

bool toBool(string in)
{
    in = toLower(in);
    if (in == "1" || in == "true" || "t")
    {
        return true;
    }
    return false;
}

bool toBool(char in)
{
    in = toLower(in);
    if (in == '1' || in == 't')
    {
        return true;
    }
    return false;
}

int timestampMilliseconds()
{
    timeb tb;
    ftime(&tb);
    int nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
    return nCount;
}

string dateTimeStamp()
{
    time_t rawtime;
    struct tm *timeinfo;
    char buf[100];
    time (&rawtime);
    timeinfo=localtime (&rawtime);
    strftime (buf,100,"%I:%M %p - %x",timeinfo);
    return buf;
}

char* toCString(string in)
{
    return (char*)in.c_str();
}

char* toCString(long in)
{
    return (char*)toString(in).c_str();
}

char* toCString(int in)
{
    return (char*)toString(in).c_str();
}

char* toCString(double in)
{
    return (char*)toString(in).c_str();
}

string replace(string originalPattern, string replacementPattern, string text)
{
    string ret = text;
    deque<int> points;
    int currPoint = text.find(originalPattern);

    while (currPoint != string::npos)
    {
        points.push_back(currPoint);
        currPoint = text.find(originalPattern, ++currPoint);
    }

    for (int i = points.size() - 1; i >= 0; i--)
    {
        ret.replace(points[i], originalPattern.length(), replacementPattern);
    }
    return ret;
}

string replace(char originalChar, char replacementChar, string text)
{
    string ret = text;
    int pos = text.find(originalChar);
    int lastPos = string::npos;
    while (pos != string::npos && pos != lastPos)
    {
        ret[pos] = replacementChar;
        lastPos = pos;
        pos = ret.find(originalChar);
    }
    return ret;
}

bool contains(string pattern, string text)
{
    if (text.find(pattern) != string::npos)
    {
        return true;
    }
    return false;
}

bool contains(char c, string text)
{
    if (text.find(c) != string::npos)
    {
        return true;
    }
    return false;
}

string reverse(string s)
{
    string ret = "";
    for (int i = s.length() - 1; i > -1; i--)
    {
        ret += s[i];
    }
    return ret;
}

bool fileExists(string filename)
{
    ifstream file(toCString(filename));
    if (file)
    {
        file.close();
        return true;
    }
    return false;
}

unsigned long fileBytes(string filename)
{
    unsigned long ret = 0;
    if (filename == "")
    {
        return 0;
    }
    FILE* file = fopen(toCString(filename), "rb");
    fseek (file, 0, SEEK_END);
    ret = ftell(file);
    rewind(file);
    fclose(file);
    return ret;
}

deque<string> readDir(string path)
{
    deque<string> ret;
    path += "/*";
    _finddata_t data;
    int ff = _findfirst (toCString(path), &data);
    if (ff != -1)
    {
        int res = 0;
        while (res != -1)
        {
            if (strcmp(data.name, ".") && strcmp(data.name, ".."))
            {
                ret.push_back(data.name);
            }
            res = _findnext(ff, &data);
        }
        _findclose(ff);
    }
    return ret;
}

string readTextFile(string filename)
{
    string data = "";
    string line = "";
    ifstream file(toCString(filename));
    if (!file)
    {
        return "";
    }
    getline(file, data);
    while (getline(file, line))
    {
        data += "\n" + line;
    }
    file.close();
    return data;
}

void startProcess(string path)
{
    popen(toCString(path), "r");
}

void startBackgroundProcess(string command)
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    memset(&si, 0, sizeof(si));
    memset(&pi, 0, sizeof(pi));
    si.cb = sizeof(si);
    CreateProcess(NULL, //full path to exe
                  (char*)command.c_str(), //cmd line options
                  NULL, //process security attr
                  NULL, //thread security attr
                  false, //inherit handles flag
                  CREATE_NO_WINDOW,//process creation flags
                  NULL,//environment
                  NULL, //current directory
                  &si,//startup info
                  &pi//process info
                 );
}

struct KeyValuePair
{
    const string field;
    const string value;

    KeyValuePair(string field, string value) : field(field), value(value) {}
};
