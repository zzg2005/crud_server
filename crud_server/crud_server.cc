/*
   Mathieu Stefani, 07 février 2016

   Updated by zzg2005, Sep 2020

   Example of a REST endpoint with routing
*/

#include <algorithm>

#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/router.h>

using namespace std;
using namespace Pistache;

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class StatsEndpoint {
public:
  explicit StatsEndpoint(Address addr)
      : httpEndpoint(std::make_shared<Http::Endpoint>(addr)) {}

  void init(size_t thr = 2) {
    auto opts = Http::Endpoint::options().threads(static_cast<int>(thr));
    httpEndpoint->init(opts);
    setupRoutes();
  }

  void start() {
    httpEndpoint->setHandler(router.handler());
    httpEndpoint->serve();
  }

private:
  void setupRoutes() {
    using namespace Rest;

    Routes::Get(router, "/demo", Routes::bind(&StatsEndpoint::doGet, this));
    Routes::Put(router, "/demo", Routes::bind(&StatsEndpoint::doPut, this));
    Routes::Post(router, "/demo", Routes::bind(&StatsEndpoint::doPost, this));
    Routes::Delete(router, "/demo",
                   Routes::bind(&StatsEndpoint::doDelete, this));
  }

  void doGet(const Rest::Request &request, Http::ResponseWriter response) {
    std::cout << "doGet!" << std::endl;
    auto jj = json::parse(request.body());
    response.send(Http::Code::Ok,  "doGet! \n" +jj.dump()+"\n");     
  }

  void doPut(const Rest::Request &request, Http::ResponseWriter response) {
    std::cout << "doPut!" << std::endl;
    auto jj = json::parse(request.body());
    std::string name = jj["name"];
    std::string age =jj["age"];
    std::string test = name+" is my name, and my age is "+age + "\n";
    response.send(Http::Code::Ok, test);      
  }

  void doPost(const Rest::Request &request, Http::ResponseWriter response) {
    std::cout << "doPost!" << std::endl;    
    auto jj = json::parse(request.body());
    response.send(Http::Code::Ok,  "doPost! \n" +jj.dump()+"\n");    
  }

  void doDelete(const Rest::Request &request, Http::ResponseWriter response) {
    std::cout << "doDelete!" << std::endl;    
    auto jj = json::parse(request.body());
    response.send(Http::Code::Ok,  "doDelete! \n" +jj.dump()+"\n");    
  }

  std::shared_ptr<Http::Endpoint> httpEndpoint;
  Rest::Router router;
};

int main(int argc, char *argv[]) {
  Port port(9080);

  int thr = 2;

  if (argc >= 2) {
    port = static_cast<uint16_t>(std::stol(argv[1]));

    if (argc == 3)
      thr = std::stoi(argv[2]);
  }

  Address addr(Ipv4::any(), port);

  cout << "Cores = " << hardware_concurrency() << endl;
  cout << "Using " << thr << " threads" << endl;

  StatsEndpoint stats(addr);

  stats.init(thr);
  stats.start();
}
