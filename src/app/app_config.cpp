//
// Created by pp on 7/29/22.
//

#include <app/app_config.hpp>

#include <boost/json.hpp>
#include <fstream>

namespace json = boost::json;

namespace mgmt::app {
static mgmt::app::AppConfig tag_invoke(json::value_to_tag<mgmt::app::AppConfig> /* unused */, const json::value& jvalue)
{
  const json::object& obj = jvalue.as_object();
  return mgmt::app::AppConfig{
    .log_dir = json::value_to<std::string>(obj.at("log_dir")),
    .dtree_file = json::value_to<std::string>(obj.at("dtree_file")),
    .entity_client_config = json::value_to<mgmt::home_assistant::adapter::EntityClientConfig>(obj.at("entity_client_config"))
  };
}

AppConfig load_config(const std::string& path)
{
  auto file = std::fstream(path, std::ios::in);
  if (!file) {
    throw std::runtime_error("Error while reading file.");
  }
  auto parser = json::stream_parser{};
  auto error_code = json::error_code{};

  do {
    auto buffer = std::array<char, 4096>{};
    file.read(buffer.begin(), buffer.size());
    parser.write(buffer.data(), file.gcount(), error_code);
  } while (!file.eof());

  if (error_code) {
    throw std::runtime_error("Error while reading file.");
  }
  parser.finish(error_code);

  if (error_code) {
    throw std::runtime_error("Error while parsing file. File may be malformed.");
  }

  return json::value_to<mgmt::app::AppConfig>(parser.release());
}

std::string pretty_format_config(const mgmt::app::AppConfig& config)
{
  return fmt::format(
    "\nGeneral: \n"
    "\tlog_dir: {}\n"
    "\tdtree_file: {}\n"
    "Entity client config:\n"
    "\tserver_address: {}\n"
    "\tserver_port: {}\n"
    "\tkeep_alive_interval: {}\n"
    "\tmax_reconnect_attempts: {}\n"
    "\treconnect_delay(seconds): {}",
    config.log_dir,
    config.dtree_file,
    config.entity_client_config.server_address,
    config.entity_client_config.server_port,
    config.entity_client_config.keep_alive_interval,
    config.entity_client_config.max_reconnect_attempts,
    config.entity_client_config.reconnect_delay.count());
}
}// namespace mgmt::app
