#pragma once

#ifndef YTDLP_H
#define YTDLP_H

#include <iostream>
#include <cstdio>
#include <memory>
#include <filesystem>  
#include <cstdlib>
#include <string>


namespace fs = std::filesystem;

std::string getVideoTitleFromSearch(const std::string& text);
bool checkDownload(const std::string& comando);
int searchAndDownloadVideo(std::string& text);
void downloadMusicUrl(const char* videoUrl);

#endif