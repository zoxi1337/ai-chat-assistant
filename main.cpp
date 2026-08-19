#pragma execution_character_set("utf-8")
#include <cpr/cpr.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include <vector>
#include <fstream>

using json = nlohmann::json;
using namespace std;
using namespace cpr;

string to_utf8(const wstring& text)
{
    if (text.empty()) return "";

    int size = WideCharToMultiByte(CP_UTF8, 0, text.c_str(), -1,
        nullptr, 0, nullptr, nullptr);
    string result(size - 1, '\0');
    WideCharToMultiByte(CP_UTF8, 0, text.c_str(), -1,
        result.data(), size, nullptr, nullptr);
    return result;
}

class AiClient {
private:
    string name;
    string key;
    json history;
public:
    AiClient(string name) : name(name), history(json::array()) {}

    string SendMessage(const json& Message) {
        try {
            auto response = Post(
                Url{ "https://api.openai.com/v1/responses" },
                Header{
                    {"Authorization", "Bearer " + key},
                    {"Content-Type", "application/json"}
                },
                Body{ Message.dump() }
            );

            string answer;

            if (response.status_code != 200) {
                cerr << "HTTP error: " << response.status_code << '\n';
                cerr << response.text << '\n';
                return "";
            }

            json data = json::parse(response.text);
            for (auto output : data["output"]) {
                if (output["type"] == "message") {
                    for (auto content : output["content"]) {
                        if (content["type"] == "output_text") {
                            answer = content["text"];
                            break;
                        }
                    }
                }
            }
            cout << answer << '\n';
            return answer;
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << '\n';
        }
        return "";
    }

    const json& GetHistory() const {
        return history;
    }

    void LoadMessageHistory(const json& history) {
        this->history = history;
    }

    void AddModelOutput(const string& answer) {
        history.push_back({
        {"role", "assistant"},
        {"content", answer}
            });
    }

    void AddUserInput(const string& my_message) {
        history.push_back({
            {"role", "user"},
            {"content", my_message}
            });
    }

    void LoadApiKey(const string& key) {
        this->key = key;
    }
};

int main()
{
    _setmode(_fileno(stdin), _O_U16TEXT);
    SetConsoleOutputCP(CP_UTF8);
    ifstream apiFile("key.txt");
    ifstream file("history.json");

    string apiKey;
    string model_answer;
    AiClient mymessage("chat1");

    if (apiFile.is_open()) {
        getline(apiFile, apiKey);
        mymessage.LoadApiKey(apiKey);
        apiFile.close();
    }
    else {
        cout << "Cann't open api key!" << "\n";
    }

    if (file.is_open()) {
        json historyData = json::parse(file);
        mymessage.LoadMessageHistory(historyData);
        file.close();
    }
    else {
        cout << "Cann't open history!" << "\n";
    }

    while (true) {
        wstring input;
        getline(wcin, input);

        string UserInput = to_utf8(input);
        mymessage.AddUserInput(UserInput);
        json body;
        body["model"] = "gpt-5.6-luna";
        body["input"] = mymessage.GetHistory();
        model_answer = mymessage.SendMessage(body);
        mymessage.AddModelOutput(model_answer);
        ofstream file("history.json");
        file << mymessage.GetHistory().dump(4);
        file.close();
    }
}