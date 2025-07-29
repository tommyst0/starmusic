#pragma once

#ifndef EXTRACTOR_H
#define EXTRACTOR_H

#include <iostream>
#include <cstdio>
#include <memory>
#include <filesystem>  
#include <cstdlib>
#include <string>

namespace fs = std::filesystem;

bool downloadFile(const std::wstring& url, const std::wstring& pasta);
bool extractZip(const std::wstring& zipPath, const std::wstring& outputDir);
std::string searchFolder(const fs::path& baseDir, const std::string& prefixo);
std::string exec(const char* cmd);
void convertWebmToMp3(const fs::path& webmFile);
int convertAll();
std::string getAuthorFromMp3(const fs::path& file);
int organizarPorAutor(std::string baseDir);
std::vector<std::string> split(const std::string& str, char delimitador);

#endif