#ifndef PIPE_H
#define PIPE_H

#include <boost/process/io.hpp>
#include <string>
#include <iostream>
#include <boost/process.hpp>
#include <boost/asio.hpp>

namespace bp = boost::process;

class Pipe{
  
  public:
  
    Pipe(std::string pythonFilePath){
    }

    ~Pipe(){
    }

    void readData(){
    }

  private:
};

#endif
