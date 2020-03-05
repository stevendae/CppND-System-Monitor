#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os;
    linestream >> version;
    linestream >> kernel;
  }
  return version + " " + kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());

  // opendir opens a directory stream corresponding to the
  // directory name, and returns a pointer to the directory stream.
  // The stream is positioned at the first entry in the directory.

  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) { // reads through every file in directory
    
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  std::string line, key, value;
  std::string MemTotal {0}, MemFree{0};
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {
    while(std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "MemTotal:") {MemTotal = value;}
      if (key == "MemFree:") {
        MemFree = value;
        return (stof(MemTotal) - stof(MemFree))/stof(MemTotal);
        }
    }
  }
  return (stof(MemTotal) - stof(MemFree))/stof(MemTotal);
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 

  std::string line, uptime;
  std::ifstream dancestream(kProcDirectory + kUptimeFilename);
  if (dancestream.is_open()) {
    std::getline(dancestream, line);
    std::istringstream linestream(line);
    linestream >> uptime;
    return std::stol(uptime);
  
  }
  return std::stol(uptime);

}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
  string line;
  string specifier;
  vector<string> cpu_util;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> specifier;
      if (specifier == "cpu"){
        string value;
        while (!linestream.eof()) {
          linestream >> value; 
          cpu_util.push_back(value);
        }
        return cpu_util;
      }

    }
  }

  return cpu_util;
}
#include <iostream>
vector<string> LinuxParser::ProcessCpuUtilization(string kProcFolder ) {
  string line;
  string value;
  vector<string> cpu_util;
  std::ifstream stream(kProcDirectory + kProcFolder + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while(!linestream.eof()){
        if (!(linestream >> value)) {value = "0.0";}
        cpu_util.push_back(value);
      }
      return cpu_util;
    }
  }

  return cpu_util;
}


// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  string line;
  string key;
  string value; 
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "processes") {
          return std::stoi(value);
        }
      }
    }
  }
  return std::stoi(value);
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  string line;
  string key;
  string value; 
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "procs_running") {
          return std::stoi(value);
        }
      }
    }
  }
  return std::stoi(value);
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
  string line;
  std::ifstream stream(kProcDirectory + to_string(pid) + kCmdlineFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    return line;
  }
  return line;
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  string line;
  string key;
  string value;
  string value_unit;

  string pid_string = to_string(pid);

  std::ifstream stream(kProcDirectory + pid_string + kStatusFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "VmSize:") {
          linestream >> value_unit;
          /*
          if (value_unit == "kB") {
            float mb = std::stof(value)/1000.0;
            value = mb;
          }
          */
          return value;
        }
      }
    }
  }
  return value;


}



// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {  
  string line;
  string key;
  string value;

  string pid_string = to_string(pid);

  std::ifstream stream(kProcDirectory + pid_string + kStatusFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "Uid:") {
          return value;
        }
      }
    }
  }
  return value;
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) {
  string uid = Uid(pid);
  
  string line;
  string uname;
  string temp;
  string id;

  std::ifstream stream(kPasswordPath);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> uname >> temp >> id ){
        if (id == uid)
          return uname;
      }
    }
  }
  return uname;
  
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function

long LinuxParser::UpTime(int pid) {
  string line;
  string temp;
  string value;
  string pid_string = to_string(pid);

  std::ifstream stream(kProcDirectory + pid_string + kStatFilename);
  if (stream.is_open()) {
    while(std::getline(stream, line)){
      std::istringstream linestream(line);
      for (int i = 0; i < 21; i++){
        linestream >> temp;
      }
      linestream >> value;
      return std::stol(value);
    }
  }
  return 0;


}