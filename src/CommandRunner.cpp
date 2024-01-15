#include "CommandRunner.hpp"
#include <array>
#include <cstdio>
#include <string>
#include <thread>

std::string exec(const char *cmd) {
  static const std::size_t BUFF_SIZE = 100000;
  std::array<char, BUFF_SIZE> buffer{};
  std::string result;

  // NOLINTNEXTLINE
  std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
  if (!pipe) {
    throw std::runtime_error("popen() failed!");
  }
  while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
    result += buffer.data();
  }
  return result;
}

CommandRunner::CommandRunner() {}

CommandRunner::~CommandRunner() { waitUntilFinished(); }

void CommandRunner::runCommand(const std::string &command, bool wait) {
  if (running) {
    waitUntilFinished();
  }

  workingThread = std::thread(&CommandRunner::executeCommand, this, command);

  if (!wait) {
    workingThread.detach(); // Detach the thread if not waiting
  }
}

void CommandRunner::waitUntilFinished() {
  if (running) {
    stopRequested = true;
    if (workingThread.joinable()) {
      workingThread.join();
    }
    running = false;
  }
}

void CommandRunner::executeCommand(const std::string &command) {
  static const std::size_t BUFF_SIZE = 100000;
  std::array<char, BUFF_SIZE> buffer{};
  std::string result;
  std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"),
                                                pclose);
  if (!pipe) {
    throw std::runtime_error("popen() failed!");
  }
  while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
    result += buffer.data();
  }
}
