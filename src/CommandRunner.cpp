#include "CommandRunner.hpp"
#include <cstdio>
#include <thread>

CommandRunner::CommandRunner() : running(false), stopRequested(false) {}

CommandRunner::~CommandRunner() { waitUntilFinished(); }

void CommandRunner::runCommand(const std::string &command, bool wait) {
  if (running) {
    waitUntilFinished();
  }

  this->command = command;
  workingThread = std::thread(&CommandRunner::executeCommand, this, wait);

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

void CommandRunner::executeCommand(bool wait) {}
