# C++ AI Assistant

A simple AI assistant written in C++ using the OpenAI API.

I created this project to improve my C++ skills and gain practical
experience with API requests, JSON, Unicode/UTF-8 handling and
working with AI models.

## Features

- OpenAI API integration
- Chat with an AI model
- Persistent chat history
- JSON-based message storage
- UTF-8 input support
- Console-based interface
- HTTP requests using CPR
- JSON processing using nlohmann/json

## Technologies

- C++
- CPR
- nlohmann/json
- OpenAI API
- Windows API

## Dependencies

This project uses the following external libraries:

- [CPR](https://github.com/libcpr/cpr) - HTTP requests
- [nlohmann/json](https://github.com/nlohmann/json) - JSON parsing and serialization

The project also uses the Windows API for UTF-8 and console input handling.

## How it works

The program receives text input from the user and converts the
Unicode input to UTF-8.

The message is then added to the local chat history and sent to
the OpenAI API as a JSON request.

After receiving the response, the assistant adds the response to
the chat history and saves the updated history to `history.json`.

When the program starts again, the previous chat history is loaded
from `history.json`, allowing the assistant to keep the previous
conversation context.

## Setup

The program requires two local files:

### 1. `key.txt`

Create a file called:

`key.txt`

The file must contain your OpenAI API key.

Example:

`sk-...`

Do not share this file!

### 2. `history.json`

The `history.json` file does not need to be created manually.

If the file does not exist, the program will create it automatically
after the first message and use it to store the chat history.
