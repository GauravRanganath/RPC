// -*- c++ -*-
#ifndef TEST_RPC_COMMON_H
#define TEST_RPC_COMMON_H

#include "rpcxx.h"
#include <thread>

class ServiceTestUtil {
 protected:
  rpc::Server *srv = nullptr;
  rpc::Client *client = nullptr;
  std::thread t;
 public:
  void SetUpServer() {
    srv = new rpc::Server();
    srv->Listen("127.0.0.1", 3888);

    t = std::thread([this]() {
      srv->MainLoop();
    });
  }
  void SetUpClient() {
    client = new rpc::Client();
    client->Connect("127.0.0.1", 3888);
  }
  void TearDownServer() {
    srv->SignalStop();
    t.join();
    delete srv;
  }
  void TearDownClient() {
    delete client;
  }
};

#endif /* TEST_RPC_COMMON_H */
