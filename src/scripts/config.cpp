

/*
void executar(const std::wstring& caminhoExe) {
    ShellExecuteW(NULL, L"open", caminhoExe.c_str(), NULL, NULL, 1);
}
*/

#include "./config.h"

json loadConfig(const std::string& arquivo)
{
    std::ifstream i("config.json");

    if (!i.is_open()) {
        std::cerr << "Could not open the file!" << std::endl;
        return 1;
    }

    // Parse the JSON data from the file stream
    json jf = json::parse(i);
    i.close();
    return jf;
}

Programas loadServer(const json& config)
{
    Programas p{};

    auto carregar = [&](const char* key, std::string& destino)
        {
            if (!config.contains(key)) return;

            const auto& obj = config.at(key);

            if (obj.contains("caminho") && obj["caminho"].is_string())
                destino = obj["caminho"].get<std::string>();
        };

    carregar("textdraw", p.textdraw);
    carregar("map", p.map);
    carregar("server", p.server);

    return p;
}