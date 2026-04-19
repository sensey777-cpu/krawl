#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <cmath>
#include <cstdlib>
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"
#define WHITE   "\033[37m" 
using namespace std;

// Словник для змінних
map<string, double> vars;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "🦾 KRAWL v3.0 | МОДУЛЬНА СИСТЕМА" << endl;
        return 0;
    }

    ifstream file(argv[1]);
    string line;

    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        // --- БЛОК 1: БАЗОВІ КОМАНДИ ---
        if (line.find("show ") == 0) {
            cout << line.substr(5) << endl;
        }
        else if (line.find("do ") == 0) {
            system(line.substr(3).c_str());
        }
        else if (line.find("set ") == 0) {
            size_t eq = line.find("=");
            string name = line.substr(4, eq - 5);
            vars[name] = stod(line.substr(eq + 1));
        }else if (line.find("create ") == 0) {
            string fn = line.substr(7);
            ofstream f(fn); f.close();
            cout << "📄 Створено файл: " << fn << endl;
        }
        else if (line.find("delete ") == 0) {
            string fn = line.substr(7);
            remove(fn.c_str());
            cout << "🗑️ Видалено: " << fn << endl;
        }
        else if (line.find("cls") == 0) {
            system("clear");
        }
        else if (line.find("wait ") == 0) {
            int sec = stoi(line.substr(5));
            string cmd = "sleep " + to_string(sec);
            system(cmd.c_str());
        }else if (line.find("check ") == 0) {
            // Перевірка пінгу (мережева команда)
            string site = line.substr(6);
            string cmd = "ping -c 1 " + site;
            cout << "🌐 Перевірка зв'язку з " << site << "..." << endl;
            system(cmd.c_str());
        }
        else if (line.find("if_host") == 0) {
            // Показує ім'я пристрою
            system("hostname");
        }
        else if (line.find("say ") == 0) {
            // Команда для озвучки (якщо встановлено termux-tts)
            // Або просто гарний вивід у рамці
            cout << "📢 [KRAWL ГОВОРИТЬ]: " << line.substr(4) << endl;
        }
        else if (line.find("my_os") == 0) {
            // Показує версію ядра
            system("uname -a");
        }else if (line.find("scan_net") == 0) {
            // Показує всі пристрої в твоїй Wi-Fi мережі
            cout << "🔍 Сканую локальну мережу..." << endl;
            system("arp -a");
        }
        else if (line.find("top_proc") == 0) {
            // Показує самі "важкі" процеси (натисни 'q' щоб вийти потім)
            system("top -n 1 -b | head -n 20");
        }
        else if (line.find("get_files") == 0) {
            // Швидкий пошук усіх текстових файлів
            cout << "📂 Текстові файли в цій папці:" << endl;
            system("ls *.txt *.kr");
        }
        else if (line.find("net_stat") == 0) {
            // Показує активні з'єднання
            system("netstat -tupln");
        }else if (line.find("read ") == 0) {
            // Читає вміст будь-якого файлу
            string fn = line.substr(5);
            string cmd = "cat " + fn;
            cout << "📖 Читаю файл " << fn << ":" << endl;
            system(cmd.c_str());
        }
        else if (line.find("search ") == 0) {
            // Шукає слово у всіх файлах .kr
            string word = line.substr(7);
            string cmd = "grep -rnw . -e " + word;
            cout << "🔍 Шукаю '" << word << "' у скриптах..." << endl;
            system(cmd.c_str());
        }
        else if (line.find("weather") == 0) {
            // Показує погоду (потребує інету)
            system("curl -s wttr.in?0");
        }
        else if (line.find("my_time") == 0) {
            // Точний час і дата
            system("date '+%Y-%m-%d %H:%M:%S'");
        }
        else if (line.find("whoami") == 0) {
            // Показує поточного користувача Termux
            system("whoami");
        }else if (line.find("download ") == 0) {
            // Завантажує файл за посиланням (потрібен wget або curl)
            string url = line.substr(9);
            string cmd = "wget " + url;
            cout << "📥 Завантажую файл з: " << url << endl;
            system(cmd.c_str());
        }
        else if (line.find("port_scan ") == 0) {
            // Швидка перевірка відкритих портів на хості
            string host = line.substr(10);
            string cmd = "nmap -F " + host;
            cout << "📡 Сканую популярні порти на " << host << "..." << endl;
            system(cmd.c_str());
        }
        else if (line.find("get_ip") == 0) {
            // Показує твій зовнішній IP (як тебе бачить світ)
            system("curl -s ifconfig.me");
            cout << endl;
        }
        else if (line.find("site_check ") == 0) {
            // Перевіряє заголовок сайту (чи живий він)
            string site = line.substr(11);
            string cmd = "curl -I " + site;
            system(cmd.c_str());
        }
        else if (line.find("speedtest") == 0) {
            // Запуск тесту швидкості (якщо встановлено speedtest-cli)
            system("speedtest --simple");
        }else if (line.find("logo") == 0) {
            cout << CYAN << BOLD << "  _  __  ___  _    _ _ " << RESET << endl;
            cout << CYAN << BOLD << " | |/ /  _ \\/ _ \\| |  | | |" << RESET << endl;
            cout << CYAN << BOLD << " | ' /| |_) | |_| | |  | | |" << RESET << endl;
            cout << CYAN << BOLD << " | . \\|  _ <|  _  | || | |_" << RESET << endl;
            cout << CYAN << BOLD << " |_|\\_\\_| \\_\\_| |_|__|_|" << RESET << endl;
            cout << YELLOW << "      Version 3.5 | Power by C++" << RESET << endl;
        }
        else if (line.find("alert ") == 0) {
            cout << RED << BOLD << "[УВАГА]: " << RESET << RED << line.substr(6) << RESET << endl;
        }
        else if (line.find("success ") == 0) {
            cout << GREEN << BOLD << "[УСПІХ]: " << RESET << GREEN << line.substr(8) << RESET << endl;
        }
        else if (line.find("info ") == 0) {
            cout << BLUE << BOLD << "[INFO]: " << RESET << CYAN << line.substr(5) << RESET << endl;
        }else if (line.find("calc ") == 0) {
            // Квадратний корінь
            string name = line.substr(5);
            cout << CYAN << "🔢 SQRT(" << name << ") = " << RESET << GREEN << sqrt(vars[name]) << RESET << endl;
        }
        else if (line.find("rand ") == 0) {
            // Випадкове число
            int max_val = stoi(line.substr(5));
            cout << CYAN << "🎲 Random: " << RESET << YELLOW << rand() % max_val << RESET << endl;
        }
        else if (line.find("pow ") == 0) {
            // Квадрат числа
            string name = line.substr(4);
            cout << CYAN << "⚡ " << name << "^2 = " << RESET << GREEN << pow(vars[name], 2) << RESET << endl;
        }
        else if (line.find("status") == 0) {
            // Стан пам'яті
            cout << BLUE << BOLD << "🧠 Krawl Memory Status:" << RESET << endl;
            for(auto const& [name, val] : vars) {
                cout << "   " << YELLOW << name << RESET << " => " << GREEN << val << RESET << endl;
            }
        }else if (line.find("version") == 0) {
            // Виводить інформацію про версію та автора
            cout << CYAN << BOLD << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << RESET << endl;
            cout << YELLOW << BOLD << "  KRAWL LANGUAGE " << RESET << WHITE << "v3.5" << endl;
            cout << BLUE << "  Developer: " << RESET << "Your Name (Krawl Team)" << endl;
            cout << BLUE << "  Build: " << RESET << "April 2026" << endl;
            cout << BLUE << "  Status: " << RESET << GREEN << "Stable Alpha" << RESET << endl;
            cout << CYAN << BOLD << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << RESET << endl;
        }else if (line.find("gen_pass") == 0) {
            // Генератор паролів
            string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%&*";
            string pass = "";
            for (int i = 0; i < 15; i++) pass += chars[rand() % chars.length()];
            cout << GREEN << BOLD << "🔐 SECURE PASS: " << RESET << WHITE << pass << RESET << endl;
        }
        else if (line.find("site_ping ") == 0) {
            // Швидка перевірка зв'язку з сайтом
            string site = line.substr(10);
            string cmd = "ping -c 2 " + site;
            cout << BLUE << "📡 Перевірка зв'язку з " << site << "..." << RESET << endl;
            system(cmd.c_str());
        }

        // <<< СЮДИ МИ БУДЕМО ВСТАВЛЯТИ НОВІ БЛОКИ >>>

    }
    return 0;
}
