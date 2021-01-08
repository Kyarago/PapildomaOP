#include "Fjos.h"

/* Funkcija sutvarkanti zodzius, kad zenklai nebutu zodzio dalim ir pakeicia raides i mazasias*/
string sutvarkymas(string zodis) {
    string sutvarkyti;
    for (char& t : zodis) {
        t = std::tolower(t);
    }
    for (char d : zodis) {
        if (std::isalnum(d)) {
            sutvarkyti = sutvarkyti + d;
        }
    }
    return sutvarkyti;
}

/* Funkcija paskaiciuojanti kiek vienodu pasikartojanciu zodziu yra*/
void kiek() {
    string pav = "";
    pav = "Lotynu.txt";
    std::ifstream file(pav);
    if (file.good()) {
        string next;
        std::map <string, int> zodziai;
        while (file >> next) {
            const string key = sutvarkymas(next);
            zodziai[key]++;
        }
        cout << "\n\n" << "Number of words: " << zodziai[next] << endl;

        file.close();
        for (const auto& i : zodziai) {
            if (i.second > 1) {
                cout << "Zodis: " << std::left << std::setw(20) << i.first << " pasikartojo " << std::left << std::setw(3) << i.second << " kartus" << endl;
            }
        }
    }
    else cout << "Failas zodziai.txt aplanke nebuvo rastas" << endl;
    file.close();
}

/* Funkcija ivykdanti galutini uzduoties prasyma - isveda faila su pasikartojanciais zodziais, ju eilutem faile ir surasanti visas faile rastas nuorodas*/
void Eilutes() {
    string pav = "";
    pav = "Lotynu.txt";
    std::ifstream file(pav);
    if (file.good()) {
        std::vector<string> url;
        string next;
        map <string, int> zodziaiMap;
        map<string, std::vector<int>> eilutesMap;
        string line;
        int eil = 1;
        while (getline(file, line)) {
            std::istringstream eilute(line);
            string next;
            while (eilute >> next) {
                if (regex_match(next, std::regex("(http|https)://([^/ :]+):?([^/ ]*)(/?[^ #?]*)\\x3f?([^ #]*)#?([^ ]*)")) || regex_match(next, std::regex("^(https?:\\/\\/)?([\\da-z\\.-]+)\\.([a-z\\.]{2,6})([\\/\\w \\.-]*)*\\/?$"))) {
                    url.push_back(next);
                    continue;
                }
                const string key = sutvarkymas(next);
                zodziaiMap[key]++;
                if (zodziaiMap[key] > 1) {
                    string line2 = std::to_string(eil);
                    char lineMem = line2.front();
                    char lineMbc = line2.back();
                    if (eilutesMap[next].empty()) {
                        eilutesMap[next].push_back(eil);
                    }
                    else if (static_cast<char>(eilutesMap[next].back() != lineMem)) {
                        eilutesMap[next].push_back(eil);
                    }
                }
                else eilutesMap[next].push_back(eil);
            }
            eil++;
        }
        
        set<pair<string, int>> set(zodziaiMap.begin(), zodziaiMap.end());
        std::ofstream out("Atsakymas.txt");
        out << "-------ZODZIAI-------" << endl;
        for (auto t : set) {
            if (t.second > 1) {
                out << "Zodis: " << std::left << std::setw(17) << t.first << " pasikartojo " << std::left << std::setw(3) << t.second << " kartus - eilutese: ";
                eilutesMap[t.first].erase(std::unique(eilutesMap[t.first].begin(), eilutesMap[t.first].end()), eilutesMap[t.first].end());
                out << eilutesMap[t.first][0];
                for (int i = 1; i < eilutesMap[t.first].size(); i++) {
                    out << ", " << eilutesMap[t.first][i];
                }
                out << endl;
            }
        }
        out << endl;
        out << "-------NUORODOS-------" << endl;
        for (auto i : url) {
            out << i << endl;
        }
        out.close(); url.clear();
    }
    else cout << "Failas Lotynu.txt aplanke nebuvo rastas" << endl;
    cout << "Failias Atsakymas.txt sukurtas!" << endl;
    file.close();
}
