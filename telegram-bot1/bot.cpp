 

//NuGet\Install-Package libcurl.NET.x64 -Version 1.4.1


#include <iostream>
#include <string>
#include <curl/curl.h>

// Function to send a POST request to Telegram
bool sendTelegramMessage(const std::string& botToken, const std::string& chatId, const std::string& message) {
    CURL* curl;
    CURLcode res;
    bool success = false;

    // Initialize cURL
    curl = curl_easy_init();
    if (curl) {
        // Validate message length
        if (message.size() > INT_MAX) {
            std::cerr << "Message too long to be escaped." << std::endl;
            curl_easy_cleanup(curl);
            return false;
        }

        // Construct the API URL
        std::string apiUrl = "https://api.telegram.org/bot" + botToken + "/sendMessage";

        // Construct the POST data
        std::string postFields = "chat_id=" + chatId + "&text=" +
            curl_easy_escape(curl, message.c_str(), static_cast<int>(message.size()));

        // Set cURL options
        curl_easy_setopt(curl, CURLOPT_URL, apiUrl.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields.c_str());

        // Perform the request
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            std::cerr << "cURL error: " << curl_easy_strerror(res) << std::endl;
        }
        else {
            success = true;
        }

        // Cleanup
        curl_easy_cleanup(curl);
    }
    else {
        std::cerr << "Failed to initialize cURL." << std::endl;
    }

    return success;
}

int main() {
    // Replace these with your actual bot token and chat ID
  // Replace these with your actual bot token and chat ID
   /*
   1- Create a Telegram Bot and Get a Bot Token
   
   telegram Start a chat with BotFather and use the command /newbot to create a new bot click start.
   Provide a name for your bot (e.g., MyFirstBot). must end by bot
   After creation, BotFather will send you a token 
   (a string that looks like 123456:ABC-DEF1234ghIkl-zyx57W2v1u123ew11).
   std::string botToken = "123456:ABC-DEF1234ghIkl-zyx57W2v1u123ew11"


   2-
   Get Your Chat ID
   https://api.telegram.org/bot<TOKEN>/getUpdates
   https://api.telegram.org/bot123456:ABC-DEF1234ghIkl-zyx57W2v1u123ew11/getUpdates

   If you're in a private chat, you’ll see your chat ID under "id"
   If it's a group chat, ill have a negative sign (e.g., -123456789).
   std::string chatId = "-123456789";
   */

    std::string botToken = "";  // Your bot token
    std::string chatId = "";  // Your chat ID (channel chat ID)


    std::string message = "Hello from your C++ Telegram bot!";  // Message to send



    // Send the message
    if (sendTelegramMessage(botToken, chatId, message)) {
        std::cout << "Message sent successfully!" << std::endl;
    }
    else {
        std::cerr << "Failed to send message." << std::endl;
    }

    return 0;
}

