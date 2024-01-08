#ifndef COMMAND_RUNNER_HPP
#define COMMAND_RUNNER_HPP

#include <functional>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

class CommandRunner {
public:
  CommandRunner();
  ~CommandRunner();

  void runCommand(const std::string &command, bool wait = true);
  void waitUntilFinished();

  std::function<void(const std::string &)> onProgramLog;
  std::function<void(const std::string &)> onProgramError;

private:
  std::string command;
  std::thread workingThread;
  std::thread stdOUtThred;
  std::thread stdErrThread;
  std::mutex mutex;
  bool running;
  bool stopRequested;

  void executeCommand(bool wait);
};

#endif // COMMAND_RUNNER_HP
