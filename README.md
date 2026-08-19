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

Do not share this file or upload it to GitHub.

### 2. `history.json`

Create an empty JSON array in a file called:

`history.json`

The initial content should be:

```json
[]