#include "functions.h"
#include "yt-dlp.h"
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

std::filesystem::path ytDlpPath = std::filesystem::absolute("tools/yt-dlp.exe");
std::string ytdlp = ytDlpPath.string();
bool organizar = false;
extern bool convert;

std::string getFfmpeg()
{
    std::string ffmpeg_folder = searchFolder("tools", "ffmpeg");
    std::filesystem::path ffmpeg = std::filesystem::absolute(ffmpeg_folder + "/bin/ffmpeg.exe");
    return ("\"" + ffmpeg.string() + "\"");
}

std::string getVideoTitleFromSearch(const std::string& text) {


    std::string cmd = ytdlp + " \"ytsearch1:" + text + "\"" + " --get-title";
    return exec(cmd.c_str());
}


std::string getVideoTitleFromURL(const std::string& text) {

    std::string cmd = ytdlp + " " + text + " --get-title";
    return exec(cmd.c_str());
}


bool checkDownload(const std::string& comando) {
    std::string output;
    char buffer[512];
    FILE* pipe = _popen(comando.c_str(), "r");
    if (!pipe) return false;

    while (fgets(buffer, sizeof(buffer), pipe)) {
        output += buffer;
    }
    _pclose(pipe);
    std::string busca = "has already been downloaded";
    return (output.find(busca) != std::string::npos);
}

int searchAndDownloadVideo(std::string& text)
{
    std::cout << "[ >> ]: Procurando video...." << "\n";
    std::this_thread::sleep_for(std::chrono::seconds((1 / 10)));
    std::string cmd = ytdlp + " \"ytsearch1:" + text + "\" --extract-audio " + (std::string)"--ffmpeg-location " + getFfmpeg() + " --audio-format mp3 -o \"musicas/%(title)s.%(ext)s\" >nul 2>&1";
    std::cout << "[ >> ]: baixando...." << "\n";
    if (!checkDownload(cmd.c_str())) {
        system("cls");
        std::cout << ">> Música baixada com sucesso!" << "\n";
    }
    else std::cout << "[ ! ]: Aconteceu algum erro, Tente novamente." << "\n";
    convertAll();
    if (organizar) organizarPorAutor("musicas");
    return 0;
}


void downloadMusicUrl(const char* videoUrl)
{
    std::cout << "[ >> ]: Procurando video...." << "\n";
    std::this_thread::sleep_for(std::chrono::seconds((1 / 10)));
    std::cout << "[ >> ]: baixando...." << "\n";
    std::string cmd = ytdlp + " --extract-audio " + (std::string)"--ffmpeg-location " + getFfmpeg() + " --audio-format mp3 -o \"musicas/%(title)s.%(ext)s\" \"" + (std::string)videoUrl + "\" >nul 2>&1";

    system(cmd.c_str());
    if (!checkDownload(cmd.c_str()))
    {
        system("cls");
        std::cout << ">> Música baixada com sucesso!" << "\n";
    }
    else
        std::cout << "[ ! ]: Aconteceu algum erro, Tente novamente." << "\n";
    if(organizar) organizarPorAutor("musicas");
}
