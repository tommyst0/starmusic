/*

*/

#include <iostream>
#include <cstdio>
#include <memory>
#include <filesystem>  
#include <cstdlib>
#include <string>

#include "curl/curl.h"

#include "devscripts/functions.h"
#include "devscripts/yt-dlp.h"

extern std::string ytdlp;
extern bool organizar;
extern bool convert;
namespace fs = std::filesystem;


int printHelp(char* argv[]) {
    std::cout << "Uso: " << argv[0] << " [opcoes]\n\n";
    std::cout << "opcoes:\n";
    std::cout << std::left; 
    std::cout << "  -h, --help"    << std::setw(23) << " " << "Mostra esta mensagem de ajuda\n";
    std::cout << "  -s, --search"  << std::setw(21) << " " << "Pesquisar video, Ex: " + (std::string)argv[0] + " Love Hurts (1976) -s\n";
    std::cout << "  -c, --convert" << std::setw(20) << " " << "Desativar a conversao (nativa) de todos os arquivos .webm em .mp3\n";
    std::cout << "  -o, --organizar" << std::setw(18) << " " << "Organizar pelo nome do canal\n";
    return 0;
}

int main(int argc, char* argv[])
{
    SetConsoleOutputCP(CP_UTF8);
    std::locale::global(std::locale(".UTF-8"));
    std::wcout.imbue(std::locale());

    if (!std::filesystem::exists("tools"))
    {
        std::cout <<  ">> Parece que voce não tem as dependências instaladas.. Iremos instalar para voce!" << "\n";

        fs::create_directories("tools");
        std::cout << "[ ! ]: Baixando dependências..." << "\n";


        const std::wstring ytDlpUrl = L"https://github.com/yt-dlp/yt-dlp/releases/latest/download/yt-dlp.exe";
        const std::wstring ffmpegZipUrl = L"https://www.gyan.dev/ffmpeg/builds/ffmpeg-release-essentials.zip";

        std::cout << "[ .. ]: Instalando yt-dlp [1 / 2].." << "\n";
        downloadFile(ytDlpUrl, L"tools/yt-dlp.exe");
        std::cout << "[ ! ]: \"yt-dlp\" instalado com sucesso!" << "\n";

        
        //
        // Install ffmpeg
        //
        std::cout << "[ .. ]: Instalando ffmpeg [2 / 2].." << "\n";
        downloadFile(ffmpegZipUrl, L"tools/temp.zip");
        std::cout << "[ ! ]: \"ffmpeg.zip\" instalado com sucesso!" << "\n";
        extractZip(L"tools/temp.zip", L"tools/");

        std::cout << "[ .. ]: Apagando arquivos temporarios.." << "\n";
        fs::remove("tools/temp.zip");

        std::cout << "Iniciando starmusic.." << "\n";
    }
    system("cls");

    if (!fs::exists("musicas")) fs::create_directory("musicas");
    std::string ffmpeg_folder = searchFolder("tools", "ffmpeg");

    //
    // flags
    //
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <url_do_youtube>\n";
        std::cerr << "\t\t\t--help, -h";
        return 1;
    }
    
    std::string beforeSearch;
    bool search = false;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-h" || arg == "--help") {
            return printHelp(argv);
        }
        if (arg == "--organizar" || arg == "-o") {
            organizar = true;
        }
        if (arg == "--convert" || arg == "-c") {
            convert = false;
        }
        if (arg == "--search" || arg == "-s") {
            search = true;
        }
        if (!beforeSearch.empty()) {
            beforeSearch += " ";
        }
        beforeSearch += arg;
    }
    if(search) return searchAndDownloadVideo(beforeSearch);
    else
    {
        std::string arg = argv[1];
        if (arg.find("youtu.be") != std::string::npos || arg.find("youtube.com") != std::string::npos)
        {
            downloadMusicUrl(argv[1]);
        }
        else
        {
            if (organizar)
            {
                organizarPorAutor("musicas");
                return 0;
            }
            convertAll();
            std::cout << "[ ERRO ]: Parece que isso não é um link do youtube." << "\n";
            std::cout << "[ ERRO ]: Use algo como: " << argv[0] << " https://www.youtube.com/watch?v=PIiINg7pNfo" << "\n";
            return 1;
        }
    }
    return convertAll();
}

