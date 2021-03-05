#include <iostream>
#include <filesystem>
#include <fstream>
#include <cstdio>
#include <string>
#include <list>

using std::string;

int main() {
    std::filesystem::path cp = std::filesystem::current_path();
    string pathToProgramm = cp.parent_path().string();
    std::cout<<pathToProgramm<<std::endl;
    //string pathToProgramm = "E:\\Projects\\c++\\CrackWifi";
    string writeWifiesInFileCommand = "netsh wlan show profiles > "+pathToProgramm+"\\wifies-win1251.txt";
    const char *command = writeWifiesInFileCommand.c_str();
    system(command);

    writeWifiesInFileCommand = "";
    delete [] command;

    string commandForShowWifiesInUtf8 = "";
    string inFile =  pathToProgramm + "\\wifies-win1251.txt";
    string outFile = pathToProgramm + "\\wifies-UTF8.txt";
    commandForShowWifiesInUtf8 += "@chcp 866>nul \n";
    commandForShowWifiesInUtf8 += "@<\""+inFile+"\">\""+outFile+"\" (for /f \"delims=\" %%i in ('find/n /v \"\"') do @chcp 65001>nul& set x=%%i& cmd/v/c echo[!x:*]^^=!)";


    std::ofstream out;          // поток для записи
    out.open( "translateCode.bat"); // окрываем файл для записи
    if (out.is_open())
    {
        out << commandForShowWifiesInUtf8 << std::endl;
    }
    commandForShowWifiesInUtf8 = "";
    out.close();
    system("translateCode.bat");

    const char *commandToDeleteInFile = inFile.c_str();
    if (remove(commandToDeleteInFile)==-1) std::cout<<"error : file doesn't remove"<<std::endl;
    delete [] commandToDeleteInFile;


    string contentOutFile = "";
    std::string line;
    std::ifstream in(outFile); // окрываем файл для чтения
    if (in.is_open())
    {
        while (getline(in, line))
        {
            contentOutFile +=line;
        }
    }
    contentOutFile+=" ";

    std::list<string> nameWifies;
    for(int i = 0;i<contentOutFile.length();i++){
        if(contentOutFile[i] == ':'){
            string wifiName = "";
            for(int j = i+2;j<contentOutFile.length();j++){
                if(contentOutFile[j] == ' ') {
                    nameWifies.push_back(wifiName);
                    break;
                }
                else
                    wifiName+=contentOutFile[j];
            }
        }
    }

    auto nameWifiesIt = nameWifies.begin();
    for(int i = 0;i<nameWifies.size();i++){
        std::cout<<*nameWifiesIt<<std::endl;
        nameWifiesIt++;
        string commandForShowWifiInfo = "";
        commandForShowWifiInfo += "netsh wlan show profiles name="+*nameWifiesIt+" key=clear > "+pathToProgramm+"\\wifi\\"+*nameWifiesIt+".txt";
        const char *_commandForShowWifiInfo = commandForShowWifiInfo.c_str();
        system(_commandForShowWifiInfo);
    }

    in.close();
    std::cin.get();
    return  0;
}
